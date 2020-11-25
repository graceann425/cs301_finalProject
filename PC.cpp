#include "PC.h"

string PC::toString(){
  stringstream s;

  s << "PC: \n"
    << myAddress << "\n";

  return s.str(); 
}
