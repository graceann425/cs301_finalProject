#include "PC.h"

string PC::toString(){
  stringstream s;

  s << "PC \n"
    << "Next Address: 0x" << myAddress << "\n";

  return s.str();
}
