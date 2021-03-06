#ifndef _SIGNEXTEND_H
#define _SIGNEXTEND_H

#include <string>
#include <sstream>
#include "NumberConverter.h"

using namespace std;

class SignExtend{
  public:
	   SignExtend();
	   ~SignExtend() {};

	   // Extend the given value to the extendToAmount
	   string extendTo32(string value);

     string getOutput() { return output; };

     // Returns all values associated with this object
     string toString();

     // Reset the value of all the member variables
     void reset();

  private:
     string input;
     string output;
};

#endif
