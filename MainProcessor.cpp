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

// //program input file
// 	getline(in, line);
// 	string::size_type idx = line.find('=');
// 	line = line.substr(idx, line.length());
// 	int p = 0;
// 	while (p < line.length() && isWhitespace(line.at(p)))
// 		p++;
// 		while (p < len && !isWhitespace(line.at(p))){
// 		string programInput = "";
// 		programInput = programInput + line.at(p);
// 		p++;
// 	}
//
// //memory contents file
// 	getline(in, line);
// 	idx = line.find('=');
// 	line = line.substr(idx, line.length());
// 	int p = 0;
// 	while (p < line.length() && isWhitespace(line.at(p)))
// 		p++;
// 		while (p < len && !isWhitespace(line.at(p))){
// 		string memoryContents = "";
// 		memoryContents = memoryContents + line.at(p);
// 		p++;
// 	}
//
// //register input file
// 	getline(in, line);
// 	idx = line.find('=');
// 	line = line.substr(idx, line.length());
// 	int p = 0;
// 	while (p < line.length() && isWhitespace(line.at(p)))
// 		p++;
// 		while (p < len && !isWhitespace(line.at(p))){
// 		string registerInput = "";
// 		registerInput = registerInput + line.at(p);
// 		p++;
// 	}
//
// //output mode
// 	getline(in, line);
// 	idx = line.find('=');
// 	line = line.substr(idx, line.length());
// 	int p = 0;
// 	while (p < line.length() && isWhitespace(line.at(p)))
// 		p++;
// 		while (p < len && !isWhitespace(line.at(p))){
// 		string output_mode = "";
// 		output_mode = output_mode + line.at(p);
// 		p++;
// 	}
//
// //debug mode
// 	getline(in, line);
// 	idx = line.find('=');
// 	line = line.substr(idx, line.length());
// 	int p = 0;
// 	while (p < line.length() && isWhitespace(line.at(p)))
// 		p++;
// 		while (p < len && !isWhitespace(line.at(p))){
// 		string debug = "";
// 		debug = debug + line.at(p);
// 		p++;
// 	}
// 	if (debug.equals("true"))
// 		debug_mode = true;
// 	else
// 		debug_mode = false;
//
// //print memory contents mode
// 	getline(in, line);
// 	idx = line.find('=');
// 	line = line.substr(idx, line.length());
// 	int p = 0;
// 	while (p < line.length() && isWhitespace(line.at(p)))
// 		p++;
// 		while (p < len && !isWhitespace(line.at(p))){
// 		string memContents = "";
// 		memContents = memContents + line.at(p);
// 		p++;
// 	}
//  	if (memContents.equals("true"))
// 		print_memory_contents = true;
// 	else
// 		print_memory_contents = false;
//
// //output file
// 	getline(in, line);
// 	idx = line.find('=');
// 	line = line.substr(idx, line.length());
// 	int p = 0;
// 	while (p < line.length() && isWhitespace(line.at(p)))
// 		p++;
// 		while (p < len && !isWhitespace(line.at(p))){
// 		output_file = "";
// 		output_file = output_file + line.at(p);
// 		p++;
// 	}
//
// //write to file mode
// 	getline(in, line);
// 	idx = line.find('=');
// 	line = line.substr(idx, line.length());
// 	int p = 0;
// 	while (p < line.length() && isWhitespace(line.at(p)))
// 		p++;
// 		while (p < len && !isWhitespace(line.at(p))){
// 		string fileWrite = "";
// 		fileWrite = fileWrite + line.at(p);
// 		p++;
// 	}
// 	if (fileWrite.equals("true"))
// 		write_to_file = true;
// 	else
// 		write_to_file = false;

	registerMem.readFileMemory(register_file_input);
	dataMem = new DataMemory(memory_contents_input);
	parser = new ASMParser(program_input);
	pc = new PC("400000");

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

	shiftL1.setName("shiftL1: 26 - 28");
	shiftL2.setName("shiftL2");
}

MainProcessor::~MainProcessor()
{
	delete dataMem;
	delete parser;
	delete pc;
}

void MainProcessor::fetch()
{
	 // Get string address and convert to int (hex)
	string address = pc->getAddress();
	int int_address = stoi(address, nullptr, 16);

	// Fetch the right instruction within instruction vector
	int idx =  (int_address - 0x400000)/4;
	currentInstruction = instructions.at(idx);

	// Update address to next instruction (PC+4)
	alu1.operate(address, "4");
}


void MainProcessor::decode()
{
	// Set control signals according to instruction opcode
	mainControlUnit.setControlSignal(currentInstruction.getOpcode());

	if (mainControlUnit.getJump() == 1) {
		// Get jump address and shift left by 2
		string j = currentInstruction.getEncoding();
		j = shiftL1.shift(j.substr(6, string::npos));

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
			string immediate = currentInstruction.getEncoding().substr(18, string::npos);
			signExtend32.extend(immediate);
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
	string in1 = signExtend32.getOutput();
	string mux2_result = mux2.select(in0, in1, mainControlUnit.getALUSrc());

	// Set the operation of alu3 and then operate
	alu3.setOperation(ALUControl.getOutput());
	alu3.operate(registerFile.getDataR1(), mux2_result);

	if (mainControlUnit.getBranch() == 1) {
		// Get sign extended address and shift left by 2
		string beq_address = signExtend32.getOutput();
		beq_address = shiftL2.shiftAdd(beq_address);

		// Add PC+4 and address from beq to get target address
		alu2.operate(alu1.getOutput(), beq_address);


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


void MainProcessor::printProcessor() {

	stringstream s;

	s << "----------Fetch Stage---------- \n"
		<< pc->toString() << "\n\n"
		<< currentInstruction.getString() << "\n\n"
		<< alu1.toString() << "\n\n"


		<< "----------Decode Stage---------- \n"
		<< mux1.toString() << "\n\n"
		<< registerFile.toString() << "\n\n"

		<< mainControlUnit.toString() << "\n\n"

		<< shiftL1.toString() << "\n\n"
		<< signExtend32.toString() << "\n\n"


		<< "----------Execute Stage---------- \n"
		<< shiftL2.toString() << "\n\n"
		<< alu2.toString() << "\n\n"
		<< mux5.toString() << "\n\n"
		<< mux4.toString() << "\n\n"

		<< mux2.toString()<< "\n\n"
		<< alu3.toString() << "\n\n"
		<< ALUControl.toString() << "\n\n"


		<< "----------Memory Stage---------- \n"
		<< dataMem->printInputsAndOutput() << "\n\n"
		<< mux3.toString() << "\n\n";

	if (print_memory_contents) {
			s << dataMem->printDataMemory()
				<< registerMem.toString();
	}


	if (write_to_file && output_file.size() != 0) {
		// Write to a specified output file
		ofstream outfile {output_file};
		outfile << s.str() << endl;
		outfile.close();

	} else {
		// Print to command prompt
		cout << s.str() << endl;
	}
}
