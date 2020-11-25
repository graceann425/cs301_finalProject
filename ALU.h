#ifndef _ALU_H
#define _ALU_H

#include <string>
#include <sstream>

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
	string SUBTRACT();
	string ADD();
	string setLessThan();

  // set name
  void setName(string n);

  // get output from computations
  string getOutput();

	// return string of all values associated with this ALU
	string toString();

   private:
	// Need to store for printing purposes
  string name;
	string input1;
	string input2;
	string ALUOperation;
	string output;
};

#endif
