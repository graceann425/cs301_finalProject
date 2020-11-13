#include "Multiplexer.h"

Multiplexer::Multiplexer(string muxName)
{
	name = muxName;
}
		
string Multiplexer::select(string a, string b, int controlSignal)
{
	if (controlSignal == 0)
		return a;
	else
		return b;
}

string Multiplexer::getName()
{
	return name;
}