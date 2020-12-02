#include "SignExtend.h"

//constructor
SignExtend::SignExtend()
{
	input = "";
	output = "";
}

//extendTo32: extends string value by adding to the most significant bits
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

//toString
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
