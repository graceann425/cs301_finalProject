#ifndef _MAINPROCESSOR_H
#define _MAINPROCESSOR_H

using namespace std;

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "ASMParser.h"
#include "Instruction.h"
#include "DataMemory.h"
#include "RegisterMemory.h"
#include "RegisterFile.h"
#include "PC.h"
#include "ALU.h"
#include "ALUControlUnit.h"
#include "ControlUnit.h"
#include "Multiplexer.h"
#include "ShiftLeft.h"
#include "SignExtend.h"
#include "NumberConverter.h"

class MainProcessor {
	public:
		MainProcessor(string config_filename);
		~MainProcessor();

		// Stages in an instruction execution
		bool fetch();
		void decode();
		void execute();
		void memory();
		void writeback();

		// Helper methods
		bool isIType(Opcode o) { return (o == ADDI || o == LW || o == SW || o == BEQ); };
		bool isJType(Opcode o) { return o == J; };
		bool isRtype(Opcode o) { return (o == ADD || o == SUB || o == SLT); };

		// Print or write to a file all the objects in this processor
		void printProcessor();

		// Reset the member variables in all the objects in this processor
		void resetContents();

		// Return true if the processor is in single_step mode.
		bool isSingleStep() { return output_mode.compare("single_step") == 0; };

	private:
		// Values obtained from config file
		string program_input;
		string memory_contents_input;
		string register_file_input;
		string output_mode;   // either to single_step or batch
		bool debug_mode;
		bool print_memory_contents;
		bool write_to_file;
		string output_file;
		ofstream outfile;

		int curInstrIdx; // The index of the current instruction
		string curAddress;

		string jumpAddress; // The current jump address; if none, set value to 0x400000

		// Classes and objects needed to run processor
		ASMParser* parser;
		vector<Instruction> instructions; // get from ASMParser
		Instruction currentInstruction;     // current instruction being processed
		DataMemory* dataMem;
		RegisterMemory registerMem;
		RegisterFile registerFile;
		PC* pc;
		ALU alu1, alu2, alu3;
		ALUControlUnit ALUControl;
		ControlUnit mainControlUnit;
		Multiplexer mux1, mux2, mux3, mux4, mux5;
		ShiftLeft shiftL1, shiftL2;
		SignExtend signExtend32;
};

#endif
