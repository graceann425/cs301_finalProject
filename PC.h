#ifndef __PC_H__
#define __PC_H__

using namespace std;

#include <string>
#include <sstream>

class PC {
  public:
    PC() {};
    PC(string address) { myAddress = address; };
    ~PC() {};

	  // Obtain current address of PC
    string getAddress() { return myAddress; };

    // Set current address of PC
    void setAddress(string address) { myAddress = address; };

    // return contents of PC
    string toString();

  private:
    string myAddress;
};

#endif
