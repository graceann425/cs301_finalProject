#ifndef _SIGNEXTEND_H
#define _SIGNEXTEND_H

#include <string>
#include <sstream>

using namespace std;

class SignExtend{
  public:
	   SignExtend();
	   ~SignExtend() {};

	   // Extend the given value to the extendToAmount
	   string extend(string value);

     string getOutput() { return output; };

     // Returns all values associated with this object
     string toString();

  private:
	   int extendToAmount;
     string input;
     string output;
};

#endif
