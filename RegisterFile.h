#ifndef __REGISTERFILE_H__
#define __REGISTERFILE_H__

using namespace std;

#include <string>
#include "RegisterMemory.h"

class RegisterFile {
  public:
    RegisterFile();
    ~RegisterFile() {};

    // Store a reference to the register memory
    void addRegisterMemory(RegisterMemory* regMem) { rm = regMem; };

		// Add first register
    void readR1(int reg1) { R1 = reg1; };
    // Add second register
    void readR2(int reg2) { R2 = reg2; };

    // Add a write register (if needed)
    void readWriteRegister(int WReg) { writeRegister = WReg; };

    // Data to be written into the write register
    void writeData(string data);

    // Get the data in R1
    string getDataR1();
    // Get the data in R2
    string getDataR2();

    // return string of all registers and values currently stored
    string toString();

  private:
    RegisterMemory* rm;
    int R1;
    int R2;
    int writeRegister;

    string dataR1;
    string dataR2;
};

#endif
