#include "ShiftLeft.h"

//constructor
ShiftLeft::ShiftLeft()
{
	name = "";
	input = "";
	output = "";
}

//shiftLeft: shifts binary string left by 2 
//(removes two most significant bits and adds two zeros in the least significant bits)
string ShiftLeft::shift(string value)
{
	string shifted = "";
	shifted = value.substr(2,string::npos) + "00";
	output = shifted;
	return output;
}

//shiftAdd: shifts binary string left by 2 without removing 2 most significant bits
string ShiftLeft::shiftAdd(string value)
{
	output = value + "00";
	return output;
}

//toString
string ShiftLeft::toString()
{
	stringstream s;

	s << "SHIFT LEFT 2 \t "
		<< name << "\n"
		<< "Input: " << input << "\n"
		<< "Output: " << output << "\n";

	return s.str();
}
