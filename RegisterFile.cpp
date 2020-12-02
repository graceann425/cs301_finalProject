
#include <iostream>
#include "RegisterFile.h"


/**
 * Default constructor initializes all member variables.
 *
 */
RegisterFile::RegisterFile() {
  rm = nullptr;
  R1 = -1;
  R2 = -1;
  writeRegister = -1;
  dataR1 = "";
  dataR2 = "";
}


/**
 * Given some data, write it to the writeRegister.
 *
 * @param data data to be written
 */
void RegisterFile::writeData(string data) {
  rm->setRegisterData(writeRegister, data);
}


/**
 * Return the data stored in register 1 (R1).
 *
 * @return the data in R1
 */
string RegisterFile::getDataR1() {
  dataR1 = rm->getRegister(R1);
  return dataR1;
}


/**
 * Return the data stored in register 2 (R2).
 *
 * @return the data in R2
 */
string RegisterFile::getDataR2() {
  dataR2 = rm->getRegister(R2);
  return dataR2;
}


/**
 * Return a string outputing all relevant information stored in this object.
 *
 */
string RegisterFile::toString() {
  stringstream s ;

  s << "REGISTER FILE \n"
    << "In \n"
    << "R1: " << to_string(R1) << "\n"
    << "R2: " << to_string(R2) << "\n"
    << "Write Register: " << to_string(writeRegister) << "\n"
    << "Out \n"
    << "R1 Data: ";
    if (dataR1.size() != 0) {
      if (dataR1.at(0) == '0' && dataR1.at(1) == 'x'){
        s << dataR1;
      } else {
        s << "0x" << dataR1;
      }
    }

  s << "\nR2 Data: ";
    if (dataR2.size() != 0){
      if (dataR2.at(0) == '0' && dataR2.at(1) == 'x'){
        s << dataR2 << "\n";
      } else {
        s << "0x" << dataR2 << "\n";
      }
    }

  return s.str();
}


/**
 * Reset the value of most member variables for next instruction cycle.
 *
 */
void RegisterFile::reset() {
  R1 = -1;
  R2 = -1;
  writeRegister = -1;
  dataR1 = "";
  dataR2 = "";
}
