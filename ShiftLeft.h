#ifndef _SHIFTLEFT_H
#define _SHIFTLEFT_H

#include <string>
#include <sstream>

using namespace std;

class ShiftLeft{
    public:
	// give this object a name
	ShiftLeft(string objectName);
	~ShiftLeft() {};

	// Shift the binary number (value) left by 2
	string shift(string value);
	string shiftAdd(string value);

	// return all associated values of this unit
	string toString();

    private:
	string name;
  string shiftAmount;
  string input;
  string output;
};

#endif
