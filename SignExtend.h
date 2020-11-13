#ifndef _SIGNEXTEND_H
#define _SIGNEXTEND_H

class SignExtend{
    public:
	SignExtend(int amount);
	~SignExtend() {};

	// Extend the given value to the extendToAmount
	string extend(string value);

  string getOutput() {return output};

  void printSignExtend();

    private:
	int extendToAmount;
  string input;
  string output;

};

#endif
