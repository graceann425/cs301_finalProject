#include "ALUControlUnit.h"

ALUControlUnit::ALUControlUnit() {
	ALUOp = -1;
	function = "";
	output = "";
}

string ALUControlUnit::determineALUOperation(int ALUOperation, string func)
{
	ALUOp = ALUOperation;
	function = func;
	if (ALUOp.equals("10"))
	{
		if (func.equals("100000"))
			output = "0010" //add
		else if (func.equals("100010"))
			output = "0110" //subtract
		else if (func.equals("100100"))
			output = "0000" //and
		else if (func.equals("100101"))
			output = "0001" //or
		else
			output = "0111" //set on less than
	}
	else if (ALUOp.equals("01"))
	{
		output = "0110" //subtract for beq
	}
	else
	{
		output = "0010" //add for lw or sw
	}

}

void ALUControlUnit::printALUControlUnit()
{
	cout << "ALU Operation Code: " << ALUOp << endl;
	cout << "Function code: " << function << endl;
	cout << "ALU Operation: " << output << endl;
}
