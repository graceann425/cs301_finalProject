#include "ALUControlUnit.h"

//constructor
ALUControlUnit::ALUControlUnit() {
	ALUOp = "";
	function = "";
	output = "";
}

//determineALUOperation: sets ALUOp based on 6 digit binary op code
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

//to string
string ALUControlUnit::toString()
{
	stringstream s;

	s << "ALU Control Unit "
    << "\nALU Operation Code: ";
		if (ALUOp.size() !=0)
		 	s << "0x" << NumberConverter::binaryToHex("00" + ALUOp);

	s << "\nFunction code: ";
		if (function.size() !=0)
		 	s << "0x" << NumberConverter::binaryToHex("00" + function);

	s << "\nALU Operation: ";
	 	if (output.size() !=0)
			s << "0x" << NumberConverter::binaryToHex(output) << endl;

	return s.str();
}


void ALUControlUnit::reset()
{
	ALUOp = "";
	function = "";
	output = "";
}
