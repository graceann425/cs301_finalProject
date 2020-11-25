#include "MainProcessor.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;



int main(int argc, char *argv[])
{
  if(argc < 2){
    cerr << "Format: ./tester <filename>"<<endl;
    exit(1);
  }

  // RegisterMemory *rm;
  // rm = new RegisterMemory();
  //
  // string ar = argv[1];
  // rm->readFileMemory(argv[1]);
  // cout << rm->toString();
  // delete rm;
}
