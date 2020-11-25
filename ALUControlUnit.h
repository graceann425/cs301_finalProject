#ifndef _ALUCONTROLUNIT_H
#define _ALUCONTROLUNIT_H

#include <string>
#include <sstream>

using namespace std;

class ALUControlUnit{
   public:
	ALUControlUnit();
	~ALUControlUnit() {};

// Return string representation of a 5-bit code that determines what the operation the ALU must do based on the instruction function field (5-0).
	string determineALUOperation(string ALUOperation, string func);

  string getOutput() { return output; };

	// return all values associated with this ALUControl unit
	string toString();

  private:
	// Store for the purpose of printing out info
	string ALUOp;    // Parameter from determineALUOperation()
	string function; // Parameter from determineALUOperation()
	string output; // Result from determineALUOperation()
};

#endif
