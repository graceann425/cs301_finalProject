#include "PC.h"

/**
 * Return a string outputing all relevant information stored in this object.
 *
 * @return a string with the address of PC
 */
string PC::toString()
{
  stringstream s;

  s << "PC \n"
    << "Next Address: 0x" << myAddress << "\n";

  return s.str();
}
