#ifndef _MULTIPLEXER_H
#define _MULTIPLEXER_H

class Multiplexer{
  public:
	   Multiplexer(string muxName);
	   ~Multiplexer() {};

	   // return a if controlSignal == 0, else return b
	   string select(string a, string b, int controlSignal);

     // get outout determined in select()
	   string getOutput();

     // print all variables associated with this object
     void printMultiplexer();

  private:
	   string name;
     string inputA;
     string inputB;
     string output;
     int controlSignal;
};

#endif
