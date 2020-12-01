#include "ALU.h"
#include <iostream>
ALU::ALU()
{
	name = "";
	ALUOperation = "0010";
	input1 = "";
	input2 = "";
	input2_sub = "";
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
	input2_sub = input2;

	// Invert input2
	for (int i = 0; i < static_cast<int>(input2.length()); i++)
	{
		if (input2[i] == '1') {
			input2[i] = '0';
		} else {
			input2[i] = '1';
		}
	}

	// input2 + 1
	int idx = input2.size()-1;
	while (idx >= 0) {
		if (input2[idx] == '1') {
			input2[idx] = '0';
			idx--;
		} else {
			input2[idx] = '1';
			break;
		}
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

	input1 = NumberConverter::binaryToHex(input1);

	// Revert from two's complement
	if (ALUOperation.compare("0110")==0 || ALUOperation.compare("0111")==0 )
		input2 = input2_sub;

	input2 = NumberConverter::binaryToHex(input2);
	output = NumberConverter::binaryToHex(output);

	return output;
}

string ALU::setLessThan()
{
	SUBTRACT();

	if (output.at(0) == '0')
		return "0";

	return "1";
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

	s << name
		<< "\nInput1: ";
		if (input1.size() != 0)
		 	s << "0x" << input1;

	s	<< "\nInput2: ";
		if (input2.size() != 0)
		 s << "0x" << input2;

	s << "\nALU Operation: 0x" << NumberConverter::binaryToHex(ALUOperation)
	  << "\nOutput: ";
		if (output.size() != 0)
			s << "0x" << output << endl;

	return s.str();
}


void ALU::reset()
{
	ALUOperation = "0010";
	input1 = "";
	input2 = "";
	input2_sub = "";
	output = "";
}
