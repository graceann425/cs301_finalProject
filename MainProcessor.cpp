

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

/*Read the configuration file and initialize all private member variables.
By the end of the constructor, DataMemory and RegisterMemory will have read their files and stored their memory.
ASMParser will have also gone through all the instructions from the asm file.
Copy ASMParser’s vector of instructions into the local member variable vector<Instruction> instructions.*/

void MainProcessor::fetch()
{
	 // Get string address and convert to int (hex)
	string address = pc.getAddress();
	int int_address = toi(address, nullptr, 16);

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


void MainProcessor::execute()
{

}
