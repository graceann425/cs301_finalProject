#include "ALU.h"

ALU::ALU()
{
	name = "";
	ALUOperation = "0010";
	input1 = "";
	input2 = "";
	output = "";
}

string ALU::operate(string in1, string in2)
{
	input1 = in1;
	input2 = in2;
	if (ALUOperation.compare("0010") == 0) //add
		return ADD();
	else if (ALUOperation.compare("0110") == 0) //subtract
		return SUBTRACT();
	else if (ALUOperation.compare("0000") == 0) //and
		return AND();
	else if (ALUOperation.compare("0001") == 0) //or
		return OR();
	else
		return setLessThan(); //set on less than (0111)
}

void ALU::setOperation(string ALUOp)
{
	ALUOperation = ALUOp;
}

string ALU::AND()
{
	output = "00000000000000000000000000000000";
	for (int i = 0; i < static_cast<int>(input1.length()); i++)
	{
		if (input1[i] == '1' && input2[i] == '1')
			output[i] == 1;
	}
	return output;
}

string ALU::OR()
{
	output = "00000000000000000000000000000000";
	for (int i = 0; i < static_cast<int>(input1.length()); i++)
	{
		if (input1[i] == '1' || input2[i] == '1')
			output[i] == 1;
	}
	return output;
}

string ALU::SUBTRACT()
{
	output = "00000000000000000000000000000000";
	int borrow = 0;
	for (int i = 0; i < static_cast<int>(input1.length()); i++)
	{
		if (input1[i] == '1' && borrow > 0){
			input1[i] = '0';
			borrow = borrow - 1;
		}
		if (input1[i] == '1' && input2[i] == '0')
			output[i] = '1';
		else if (input1[i] == '0' && input2[i] == '1')
			borrow = borrow + 1;
	}
	return output;
}

string ALU::ADD()
{
	output = "00000000000000000000000000000000";
	int carry = 0;
	for (int i = 0; i < static_cast<int>(input1.length()); i++)
	{
		if (input1[i] == '1' && input2[i] == '0' && carry == 0)
			output[i] = '1';
		else if (input1[i] == '0' && input2[i] == '1' && carry == 0)
			output[i] = '1';
		else if (input1[i] == '0' && input2[i] == '0' && carry == 1)
		{
			output[i] = '1';
			carry = 0;
		}
		else if (input1[i] == '1' && input2[i] == '1' && carry == 0)
			carry = 1;
		else if (input1[i] == '1' && input2[i] == '1' && carry == 1)
			output[i] = '1';
	}
	return output;
}

string ALU::setLessThan()
{
	// if (input1 < input2)
	// 	output = 1;
	// else
	// 	output = 0;
	return output;
}


void ALU::setName(string n)
{
	name = n;
}

string ALU::getOutput()
{
	return output;
}


string ALU::toString()
{
	stringstream s;

	s << name << "\n"
		<< "Input1: " << input1 << "\n"
		<< "Input2: " << input2 << "\n"
	  << "ALU Operation: " << ALUOperation << "\n"
	  << "Output: " << output << endl;

	return s.str();
}
