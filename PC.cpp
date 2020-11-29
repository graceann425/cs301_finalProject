#include "PC.h"

string PC::toString(){
  stringstream s;

  s << "PC \n"
    << "Current Address: 0x" << myAddress << "\n";

  return s.str();
}
