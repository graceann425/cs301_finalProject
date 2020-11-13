#ifndef _SHIFTLEFT_H
#define _SHIFTLEFT_H

class ShiftLeft{
    public:
	// indicate the amount to shift and give this object a name
	ShiftLeft(string objectName, int amount);
	~ShiftLeft() {};

	// Shift the binary number (value) left by the designated shift amount
	string shift(string value);
	string shiftAdd(string value);

	// Get name of this object
	string getName(); 

    private:
	string name;
	int shiftAmount;
};

#endif
