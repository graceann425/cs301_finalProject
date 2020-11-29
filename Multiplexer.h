#ifndef _MULTIPLEXER_H
#define _MULTIPLEXER_H

#include <string>
#include <sstream>

using namespace std;

class Multiplexer{
  public:
	   Multiplexer();
	   ~Multiplexer() {};

	   // return a if controlSignal == 0, else return b
	   string select(string a, string b, int cs);

     // Set the name of this Multiplexer
     void setName(string muxName) {	name = muxName; };

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
