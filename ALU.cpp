#include "ALU.h"
#include <iostream>

//constructor (defaults to add and all inputs as 0)
ALU::ALU()
{
	name = "";
	ALUOperation = "0010";
	input1 = "0";
	input2 = "0";
	output = "0";
}

//operate: takes in two input strings and calls the ALU operation
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

//setOperation: sets ALU operation code
void ALU::setOperation(string ALUOp)
{
	ALUOperation = ALUOp;
}

//AND: and of two inputs
string ALU::AND()
{
	output = "00000000000000000000000000000000"; //starts output as all zeros
	for (int i = 0; i < static_cast<int>(input1.length()); i++) 
	{
		if (input1[i] == '1' && input2[i] == '1') 
			output[i] = '1'; //changes output to 1 if both inputs are 1
	}
	return output;
}

//OR: or of two inputs 
string ALU::OR()
{
	output = "00000000000000000000000000000000"; //starts output as all zeros
	for (int i = 0; i < static_cast<int>(input1.length()); i++)
	{
		if (input1[i] == '1' || input2[i] == '1')
			output[i] = '1'; //changes output to 1 if either input is 1
	}
	return output;
}

//SUBTRACT: subtracts input 2 from input 1 (adds input 1 and twos complement of input 2)
string ALU::SUBTRACT()
{
	for (int i = 0; i < static_cast<int>(input2.length()); i++)
	{
		if (input2[i] == '1')
			input2[i] = '0';
		else
			input2[i] = '1';
	}
	return ADD();
}

//ADD: adds input 1 and input 2
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

//setLessThan: if input 1 < input 2, output = 1, otherwise output = 0
string ALU::setLessThan()
{
	output = "00000000000000000000000000000000"; //set default output to 0
	int less = 0;
	for (int i = static_cast<int>(input1.length()-1); i >= 0; i--)
	{
		if (input1[i] == '1' && input2[i] == '0')
			less = 1;
		if (input1[i] == '0' && input2[i] == '1' && less == 0)
			output = "00000000000000000000000000000001";
	}
	return output;
}

//setName
void ALU::setName(string n)
{
	name = n;
}

//getOutput: returns output
string ALU::getOutput()
{
	return output;
}

//toString
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
