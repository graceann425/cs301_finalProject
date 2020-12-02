#include "ControlUnit.h"

ControlUnit::ControlUnit()
{
  RegDest = 0;
  Jump = 0;
  Branch = 0;
  MemRead = 0;
  MemToReg = 0;
  ALUOp = "00";
  MemWrite = 0;
  ALUSrc = 0;
  RegWrite = 0;
  op_binary = "";
}


void ControlUnit::setControlSignal(Opcode op, string op_bi)
{
  o = op;
  op_binary = op_bi;
  // If R-Type
  if (op == ADD || op == SUB || op == SLT) {
    RegDest = 1;
    Jump = 0;
    Branch = 0;
    MemRead = 0;
    MemToReg = 0;
    ALUOp = "10";
    MemWrite = 0;
    ALUSrc = 0;
    RegWrite = 1;

  } else if (op == LW) {
    RegDest = 0;
    Jump = 0;
    Branch = 0;
    MemRead = 1;
    MemToReg = 1;
    ALUOp = "00";
    MemWrite = 0;
    ALUSrc = 1;
    RegWrite = 1;

  } else if (op == SW) {
    RegDest = 0;
    Jump = 0;
    Branch = 0;
    MemRead = 0;
    MemToReg = 0;
    ALUOp = "00";
    MemWrite = 1;
    ALUSrc = 1;
    RegWrite = 0;

  } else if (op == ADDI) {
    RegDest = 0;
    Jump = 0;
    Branch = 0;
    MemRead = 0;
    MemToReg = 0;
    ALUOp = "00";
    MemWrite = 0;
    ALUSrc = 1;
    RegWrite = 0;

  } else if (op == BEQ) {
    RegDest = 0;
    Jump = 0;
    Branch = 1;
    MemRead = 0;
    MemToReg = 0;
    ALUOp = "01";
    MemWrite = 0;
    ALUSrc = 0;
    RegWrite = 0;

  } else if (op == J) {
    RegDest = 0;
    Jump = 1;
    Branch = 0;
    MemRead = 0;
    MemToReg = 0;
    ALUOp = "00";
    MemWrite = 0;
    ALUSrc = 0;
    RegWrite = 0;
  }
}


string ControlUnit::toString()
{
  stringstream s;

  s << "CONTROL UNIT \n"
    << "Opcode: ";
    if (op_binary.size() != 0)
        s << "0x" << NumberConverter::binaryToHex("00"+op_binary);
  s << "\nRegDest: 0x" << to_string(RegDest)
    << "\nJump: 0x" << to_string(Jump)
    << "\nBranch: 0x" << to_string(Branch)
    << "\nMemRead: 0x" << to_string(MemRead)
    << "\nMemToReg: 0x" << to_string(MemToReg)
    << "\nALUOp: 0x" << NumberConverter::binaryToHex("00" + ALUOp)
    << "\nMemWrite: 0x" << to_string(MemWrite)
    << "\nALUSrc: 0x" << to_string(ALUSrc)
    << "\nRegWrite: 0x" << to_string(RegWrite) << "\n";

  return s.str();
}


void ControlUnit::reset()
{
  RegDest = 0;
  Jump = 0;
  Branch = 0;
  MemRead = 0;
  MemToReg = 0;
  ALUOp = "00";
  MemWrite = 0;
  ALUSrc = 0;
  RegWrite = 0;
  op_binary = "";
}
