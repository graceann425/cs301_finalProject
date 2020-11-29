#include "MainProcessor.h"

MainProcessor::MainProcessor(string config_filename)
{

	ifstream in;
	in.open(config_filename.c_str());
	string line;

	while (getline(in, line)) {
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


MainProcessor::~MainProcessor()
{
	delete dataMem;
	delete parser;
	delete pc;
}


bool MainProcessor::fetch()
{
	 // Get string address and convert to int (hex)
	string address = pc->getAddress();
	int int_address = stoi(address, nullptr, 16);

	// Fetch the right instruction within instruction vector
	//curInstrIdx = (int_address - 0x400000)/4;
	cout << curInstrIdx << endl;

	if (curInstrIdx >= static_cast<int>(instructions.size()))
		return false;

	currentInstruction = instructions.at(curInstrIdx);
	cout << currentInstruction.getOriginalCode() << endl;
	cout << currentInstruction.getEncoding() << endl;

	curInstrIdx++;

	// Update address to next instruction (PC+4)
	alu1.operate(hexToBinary(address), "0100");

	return true;
}


void MainProcessor::decode()
{
	// Set control signals according to instruction opcode
	mainControlUnit.setControlSignal(currentInstruction.getOpcode());

	if (mainControlUnit.getJump() == 1) {
		// Get jump address and shift left by 2
		string j = currentInstruction.getEncoding();
		j = shiftL1.shiftAdd(j.substr(6, string::npos));

		// alu1 output = PC+4
		string PC4_address = alu1.getOutput();

		// concatenate PC+4 [31-28] and jump address [31-0]
		jumpAddress = PC4_address.substr(0,4) + j;

	} else {
		// Load instruction registers into Register File
		registerFile.readR1(currentInstruction.getRS());
		registerFile.readR2(currentInstruction.getRT());

		// Determine write register
		// "0" for RT, "1" for RD
		string result = mux1.select("0","1", mainControlUnit.getRegDest());
		if (result.compare("0") == 0) {
			registerFile.readWriteRegister(currentInstruction.getRT());
		} else {
			registerFile.readWriteRegister(currentInstruction.getRD());
		}

		// Determine the instruction type
		Opcode o = currentInstruction.getOpcode();
		//InstType type = opcodes.getInstType(o);

		// For I-Type
		if (o == ADDI || o == LW || o == SW || o == BEQ) {
			// Sign extend from 16 to 32 bits
			string immediate = currentInstruction.getEncoding().substr(16, string::npos);
			signExtend32.extendTo32(immediate);
		}
		// For R-Type
		else if (o == ADD || o == SUB || o == SLT) {
			string func = currentInstruction.getEncoding().substr(27, string::npos);
			ALUControl.determineALUOperation(mainControlUnit.getALUOp(), func);
		}
	}
}

// R Type : ADD, SUB, SLT
// I Type : ADDI, LW, SW, BEQ
// J Type : J
void MainProcessor::execute()
{
	// Determine which value will go to the ALU
	string in0 = registerFile.getDataR2();
	in0 = hexToBinary(in0);
	string in1 = signExtend32.getOutput();
	string mux2_result = mux2.select(in0, in1, mainControlUnit.getALUSrc());

	// Convert hex to binary
	string input_r1 = registerFile.getDataR1();
	input_r1 = hexToBinary(input_r1);

	// Set the operation of alu3 and then operate
	alu3.setOperation(ALUControl.getOutput());
	alu3.operate(input_r1, mux2_result);

	if (mainControlUnit.getBranch() == 1) {
		// Get sign extended address and shift left by 2
		string beq_address = signExtend32.getOutput();
		beq_address = shiftL2.shift(beq_address);

		// Add PC+4 and address from beq to get target address
		string alu1_output = alu1.getOutput();
		alu1_output = hexToBinary(alu1_output);
		alu2.operate(alu1_output, beq_address);


		string mux5_result = "";

		if (alu3.getOutput().compare("0") == 0) {
			// If beq condition is false
			mux5_result = mux5.select(alu1.getOutput(), alu2.getOutput(), 0);
		} else {
			// If beq condition is true
			mux5_result = mux5.select(alu1.getOutput(), alu2.getOutput(), 1);
		}

		// Select address and write it back to PC
		string mux4_result = mux4.select(mux5_result, jumpAddress, mainControlUnit.getJump());
		pc->setAddress(mux4_result);
	}
}


void MainProcessor::memory()
{

}


void MainProcessor::writeback()
{

}


string MainProcessor::hexToBinary(string hex)
{
	string binary = "";

	for (int i=hex.size()-1; i >= 0; i--) {
		char c = hex.at(i);

		// If uppercase, make lowercase
		if (c >= 65 && c <= 90)
			c += 32;

		switch (c) {
			case '0':
				binary = "0000" + binary;	break;
			case '1':
				binary = "0001" + binary;	break;
			case '2':
				binary = "0010" + binary;	break;
			case '3':
				binary = "0011" + binary;	break;
			case '4':
				binary = "0100" + binary;	break;
			case '5':
				binary = "0101" + binary;	break;
			case '6':
				binary = "0110" + binary;	break;
			case '7':
				binary = "0111" + binary;	break;
			case '8':
				binary = "1000" + binary;	break;
			case '9':
				binary = "1001" + binary;	break;
			case 'a':
				binary = "1010" + binary;	break;
			case 'b':
				binary = "1011" + binary; break;
			case 'c':
				binary = "1100" + binary;	break;
			case 'd':
				binary = "1101" + binary;	break;
			case 'e':
				binary = "1110" + binary;	break;
			case 'f':
				binary = "1111" + binary;	break;
			case 'x':
				// In the case hex number starts with 0x
				return binary;
		}
	}
	return binary;
}


void MainProcessor::printProcessor()
{

	stringstream s;

	s << "---------------------------------------------------------------------\n"
		<< "--------------------Fetch Stage-------------------- \n"
		<< pc->toString() << "\n\n"

		<< "INSTRUCTION MEMORY\n"
		<< "ASM: " << currentInstruction.getOriginalCode() << "\n"
		<< "32-bit: " << currentInstruction.getEncoding() << "\n\n"

		<< alu1.toString() << "\n\n"


		<< "--------------------Decode Stage-------------------- \n"
		<< mux1.toString() << "\n\n"
		<< registerFile.toString() << "\n\n"

		<< mainControlUnit.toString() << "\n\n"

		<< shiftL1.toString() << "\n\n"
		<< signExtend32.toString() << "\n\n"


		<< "--------------------Execute Stage-------------------- \n"
		<< shiftL2.toString() << "\n\n"
		<< alu2.toString() << "\n\n"
		<< mux5.toString() << "\n\n"
		<< mux4.toString() << "\n\n"

		<< mux2.toString()<< "\n\n"
		<< alu3.toString() << "\n\n"
		<< ALUControl.toString() << "\n\n"


		<< "--------------------Memory Stage-------------------- \n"
		<< dataMem->printInputsAndOutput() << "\n\n"
		<< mux3.toString() << "\n\n";

	if (print_memory_contents) {
			s << dataMem->printDataMemory()
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
