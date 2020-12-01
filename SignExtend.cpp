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

	s << "SIGN EXTEND 32 "
		<< "\nInput: ";
		if (input.size() != 0)
		 	s << "0x" << NumberConverter::binaryToHex(input);

	s	<< "\nOutput: ";
	 	if (output.size() !=0)
			s << "0x" << NumberConverter::binaryToHex(output) << "\n";

	return s.str();
}


void SignExtend::reset()
{
	input = "";
	output = "";
}
