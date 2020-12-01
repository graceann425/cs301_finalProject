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


string Multiplexer::toString()
{
	stringstream s;

	s << "MULTIPLEXER \t"
		<< name
		<< "\nInput 0: ";
		if (inputA.size() != 0)
		  s << "0x" << inputA;

	s << "\nInput 1: ";
	 	if (inputB.size() != 0)
			s << "0x" << inputB;

	s	<< "\nControl Signal: ";
		if (controlSignal != -1)
			s << "0x" << to_string(controlSignal);

	s	<< "\nOutput:  ";
		if (output.size() != 0)
			s << "0x" << output << "\n";

	return s.str();
}


void Multiplexer::reset()
{
	inputA = "";
	inputB = "";
	controlSignal = -1;
	output = "";
}
