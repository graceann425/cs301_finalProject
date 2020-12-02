#ifndef __CONTROLUNIT_H__
#define __CONTROLUNIT_H__

#include <string>
#include <sstream>
#include "Opcode.h"
#include "NumberConverter.h"

using namespace std;

class ControlUnit{
  public:
	   // Initialize all control signals to 0
	   ControlUnit();
	   ~ControlUnit() {};

     // Given an opcode, set the value of the corresponding control signals to 1 or 0
	   void setControlSignal(Opcode op);

	   // Getters for all control signals
	   int getRegDest() { return RegDest; };
	   int getJump() { return Jump; };
     int getBranch() { return Branch; };
     int getMemRead() { return MemRead; };
     int getMemToReg() { return MemToReg; };
     string getALUOp() { return ALUOp; };
     int getMemWrite() { return MemWrite; };
     int getALUSrc() { return ALUSrc; };
     int getRegWrite() { return RegWrite; };

	   // Print the state of all the control signals
     string toString();

     // Reset the value of all member variables
     void reset();

   private:
     Opcode o;
     // The different control signals available
     int RegDest;
     int Jump;
     int Branch;
     int MemRead;
     int MemToReg;
     string ALUOp;
     int MemWrite;
     int ALUSrc;
     int RegWrite;

};

#endif
