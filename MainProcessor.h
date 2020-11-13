#ifndef _MAINPROCESSOR_H
#define _MAINPROCESSOR_H

class MainProcessor{
	    public:
		MainProcessor(string config_filename);
		~MainProcessor() {};

		void fetch();

		void decode();

		void execute();

		void memory(string address, string data);

		void writeback(string data);

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
		Multiplexer mux1, mux2, mux3, mux4, mux5;
		ShiftLeft shiftL1, shiftL2;
		SignExtend signExtend32;
	};

#endif
