#include "SignExtend.h"

SignExtend::SignExtend()
{
	extendToAmount = 32;
	input = "";
	output = "";
}

string SignExtend::extend(string value)
{
	input = value;

	string extend = "";
	if (value[0] == '0'){
		for(int i = 0; i < extendToAmount; i++)
			extend.append("0");
	}
	else{
		for(int i = 0; i < extendToAmount; i++)
			extend.append("1");
	}

	output = extend.append(value);
	return output;
}


string SignExtend::toString()
{
	stringstream s;

	s << "Sign Extend 32: \n"
		<< "Input: " << input << "\n"
		<< "Output: " << output << "\n";

	return s.str();
}
