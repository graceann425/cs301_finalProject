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
	input = value;
	string shifted = "";
	shifted = value.substr(2,string::npos) + "00";
	output = shifted;
	return output;
}

//shiftAdd: shifts binary string left by 2 without removing 2 most significant bits
string ShiftLeft::shiftAdd(string value)
{
	input = value;
	output = value + "00";
	return output;
}

//toString
string ShiftLeft::toString()
{
	stringstream s;
	//cout << "made it into shiftLeft\n";
	s << "SHIFT LEFT 2 \t "
		<< name
		<< "\nInput: ";
		if (input.size() != 0) {
			if (input.size() == 26) {
				// char c = input.at(0);
				// if (c == '1') {
				// 	input = "11" + input;
				// } else {
				// 	input = "00" + input;
				// }
				s << "0x" << NumberConverter::binaryToHex("00"+input);
			} else {
				s << "0x" << NumberConverter::binaryToHex(input);
			}
		}
	s	<< "\nOutput: ";
		if (output.size() != 0)
			s << "0x" << NumberConverter::binaryToHex(output) << "\n";
		//cout << "Made it past shiftLeft\n";
	return s.str();
}


void ShiftLeft::reset()
{
	input = "";
	output = "";
}
