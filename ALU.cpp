#include "ALU.h"
#include <iostream>
ALU::ALU()
{
	name = "";
	ALUOperation = "0010";
	input1 = "0";
	input2 = "0";
	output = "0";
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
			output[i] = '1';
	}
	return output;
}

string ALU::OR()
{
	output = "00000000000000000000000000000000";
	for (int i = 0; i < static_cast<int>(input1.length()); i++)
	{
		if (input1[i] == '1' || input2[i] == '1')
			output[i] = '1';
	}
	return output;
}

string ALU::SUBTRACT()
{
	for (int i = 0; i < static_cast<int>(input1.length()); i++)
	{
		if (input1[i] == '1')
			input1[i] = '0';
		else
			input1[i] = '1';
	}
	return ADD();
}

string ALU::ADD()
{
	output = "00000000000000000000000000000000";
	int carry = 0;
	for (int i = static_cast<int>(input1.length()-1); i >= 0 ; i--)
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
		<< "Input1: " << hex << "0x" << input1 << "\n"
		<< "Input2: " << hex << "0x" << input2 << "\n"
	  << "ALU Operation: " << "0x" << ALUOperation << "\n"
	  << "Output: " << "0x" << output << endl;

	return s.str();
}
