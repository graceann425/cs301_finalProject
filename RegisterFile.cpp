
#include <iostream>
#include "RegisterFile.h"

RegisterFile::RegisterFile() {
  rm = nullptr;
  R1 = -1;
  R2 = -1;
  writeRegister = -1;
  dataR1 = "";
  dataR2 = "";
}


void RegisterFile::writeData(string data) {
  rm->setRegisterData(writeRegister, data);
}


string RegisterFile::getDataR1() {
  dataR1 = rm->getRegister(R1);
  return dataR1;
}


string RegisterFile::getDataR2() {
  dataR2 = rm->getRegister(R2);
  return dataR2;
}


string RegisterFile::toString() {
  stringstream s ;

  s << "REGISTER FILE \n"
    << "In \n"
    << "R1: " << to_string(R1) << "\n"
    << "R2: " << to_string(R2) << "\n"
    << "Write Register: " << to_string(writeRegister) << "\n"
    << "Out \n"
    << "R1 Data: 0x" << dataR1 << "\n"
    << "R2 Data: 0x" << dataR2 << "\n";

  return s.str();
}
