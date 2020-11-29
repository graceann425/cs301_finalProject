#include "ShiftLeft.h"

ShiftLeft::ShiftLeft()
{
	name = "";
	input = "";
	output = "";
}


string ShiftLeft::shift(string value)
{
	string shifted = "";

	shifted = value.substr(2,string::npos) + "00";
	output = shifted;
	return output;
}


string ShiftLeft::shiftAdd(string value)
{
	output = value + "00";
	return output;
}


string ShiftLeft::toString()
{
	stringstream s;

	s << "SHIFT LEFT 2 \t "
		<< name << "\n"
		<< "Input: " << input << "\n"
		<< "Output: " << output << "\n";

	return s.str();
}
