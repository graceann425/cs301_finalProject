#ifndef __CONTROLUNIT_H__
#define __CONTROLUNIT_H__


class ControlUnit{
  public:
	   // Initialize all control signals to 0
	   ControlUnit();
	   ~ControlUnit() {};

     // Given an opcode, set the value of the corresponding control signals to 1 or 0
	   void setControlSignal(Opcode op) {};

	   // Getters for all control signals
	   int getRegDest();
	   int getJump();
     int getBranch();
     int getMemRead();
     int getMemToReg();
     string getALUOp();
     int getMemWrite();
     int getALUSrc();
     int getRegWrite();

	   // Print the state of all the control signals
     string toString();

   private:
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
