#include "MainProcessor.h"
#include "NumberConverter.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

void testing()
// For testing objects
{

  stringstream s;
  // 31 bit cannot be 1
  int l = stoi("1000000000000000",nullptr,2);
  int r = stoi("0000001010111100",nullptr,2);
  // (r < 0x8000)

  string sr = "hello";
  sr += 4;
  cout << sr << endl;

  s << dec << l << " " << r << endl;
  s << hex << l << " " << r;
  cout << s.str() << endl;

  string hexi = NumberConverter::binaryToHex("10001100010000010000001010111100");
  cout << hexi << endl;

  exit(1);
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
  // // 0x400000 + -4
  // a->setOperation("0000");
  // a->operate("00000000010000000000000000000100","00000000000000000000000000000100");
  // //a->operate("00000000010000000000000000000100","11111111111111111111111111111100");
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


int main(int argc, char *argv[])
{
  if(argc < 2) {
    cerr << "Format: ./tester <config_filename>" << endl;
    exit(1);
  }

  // Use flag -t for testing and debugging
  string command = argv[1];
  if (command.compare("-t") == 0){
    testing();
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
    mp->resetContents();

    if (mp->isSingleStep()) {
      char c = 0;

      while (c != 'y') {
        cout << "Press 'y' to continue: ";
        cin >> c;
      }
    }

  }

  delete mp;

}
