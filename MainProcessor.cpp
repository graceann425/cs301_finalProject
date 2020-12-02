#include "MainProcessor.h"

//constructor
MainProcessor::MainProcessor(string config_filename)
{

	ifstream in; //takes in the configuration file
	in.open(config_filename.c_str());
	string line;

	while (getline(in, line)) { //parses configuration file
		if (line.size() == 0 || line.at(0) == '#')
			continue;

		string::size_type idx = 0;
		string parameter = "";
		string value = "";
		bool isValue = false;

		while (idx < line.size()){
			char c = line.at(idx);
			if (c == ' ' || c == '\t'){
				idx++;
			} else if (c == '#'){
				break;
			} else if (c == '='){
				isValue = true;
				idx++;
			} else if (isValue){
				value += c;
				idx++;
			} else {
				parameter += c;
				idx++;
			}
		}

		if (parameter.compare("program_input") == 0){
			program_input = value;
		} else if (parameter.compare("memory_contents_input") == 0){
			memory_contents_input = value;
		} else if (parameter.compare("register_file_input") == 0){
			register_file_input = value;
		} else if (parameter.compare("output_mode") == 0){
			output_mode = value;
		} else if (parameter.compare("debug_mode") == 0){
			if (value.compare("true") == 0){
				debug_mode = true;
			} else {
				debug_mode = false;
			}
		} else if (parameter.compare("print_memory_contents") == 0){
			if (value.compare("true") == 0){
				print_memory_contents = true;
			} else {
				print_memory_contents = false;
			}
		} else if (parameter.compare("write_to_file") == 0){
			if (value.compare("true") == 0){
				write_to_file = true;
			} else {
				write_to_file = false;
			}
		} else {
			output_file = value;
		}

	}

	//initiates objects
	registerMem.readFileMemory(register_file_input);
	dataMem = new DataMemory(memory_contents_input);
	parser = new ASMParser(program_input);
	pc = new PC("400000");

	registerFile.setRegisterMemory(registerMem);

	instructions = parser->getInstructionVector();

	jumpAddress = "400000";

	alu1.setName("ADD");
	alu2.setName("ADD | ALU Result");
	alu3.setName("ALU | ALU Result");

	mux1.setName("mux1");
	mux2.setName("mux2");
	mux3.setName("mux3");
	mux4.setName("mux4");
	mux5.setName("mux5");

	shiftL1.setName("shiftL1 | 26 - 28");
	shiftL2.setName("shiftL2");

	if (write_to_file && output_file.size() != 0)
		outfile.open(output_file, ios::trunc);
}


/**
 * Default destructor.
 */
MainProcessor::~MainProcessor()
{
	delete dataMem;
	delete parser;
	delete pc;
}


/**
 * Fetch stage of an instruction cycle. It reads and updates the current address.
 *
 * @return true if the new address is within bounds of the program, false if not.
 */
bool MainProcessor::fetch()
{
	 // Get string address and convert to int (hex)
	curAddress = pc->getAddress();
	//cout << "address:" << curAddress << endl;
	int int_address = stoi(curAddress, nullptr, 16);

	// Fetch the right instruction within instruction vector
	curInstrIdx = (int_address - 0x400000)/4;
	//cout << curInstrIdx << endl;

	if (curInstrIdx >= static_cast<int>(instructions.size()))
		return false;

	currentInstruction = instructions.at(curInstrIdx);
	//cout << currentInstruction.getOriginalCode() << endl;
	//cout << currentInstruction.getEncoding() << endl;


	// Update address to next instruction (PC+4)
	string binary_4 = "00000000000000000000000000000100";
	alu1.operate(NumberConverter::hexToBinary(curAddress), binary_4);
	pc->setAddress(alu1.getOutput());

	return true;
}


/**
 * Decode stage of an instruction cycle.
 */
void MainProcessor::decode()
{
	// Set control signals according to instruction opcode
	string opcode = currentInstruction.getEncoding().substr(0,6);
	mainControlUnit.setControlSignal(currentInstruction.getOpcode(), opcode);

	if (mainControlUnit.getJump() == 1) {
		// Get jump address and shift left by 2
		string j = currentInstruction.getEncoding();
		j = shiftL1.shiftAdd(j.substr(6, string::npos));

		// alu1 output = PC+4
		string PC4_address = NumberConverter::hexToBinary(alu1.getOutput());

		// concatenate PC+4 [31-28] and jump address [31-0]
		jumpAddress = PC4_address.substr(0,4) + j;

	} else {
		// Load instruction registers into Register File
		registerFile.readR1(currentInstruction.getRS());
		registerFile.readR2(currentInstruction.getRT());

		// Get instruction type
		Opcode o = currentInstruction.getOpcode();

		// Determine write register
		if (o == LW || o == ADDI || isRtype(o)) {

			string rt = to_string(currentInstruction.getRT());
			string rd = to_string(currentInstruction.getRD());

			string mux1_result = mux1.select(rt,rd, mainControlUnit.getRegDest());

			// Set write register
			int wr = stoi(mux1_result,nullptr,16);
			registerFile.readWriteRegister(wr);
		}


		// For I-Type
		if (isIType(o)) {
			// Sign extend from 16 to 32 bits
			string immediate = currentInstruction.getEncoding().substr(16, string::npos);
			signExtend32.extendTo32(immediate);
			ALUControl.determineALUOperation(mainControlUnit.getALUOp(), "");
		}
		// For R-Type
		else if (isRtype(o)) {
			string func = currentInstruction.getEncoding().substr(27, string::npos);
			ALUControl.determineALUOperation(mainControlUnit.getALUOp(), func);
		}
	}
}


/**
 * Execute stage of an instruction cycle.
 *
 */
void MainProcessor::execute()
{
	Opcode o = currentInstruction.getOpcode();

	if (!isJType(o)) {

		// Determine which value will go to the ALU
		string in0 = registerFile.getDataR2();
		in0 = NumberConverter::hexToBinary(in0);

		string in1 = signExtend32.getOutput();

		string mux2_result = mux2.select(in0, in1, mainControlUnit.getALUSrc());
		mux2_result = NumberConverter::hexToBinary(mux2_result);


		// Convert DataR1 from hex to binary
		string input_r1 = registerFile.getDataR1();
		input_r1 = NumberConverter::hexToBinary(input_r1);


		// Set the operation of alu3 and then operate
		alu3.setOperation(ALUControl.getOutput());
		alu3.operate(input_r1, mux2_result);
	}

	string mux5_result = "";

	// Case where there is a BEQ instruction
	if (mainControlUnit.getBranch() == 1) {

		// Get sign extended address and shift left by 2
		string beq_address = signExtend32.getOutput();
		beq_address = shiftL2.shift(beq_address);

		// Add PC+4 and address from beq to get target address
		string curAddress_binary = NumberConverter::hexToBinary(curAddress);
		alu2.operate(curAddress_binary, beq_address);
		// string curAddress_binary = NumberConverter::hexToBinary(pc->getAddress());
		// alu2.operate(curAddress_binary, beq_address);


		string alu3_output = alu3.getOutput();
		if (alu3_output.compare("00000000") == 0) {
			// If beq condition is true
			mux5_result = mux5.select(alu1.getOutput(), alu2.getOutput(), 1);

		} else {
			// If beq condition is false
			mux5_result = mux5.select(alu1.getOutput(), alu2.getOutput(), 0);
		}

	// If no BEQ, mux5 still needs to output PC+4
	} else {
			mux5_result = mux5.select(alu1.getOutput(), alu2.getOutput(), mainControlUnit.getBranch());
	}

	// Select address and write it back to PC
	string mux4_result = mux4.select(mux5_result, jumpAddress, mainControlUnit.getJump());
	pc->setAddress(mux4_result);
}


/**
 * Memory stage of an instruction cycle.
 */
void MainProcessor::memory()
{
	// Read data
	if (mainControlUnit.getMemRead() == 1) {
		dataMem->setInAddress(alu3.getOutput());
		dataMem->readData();

	// Write data
	} else if (mainControlUnit.getMemWrite() == 1) {
		dataMem->setInAddress(alu3.getOutput());
		dataMem->setInData(registerFile.getDataR2());
		dataMem->writeData();
	}
}


/**
 * Writeback stage of the instruction cycle.
 */
void MainProcessor::writeback()
{
	Opcode o = currentInstruction.getOpcode();
	if (o == LW || o == ADDI || isRtype(o)) {
		string mux3_result = "";
		mux3_result = mux3.select(alu3.getOutput(), dataMem->getOutData(), mainControlUnit.getMemToReg());
		registerFile.writeData(mux3_result);
	}
}


/**
 * Print or write the current contents of all objects in this processor.
 *
 */
void MainProcessor::printProcessor()
{
	string newLine = "--------------------------------------------------------------------------------\n";

	stringstream s;

	s << newLine << newLine
		<< "----------------------------------FETCH STAGE----------------------------------- \n"
		<< newLine
		<< "Current Address: 0x" << curAddress << '\n'
		<< pc->toString() << "\n\n"

		<< "INSTRUCTION MEMORY\n"
		<< "ASM: " << currentInstruction.getOriginalCode() << "\n"
		<< "Hex: 0x" << NumberConverter::binaryToHex(currentInstruction.getEncoding()) << "\n"
		<< "32-bit: " << currentInstruction.getEncoding() << "\n\n";

		if (print_memory_contents) {
				s << newLine;
				for (int i=0; i < static_cast<int>(instructions.size()); i++)
					s << instructions.at(i).getOriginalCode() << "\n";
				s	<< newLine << "\n";
		}

		s << alu1.toString() << "\n\n"


		<< newLine
		<< "----------------------------------DECODE STAGE---------------------------------- \n"
		<< newLine
		<< mainControlUnit.toString() << "\n\n"

		<< mux1.toString() << "\n\n"
		<< registerFile.toString() << "\n\n"

		<< shiftL1.toString() << "\n\n"
		<< signExtend32.toString() << "\n\n"


		<< newLine
		<< "----------------------------------EXECUTE STAGE--------------------------------- \n"
		<< newLine
		<< ALUControl.toString() << "\n\n"

		<< "--------------------Register File -> ALU -> Data Memory Path--------------------\n\n"
		<< mux2.toString()<< "\n\n"
		<< alu3.toString() << "\n\n"

		<< "------------------------------BEQ Instruction Path------------------------------\n\n"
		<< shiftL2.toString() << "\n\n"
		<< alu2.toString() << "\n\n"
		<< mux5.toString() << "\n\n"
		<< mux4.toString() << "\n\n"


		<< newLine
		<< "----------------------------------MEMORY STAGE---------------------------------- \n"
		<< newLine
		<< dataMem->printInputsAndOutput() << "\n\n"
		<< mux3.toString() << "\n\n";

	if (print_memory_contents) {
			s << newLine
				<< dataMem->printDataMemory()
				<< newLine
				<< registerMem.toString();
	}


	if (write_to_file && output_file.size() != 0) {
		// Write to a specified output file
		outfile << s.str() << endl;

	} else {
		// Print to command prompt
		cout << s.str() << endl;
	}
}


/**
 * Reset the values of the member variables of each object.
 *
 */
void MainProcessor::resetContents()
{
	alu1.reset();
	alu2.reset();
	alu3.reset();

	mux1.reset();
	mux2.reset();
	mux3.reset();
	mux4.reset();
	mux5.reset();

	shiftL1.reset();
	shiftL2.reset();

	dataMem->reset();
	registerFile.reset();
	ALUControl.reset();
	signExtend32.reset();
	mainControlUnit.reset();
}
