

MainProcessor(string config_filename) 
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

void fetch() 
{
	string address = pc.getAddress();
	alu1.operate(address, 4);
	//IDK what I'm doing here....
	currentInstruction = instructions[address];

}
/*Use the current address from PC pc to select the appropriate current instruction from the instruction vector. 
Then take the pc address and load it into ALU alu1 alongside 4 to increment the address.*/

 private:
		// Values obtained from config file
		string output_mode;   // either to single_step or batch
		boolean debug_mode;
		boolean print_memory_contents;
		boolean write_to_file; 
		string output_file;  

		string jumpAddress; // The current jump address; if none, set value to 0x400000

		// Classes and objects needed to run processor
		ASMParser parser;
		vector<Instruction> instructions; // get from ASMParser
		Instruction currentInstruction;     // current instruction being processed
		DataMemory dataMem;
		RegisterMemory registerMem;
		RegisterFile registerFile;
		PC pc;
		ALU alu1, alu2, alu3;
		ALUControlUnit ALUControl;
		controlUnit mainControlUnit;
		multiplexer mux1, mux2, mux3, mux4, mux5;
		shiftLeft shiftL1, shiftL2;
		signExtend signExtend32;
