#include "Multiplexer.h"

//constructor
Multiplexer::Multiplexer()
{
	name = "";
	inputA = "";
	inputB = "";
	controlSignal = -1;
	output = "";
}

//select: if control signal is 0, outputs string a, otherwise, outputs string b
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

//getOutput: returns output
string Multiplexer::getOutput()
{
	return output;
}

//toString
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
