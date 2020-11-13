

MainProcessor::MainProcessor(string config_filename)
{
	myLabelAddress = 0x400000;

	ifstream in;
	in.open(config_filename.c_str());
	string line;

//program input file
	getline(in, line);
	string::size_type idx = line.find('=');
	line = line.substr(idx, line.length());
	int p = 0;
	while (p < line.length() && isWhitespace(line.at(p)))
		p++;
		while (p < len && !isWhitespace(line.at(p))){
		string programInput = "";
		programInput = programInput + line.at(p);
		p++;
	}

//memory contents file
	getline(in, line);
	idx = line.find('=');
	line = line.substr(idx, line.length());
	int p = 0;
	while (p < line.length() && isWhitespace(line.at(p)))
		p++;
		while (p < len && !isWhitespace(line.at(p))){
		string memoryContents = "";
		memoryContents = memoryContents + line.at(p);
		p++;
	}

//register input file
	getline(in, line);
	idx = line.find('=');
	line = line.substr(idx, line.length());
	int p = 0;
	while (p < line.length() && isWhitespace(line.at(p)))
		p++;
		while (p < len && !isWhitespace(line.at(p))){
		string registerInput = "";
		registerInput = registerInput + line.at(p);
		p++;
	}

//output mode
	getline(in, line);
	idx = line.find('=');
	line = line.substr(idx, line.length());
	int p = 0;
	while (p < line.length() && isWhitespace(line.at(p)))
		p++;
		while (p < len && !isWhitespace(line.at(p))){
		string output_mode = "";
		output_mode = output_mode + line.at(p);
		p++;
	}

//debug mode
	getline(in, line);
	idx = line.find('=');
	line = line.substr(idx, line.length());
	int p = 0;
	while (p < line.length() && isWhitespace(line.at(p)))
		p++;
		while (p < len && !isWhitespace(line.at(p))){
		string debug = "";
		debug = debug + line.at(p);
		p++;
	}
	if (debug.equals("true"))
		debug_mode = true;
	else
		debug_mode = false;

//print memory contents mode
	getline(in, line);
	idx = line.find('=');
	line = line.substr(idx, line.length());
	int p = 0;
	while (p < line.length() && isWhitespace(line.at(p)))
		p++;
		while (p < len && !isWhitespace(line.at(p))){
		string memContents = "";
		memContents = memContents + line.at(p);
		p++;
	}
 	if (memContents.equals("true"))
		print_memory_contents = true;
	else
		print_memory_contents = false;

//output file
	getline(in, line);
	idx = line.find('=');
	line = line.substr(idx, line.length());
	int p = 0;
	while (p < line.length() && isWhitespace(line.at(p)))
		p++;
		while (p < len && !isWhitespace(line.at(p))){
		string output_file = "";
		output_file = output_file + line.at(p);
		p++;
	}

//write to file mode
	getline(in, line);
	idx = line.find('=');
	line = line.substr(idx, line.length());
	int p = 0;
	while (p < line.length() && isWhitespace(line.at(p)))
		p++;
		while (p < len && !isWhitespace(line.at(p))){
		string fileWrite = "";
		fileWrite = fileWrite + line.at(p);
		p++;
	}
	if (fileWrite.equals("true"))
		write_to_file = true;
	else
		write_to_file = false;

	registerMem.readFileMemory(registerInput);
	dataMem(memoryContents);
	parser(programInput);

}


void MainProcessor::fetch()
{
	 // Get string address and convert to int (hex)
	string address = pc.getAddress();
	int int_address = stoi(address, nullptr, 16);

	// Fetch the right instruction within instruction vector
	int idx =  (int_address - 0x400000)/4;
	currentInstruction = instructions.at(idx);

	// Update address to next instruction
	alu1.operate(address, 4);
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
		if (result.equals("0")) {
			registerFile.readWriteRegister(currentInstruction.getRT());
		} else {
			registerFile.readWriteRegister(currentInstruction.getRD());
		}

		// Determine the instruction type
		Opcode o = currentInstruction.getOpcode();
		InstType type = opcodes.getInstType(o);

		// For I-Type
		if (type == ITYPE) {
			// Sign extend from 16 to 32 bits
			string immediate = currentInstruction.getEncoding().substr(18, string::npos);
			signExtend32.extend(immediate);
		}
		// For R-Type
		else if (type == RTYPE) {
			string func = currentInstruction.substr(27, string::npos);
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

		if (alu3.getOutput().equals("0")) {
			// If beq condition is false
			mux5_result = mux5.select(alu1.getOutput(), alu2.getOutput(), 0);
		} else {
			// If beq condition is true
			mux5_result = mux5.select(alu1.getOutput(), alu2.getOutput(), 1);
		}

		// Select address and write it back to PC
		string mux4_result = mux4.select(mux5_result, jumpAddress, mainControlUnit.getJump());
		pc.setAddress(mux4_result);
	}
}
