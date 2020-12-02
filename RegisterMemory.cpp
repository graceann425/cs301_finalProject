
#include <iostream>
#include "RegisterMemory.h"



/**
 * Reads the memory stored in a register memory file.
 *
 * @param filename name of file to read
 */
void RegisterMemory::readFileMemory(string filename) {
  ifstream in;
  in.open(filename.c_str());


  if (in.fail()) {
    cout << "bad format in file " << filename << endl;

  } else {

    string line;
    int regNum = 0;

    while (getline(in, line)) {

      // Ignore blank line
      if (line.size() == 0)
        continue;

      // Skip line if it starts with a '#'
      if (line.at(0) == '#')
        continue;

      // Check for a ':'
      std::size_t start = line.find(':');

      // If ':' found
      if (start != string::npos) {

        start += 1;
        string data = "";

        while (start < line.size()) {

          // current character in the line
          char c = line.at(start);

          // Ignore whitespace
          if (c == ' ' || c == '\t') {
            start++;

          // Stop reading line if a comment begins
          } else if (c == '#') {
            break;

          // Add character c to data
          } else {
            data += c;
            start++;
          }
        }
        registerArray[regNum++] = data;
      }
    }
  }
  in.close();
}


/**
 * Get the memory stored in the specified register.
 *
 * @param regNum the register number
 * @return a string with the memory of the given register
 */
string RegisterMemory::getRegister(int regNum) {
  if (regNum >= 32 || regNum < 0)
    return "";

  return registerArray[regNum];
}


/**
 * Given a register number and data, store the data in said register.
 *
 * @param regNum register to write to
 * @param data   data to store in given register
 */
void RegisterMemory::setRegisterData(int regNum, string data) {
  if (regNum >= 32 || regNum < 0)
    return;

  registerArray[regNum] = data;
}


/**
 * Return a string outputing all registers and their data.
 *
 * @return a string representing all the registers
 */
string RegisterMemory::toString() {
  stringstream s;

  s << "REGISTER MEMORY \n";

  for (int i = 0; i < 32; i++)
    s << to_string(i) << ":" << registerArray[i] << "\n";

  return s.str();
}
