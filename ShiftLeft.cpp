#include "ShiftLeft.h"

ShiftLeft::ShiftLeft()
{
	name = "";
	input = "";
	output = "";
}


string ShiftLeft::shift(string value)
{
	input = value;
	string shifted = "";

	shifted = value.substr(2,string::npos) + "00";
	output = shifted;
	return output;
}


string ShiftLeft::shiftAdd(string value)
{
	input = value;
	output = value + "00";
	return output;
}


string ShiftLeft::toString()
{
	stringstream s;

	s << "SHIFT LEFT 2 \t "
		<< name
		<< "\nInput: ";
		if (input.size() != 0) {
			if (input.size() == 26) {
				char c = input.at(0);
				input = "" + c + c + input;
				s << "0x" << NumberConverter::binaryToHex(input);
			} else {
				s << "0x" << NumberConverter::binaryToHex(input);
			}
		}
	s	<< "\nOutput: ";
		if (output.size() != 0)
			s << "0x" << NumberConverter::binaryToHex(output) << "\n";

	return s.str();
}


void ShiftLeft::reset()
{
	input = "";
	output = "";
}
