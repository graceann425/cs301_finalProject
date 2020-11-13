#include "SignExtend.h"

SignExtend::SignExtend(int amount)
{
	extendToAmount = amount;
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


void SignExtend::printSignExtend() {

}
