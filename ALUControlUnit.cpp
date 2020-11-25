#include "ALUControlUnit.h"

ALUControlUnit::ALUControlUnit() {
	ALUOp = -1;
	function = "";
	output = "";
}

string ALUControlUnit::determineALUOperation(string ALUOperation, string func)
{
	ALUOp = ALUOperation;
	function = func;
	if (ALUOp.compare("10") == 0)
	{
		if (func.compare("100000") == 0){
			output = "0010"; //add
		} else if (func.compare("100010") == 0){
			output = "0110"; //subtract
		} else if (func.compare("100100") == 0){
			output = "0000"; //and
		} else if (func.compare("100101") == 0){
			output = "0001"; //or
		} else{
			output = "0111"; //set on less than
		}
	}
	else if (ALUOp.compare("01") == 0)
	{
		output = "0110"; //subtract for beq
	}
	else
	{
		output = "0010"; //add for lw or sw
	}
	return output;
}

string ALUControlUnit::toString()
{
	stringstream s;

	s << "ALU Control Unit \n"
    << "ALU Operation Code: " << ALUOp << endl
	  << "Function code: " << function << endl
	  << "ALU Operation: " << output << endl;

	return s.str();
}
