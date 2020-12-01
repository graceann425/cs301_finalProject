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
	if (a.size() == 32) {
		inputA = NumberConverter::binaryToHex(a);
	} else {
		inputA = a;
	}

	if (b.size() == 32) {
		inputB = NumberConverter::binaryToHex(b);
	} else {
		inputB = b;
	}

	controlSignal = cs;

	if (controlSignal == 0) {
		output = inputA;
		return output;
	} else {
		output = inputB;
		return output;
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
		<< "Input 0: 0x" << inputA << "\n"
		<< "Input 1: 0x" << inputB << "\n"
		<< "Control Signal: 0x" << to_string(controlSignal) << "\n"
		<< "Output: 0x" << output << "\n";

	return s.str();
}
