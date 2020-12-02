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
  
  //testing ALU
  ALU *a;
  a = new ALU();
  a->setName('Test ALU');

  //testing add operation 
  a->setOperation('0010');
  a->operate('00000000000000000000000000000111', '000000000000000000000000000110');
  cout << 'Test ALU' << '\n';
  cout << "Input 1: 0x00000007" << '\n';
  cout << "Input 2: 0x00000006" << '\n';
  cout << "ALU Operation: 0x00000002" << '\n';
  cout << "Output: 0x0000000D" << endl;
  cout << a->toString();

  a->operate('11111111111111111111111111111000', '11111111111111111111111111111011');
  cout << 'Test ALU' << '\n';
  cout << "Input 1: 0xFFFFFFF8" << '\n';
  cout << "Input 2: 0xFFFFFFFB" << '\n';
  cout << "ALU Operation: 0x00000002" << '\n';
  cout << "Output: 0xFFFFFFF3" << endl;
  cout << a->toString();

  //testing subtract operation
  a->setOperation('0110');
  a->operate('00000000000000000000000000000111', '000000000000000000000000000110');
  cout << 'Test ALU' << '\n';
  cout << "Input 1: 0x00000007" << '\n';
  cout << "Input 2: 0x00000006" << '\n';
  cout << "ALU Operation: 0x00000006" << '\n';
  cout << "Output: 0x00000001" << endl;
  cout << a->toString();

  a->operate('11111111111111111111111111111000', '11111111111111111111111111111011');
  cout << 'Test ALU' << '\n';
  cout << "Input 1: 0xFFFFFFF8" << '\n';
  cout << "Input 2: 0xFFFFFFFB" << '\n';
  cout << "ALU Operation: 0x00000006" << '\n';
  cout << "Output: 0xFFFFFFFD" << endl;
  cout << a->toString();

  //testing and operation
  a->setOperation('0000');
  a->operate('00000000000000000000000000000111', '000000000000000000000000000110');
  cout << 'Test ALU' << '\n';
  cout << "Input 1: 0x00000007" << '\n';
  cout << "Input 2: 0x00000006" << '\n';
  cout << "ALU Operation: 0x00000000" << '\n';
  cout << "Output: 0x00000006" << endl;
  cout << a->toString();

  a->operate('11111111111111111111111111111000', '11111111111111111111111111111011');
  cout << 'Test ALU' << '\n';
  cout << "Input 1: 0xFFFFFFF8" << '\n';
  cout << "Input 2: 0xFFFFFFFB" << '\n';
  cout << "ALU Operation: 0x00000000" << '\n';
  cout << "Output: 0xFFFFFFF8" << endl;
  cout << a->toString();

  //testing or operation
  a->setOperation('0001');
  a->operate('00000000000000000000000000000111', '000000000000000000000000000110');
  cout << 'Test ALU' << '\n';
  cout << "Input 1: 0x00000007" << '\n';
  cout << "Input 2: 0x00000006" << '\n';
  cout << "ALU Operation: 0x00000001" << '\n';
  cout << "Output: 0x00000007" << endl;
  cout << a->toString();

  a->operate('11111111111111111111111111111000', '11111111111111111111111111111011');
  cout << 'Test ALU' << '\n';
  cout << "Input 1: 0xFFFFFFF8" << '\n';
  cout << "Input 2: 0xFFFFFFFB" << '\n';
  cout << "ALU Operation: 0x00000001" << '\n';
  cout << "Output: 0xFFFFFFFB" << endl;
  cout << a->toString();

  //testing set on less than operation
  a->setOperation('0111');
  a->operate('00000000000000000000000000000111', '000000000000000000000000000110');
  cout << 'Test ALU' << '\n';
  cout << "Input 1: 0x00000007" << '\n';
  cout << "Input 2: 0x00000006" << '\n';
  cout << "ALU Operation: 0x00000007" << '\n';
  cout << "Output: 0x00000000" << endl;
  cout << a->toString();

  a->operate('11111111111111111111111111111000', '11111111111111111111111111111011');
  cout << 'Test ALU' << '\n';
  cout << "Input 1: 0xFFFFFFF8" << '\n';
  cout << "Input 2: 0xFFFFFFFB" << '\n';
  cout << "ALU Operation: 0x00000007" << '\n';
  cout << "Output: 0x00000001" << endl;
  cout << a->toString();

  delete a;

  //testing ALU Control Unit
  ALUControlUnit *a;
  a = new ALUControlUnit();
  cout << "Test ALU Control Unit" << endl;
  //testing add
  a->determineALUOperation('10', '100000');
  cout << "Test add" << '\n';
  cout << "ALU Operation Code: 10" << '\n';
  cout << "Function Code: 100000" << '\n';
  cout << "ALU Operation: 0010" << endl;
  cout << a->toString();
  //testing subtract
  a->determineALUOperation('10', '100010');
  cout << "Test subtract" << '\n';
  cout << "ALU Operation Code: 10" << '\n';
  cout << "Function Code: 100010" << '\n';
  cout << "ALU Operation: 0110" << endl;
  cout << a->toString();
  //testing and
  a->determineALUOperation('10', '100100');
  cout << "Test and" << '\n';
  cout << "ALU Operation Code: 10" << '\n';
  cout << "Function Code: 100100" << '\n';
  cout << "ALU Operation: 0000" << endl;
  cout << a->toString();
  //testing or
  a->determineALUOperation('10', '100101');
  cout << "Test or" << '\n';
  cout << "ALU Operation Code: 10" << '\n';
  cout << "Function Code: 100101" << '\n';
  cout << "ALU Operation: 0001" << endl;
  cout << a->toString();
  //testing beq
  a->determineALUOperation('01', '100000');
  cout << "Test beq" << '\n';
  cout << "ALU Operation Code: 01" << '\n';
  cout << "Function Code: 000000" << '\n';
  cout << "ALU Operation: 0110" << endl;
  cout << a->toString();
  //testing lw/sw
  a->determineALUOperation('00', '100000');
  cout << "Test sw/lw" << '\n';
  cout << "ALU Operation Code: 00" << '\n';
  cout << "Function Code: 000000" << '\n';
  cout << "ALU Operation: 0010" << endl;
  cout << a->toString();
  
  
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
