#include "ShiftLeft.h"

ShiftLeft::ShiftLeft()
{
	name = "";
	shiftAmount = 2;
	input = "";
	output = "";
}


string ShiftLeft::shift(string value)
{
	string shifted = "";
	// for (int i = shiftAmount; i < value.length(); i++)
	// {
	// 	string s(1, value[i]);
	// 	shifted.append(s);
	// }
	// for (int i = 0; i < shiftAmount; i++)
	// {
	// 	shifted.append('0');
	// }
	output = shifted;
	return output;
}


string ShiftLeft::shiftAdd(string value)
{
	// for (int i = 0; i < shiftAmount; i++)
	// {
	// 	value.append('0');
	// }
	output = value;
	return output;
}


string ShiftLeft::toString()
{
	stringstream s;

	s << "ShiftLeft: \n"
		<< "Name: " << name << "\n"
		<< "Input: " << input << "\n"
		<< "Output: " << output << "\n";

	return s.str();
}
