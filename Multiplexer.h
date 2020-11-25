#ifndef _MULTIPLEXER_H
#define _MULTIPLEXER_H

#include <string>
#include <sstream>

using namespace std;

class Multiplexer{
  public:
	   Multiplexer(string muxName);
	   ~Multiplexer() {};

	   // return a if controlSignal == 0, else return b
	   string select(string a, string b, int controlSignal);

     // get outout determined in select()
	   string getOutput();

     // return string of all variables associated with this object
     string toString();

  private:
	   string name;
     string inputA;
     string inputB;
     string output;
     int controlSignal;
};

#endif
