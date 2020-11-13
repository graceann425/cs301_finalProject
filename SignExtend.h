#ifndef _SIGNEXTEND_H
#define _SIGNEXTEND_H

class SignExtend{
    public:
	SignExtend(int amount);
	~SignExtend() {};

	// Extend the given value to the extendToAmount
	string extend(string value);

    private:
	int extendToAmount;

};

#endif
