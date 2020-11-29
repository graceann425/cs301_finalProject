#include "MainProcessor.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;



int main(int argc, char *argv[])
{
  if(argc < 2) {
    cerr << "Format: ./tester <config_filename>" << endl;
    exit(1);
  }


  MainProcessor *mp;
  mp = new MainProcessor(argv[1]);

  // fetch() returns false when it tries to access an index greater than the
  // total number of instructions in the asm file.
  while (mp->fetch()) {

    mp->decode();
    mp->execute();
    mp->memory();
    mp->writeback();
    mp->printProcessor();

    if (mp->isSingleStep()) {
      char c = 0;

      while (c != 'y') {
        cout << "Press 'y' to continue: ";
        cin >> c;
      }
    }

  }

  delete mp;

  stringstream s;

  // s << hex << 10;
  //
  // cout << s.str() << endl;
  //
  // int e = stoi("0x1AbC", nullptr, 16);
  // cout << e << endl;
  // cout << "0x" << hex << e << endl;
  // int i = stoi("10000000000000000000000",nullptr,2);
  // cout << "0x" << hex << i << endl;

  // ALU *a;
  // a = new ALU();
  // a->operate("1100","1100");
  // cout << a->toString();
  // delete a;
  // RegisterMemory *rm;
  // rm = new RegisterMemory();
  //
  // string ar = argv[1];
  // rm->readFileMemory(argv[1]);
  // cout << rm->toString();
  // delete rm;
}
