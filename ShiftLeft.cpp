#include "ShiftLeft.h"

ShiftLeft::ShiftLeft(string objectName, int amount)
{
	name = objectName;
	shiftAmount = amount;
}

string ShiftLeft::shift(string value)
{
	string shifted = "";
	for (int i = shiftAmount; i < value.length(); i++)
	{
		string s(1, value[i]);
		shifted.append(s);
	}
	for (int i = 0; i < shiftAmount; i++)
	{
		shifted.append('0');
	}
	return shifted;
}

string ShiftLeft::shiftAdd(string value)
{
	for (int i = 0; i < shiftAmount; i++)
	{
		value.append('0');
	}
	return value; 
}

string ShiftLeft::getName()
{
	return name; 
}