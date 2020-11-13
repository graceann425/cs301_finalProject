#include "ALU.h"

ALU::ALU() 
{
	ALUOperation = "0010";
}

string ALU::operate(string in1, string in2) 
{
	input1 = in1;
	input2 = in2;
	if (ALUOperation.equals("0010")) //add
		return add();
	else if (ALUOperation.equals("0110")) //subtract
		return sub();
	else if (ALUOperation.equals("0000")) //and
		return AND();
	else if (ALUOperation.equals("0001")) //or
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
	output = "00000000000000000000000000000000"
	for (int i = 0; i < input1.length(); i++)
	{
		if (input1[i] == '1' && input2[i] == '1')
			output[i] == 1;
	}
	return output; 
}

string ALU::OR()
{
	output = "00000000000000000000000000000000";
	for (int i = 0; i < input1.length(); i++)
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
	for (int i = 0; i < input1.length(); i++)
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
	for (int i = 0; i < input1.length(); i++)
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
	if (input1 < input2)
		output = 1;
	else
		output = 0;
	return output;
}
	
void ALU::printALU()
{
	cout << "Input1: " << input1 << endl;
	cout << "Input2: " << input2 << endl;
	cout << "ALU Operation: " << ALUOperation << endl;
	cout << "Output: " << output << endl; 
}