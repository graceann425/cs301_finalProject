#include "SignExtend.h"

SignExtend::SignExtend()
{
	input = "";
	output = "";
}

string SignExtend::extendTo32(string value)
{
	input = value;

	string extend = "";
	if (value[0] == '0'){
		extend = "0000000000000000" + value;
	}
	else {
		extend = "1111111111111111" + value;
	}

	output = extend;
	return output;
}


string SignExtend::toString()
{
	stringstream s;

	s << "SIGN EXTEND 32 \n"
		<< "Input: " << input << "\n"
		<< "Output: " << output << "\n";

	return s.str();
}
