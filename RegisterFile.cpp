
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
  return rm->getRegister(R1);
}


string RegisterFile::getDataR2() {
  return rm->getRegister(R2);
}


string RegisterFile::toString() {
  stringstream s ;

  s << "REGISTER FILE \n"
    << "In \n"
    << "R1: " << to_string(R1) << "\n"
    << "R2: " << to_string(R2) << "\n"
    << "Write Register: " << to_string(writeRegister) << "\n"
    << "Out \n"
    << "R1 Data: " << dataR1 << "\n"
    << "R2 Data: " << dataR2 << "\n";

  return s.str();
}
