#ifndef __REGISTERMEMORY_H__
#define __REGISTERMEMORY_H__

using namespace std;

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class RegisterMemory {
  public:
    RegisterMemory() {};
    ~RegisterMemory() {};

    // Read the register memory file and store the values
    void readFileMemory(string filename);

    // Obtain the data of the specified register
    string getRegister(int regNum);

    // Load given data into the specified register
    void setRegisterData(int regNum, string data);

    // Print the current state of all registers
    void printRegisterMemory();

  private:
    string registerArray[32];
};

#endif
