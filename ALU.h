#ifndef _ALU_H
#define _ALU_H

#include <string>

using namespace std;

class ALU{
   public: 
	// By default, have constructor set operation to add
	ALU();
	~ALU() {};

	// Runs the operation on the two inputs and returns an output
	string operate(string in1, string in2);
	
	// Sets the current operation of this ALU. The parameter ALUOp is the output of the ALU Control Unit, so it’s a number in binary representation
	void setOperation(string ALUOp);
	
	// All operations the ALU can do. Method operate() will call one of these depending on the current value of ALUOperation.
	string AND();
	string OR();
	string subtract();
	string add();
	string setLessThan();
	
	// print all values associated with this ALU
	void printALU();

   private: 
	// Need to store for printing purposes
	int input1;
	int input2;
	string ALUOperation;
	string output;
};

#endif
