#ifndef _ALUCONTROLUNIT_H
#define _ALUCONTROLUNIT_H

#include <string>

using namespace std;

class ALUControlUnit{
   public:
	ALUControlUnit();
	~ALUControlUnit() {};

// Return string representation of a 5-bit code that determines what the operation the ALU must do based on the instruction function field (5-0).
	string determineALUOperation(int ALUOperation, string func);

  string getOutput() { return output };

	// print all values associated with this ALUControl unit
	void printALUControlUnit();

  private:
	// Store for the purpose of printing out info
	int ALUOp;    // Parameter from determineALUOperation()
	string function; // Parameter from determineALUOperation()
	string output; // Result from determineALUOperation()
};

#endif
