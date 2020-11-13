#include "SignExtend.h"

SignExtend::SignExtend(int amount)
{
	extendToAmount = amount;
}

string SignExtend::Extend(string value)
{
	string extend = "";
	if (value[0] == '0'){
		for(int i = 0; i < extendToAmount; i++)
			extend.append("0");
	}
	else{
		for(int i = 0; i < extendToAmount; i++)
			extend.append("1");
	}

	extend.append(value);
	return extend; 
}