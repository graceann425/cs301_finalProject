#include "Multiplexer.h"

Multiplexer::Multiplexer()
{
	name = "";
	inputA = "";
	inputB = "";
	controlSignal = -1;
	output = "";
}

string Multiplexer::select(string a, string b, int cs)
{
	inputA = a;
	inputB = b;
	controlSignal = cs;

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

string Multiplexer::toString() {
	stringstream s;

	s << "MULTIPLEXER \t"
		<< name << "\n"
		<< "Input 0: " << inputA << "\n"
		<< "Input 1: " << inputB << "\n"
		<< "Control Signal: 0x" << to_string(controlSignal) << "\n"
		<< "Output: " << output << "\n";

	return s.str();
}
