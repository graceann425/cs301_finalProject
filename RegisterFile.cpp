
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
  rm.setRegisterData(writeRegister, data);
}


string RegisterFile::getDataR1() {
  return getRegister(R1);
}


string RegisterFile::getDataR2() {
  return getRegister(R2);
}


void RegisterFile::printRegisterFile() {
  cout << "Register File: \n";
  cout << "In " << endl;
  cout << "R1: " << R1.to_string() << endl;
  cout << "R2: " << R2.to_string() << endl;
  cout << "Write Register: " << writeRegister.to_string() << endl;
  cout << "Out " << endl;
  cout << "R1 Data: " << dataR1 << endl;
  cout << "R2 Data: " << dataR2 << endl;
}
