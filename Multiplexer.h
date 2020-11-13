#ifndef _MULTIPLEXER_H
#define _MULTIPLEXER_H

class Multiplexer{
    public:
	Multiplexer(string muxName);
	~Multiplexer() {};
		
	// return a if controlSignal == 0, else return b
	string select(string a, string b, int controlSignal);

	// get the name associated with this object instance
	string getName();

    private: 
	string name;
};

#endif

