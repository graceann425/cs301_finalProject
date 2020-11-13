#include "Multiplexer.h"

Multiplexer::Multiplexer(string muxName)
{
	name = muxName;
	inputA = "";
	inputB = "";
	output = "";
}

string Multiplexer::select(string a, string b, int controlSignal)
{
	inputA = a;
	inputB = b;

	if (controlSignal == 0) {
		output = a;
		return a;
	} else {
		output = b;
		return b;
	}
}

string Multiplexer::getOutput()
{
	return output;
}

void Multiplexer::printMultiplexer() {
	
}
