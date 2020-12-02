#include "MainProcessor.h"
#include "NumberConverter.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

void testing()
// For testing objects
{


  //testing ALU
  ALU *a;
  a = new ALU();
  a->setName("Test ALU");

  //testing add operation
  a->setOperation("0010");
  a->operate("00000000000000000000000000000111", "00000000000000000000000000000110");
  cout << "Test ALU" << '\n';
  cout << "Input 1: 0x00000007" << '\n';
  cout << "Input 2: 0x00000006" << '\n';
  cout << "ALU Operation: 0x00000002" << '\n';
  cout << "Output: 0x0000000D" << endl;
  cout << a->toString();

  a->operate("11111111111111111111111111111000", "11111111111111111111111111111011");
  cout << "Test ALU" << '\n';
  cout << "Input 1: 0xFFFFFFF8" << '\n';
  cout << "Input 2: 0xFFFFFFFB" << '\n';
  cout << "ALU Operation: 0x00000002" << '\n';
  cout << "Output: 0xFFFFFFF3" << endl;
  cout << a->toString();

  //testing subtract operation
  a->setOperation("0110");
  a->operate("00000000000000000000000000000111", "000000000000000000000000000110");
  cout << "Test ALU" << '\n';
  cout << "Input 1: 0x00000007" << '\n';
  cout << "Input 2: 0x00000006" << '\n';
  cout << "ALU Operation: 0x00000006" << '\n';
  cout << "Output: 0x00000001" << endl;
  cout << a->toString();

  a->operate("11111111111111111111111111111000", "11111111111111111111111111111011");
  cout << "Test ALU" << '\n';
  cout << "Input 1: 0xFFFFFFF8" << '\n';
  cout << "Input 2: 0xFFFFFFFB" << '\n';
  cout << "ALU Operation: 0x00000006" << '\n';
  cout << "Output: 0xFFFFFFFD" << endl;
  cout << a->toString();

  //testing and operation
  a->setOperation("0000");
  a->operate("00000000000000000000000000000111", "000000000000000000000000000110");
  cout << "Test ALU" << '\n';
  cout << "Input 1: 0x00000007" << '\n';
  cout << "Input 2: 0x00000006" << '\n';
  cout << "ALU Operation: 0x00000000" << '\n';
  cout << "Output: 0x00000006" << endl;
  cout << a->toString();

  a->operate("11111111111111111111111111111000", "11111111111111111111111111111011");
  cout << "Test ALU" << '\n';
  cout << "Input 1: 0xFFFFFFF8" << '\n';
  cout << "Input 2: 0xFFFFFFFB" << '\n';
  cout << "ALU Operation: 0x00000000" << '\n';
  cout << "Output: 0xFFFFFFF8" << endl;
  cout << a->toString();

  //testing or operation
  a->setOperation("0001");
  a->operate("00000000000000000000000000000111", "000000000000000000000000000110");
  cout << "Test ALU" << '\n';
  cout << "Input 1: 0x00000007" << '\n';
  cout << "Input 2: 0x00000006" << '\n';
  cout << "ALU Operation: 0x00000001" << '\n';
  cout << "Output: 0x00000007" << endl;
  cout << a->toString();

  a->operate("11111111111111111111111111111000", "11111111111111111111111111111011");
  cout << "Test ALU" << '\n';
  cout << "Input 1: 0xFFFFFFF8" << '\n';
  cout << "Input 2: 0xFFFFFFFB" << '\n';
  cout << "ALU Operation: 0x00000001" << '\n';
  cout << "Output: 0xFFFFFFFB" << endl;
  cout << a->toString();

  //testing set on less than operation
  a->setOperation("0111");
  a->operate("00000000000000000000000000000111", "000000000000000000000000000110");
  cout << "Test ALU" << '\n';
  cout << "Input 1: 0x00000007" << '\n';
  cout << "Input 2: 0x00000006" << '\n';
  cout << "ALU Operation: 0x00000007" << '\n';
  cout << "Output: 0x00000000" << endl;
  cout << a->toString();

  a->operate("11111111111111111111111111111000", "11111111111111111111111111111011");
  cout << "Test ALU" << '\n';
  cout << "Input 1: 0xFFFFFFF8" << '\n';
  cout << "Input 2: 0xFFFFFFFB" << '\n';
  cout << "ALU Operation: 0x00000007" << '\n';
  cout << "Output: 0x00000001" << endl;
  cout << a->toString();

  delete a;

  //testing ALU Control Unit
  ALUControlUnit *alu;
  alu = new ALUControlUnit();
  cout << "Test ALU Control Unit" << endl;
  //testing add
  alu->determineALUOperation("10", "100000");
  cout << "Test add" << '\n';
  cout << "ALU Operation Code: 10" << '\n';
  cout << "Function Code: 100000" << '\n';
  cout << "ALU Operation: 0010" << endl;
  cout << alu->toString();
  //testing subtract
  alu->determineALUOperation("10", "100010");
  cout << "Test subtract" << '\n';
  cout << "ALU Operation Code: 10" << '\n';
  cout << "Function Code: 100010" << '\n';
  cout << "ALU Operation: 0110" << endl;
  cout << alu->toString();
  //testing and
  alu->determineALUOperation("10", "100100");
  cout << "Test and" << '\n';
  cout << "ALU Operation Code: 10" << '\n';
  cout << "Function Code: 100100" << '\n';
  cout << "ALU Operation: 0000" << endl;
  cout << alu->toString();
  //testing or
  alu->determineALUOperation("10", "100101");
  cout << "Test or" << '\n';
  cout << "ALU Operation Code: 10" << '\n';
  cout << "Function Code: 100101" << '\n';
  cout << "ALU Operation: 0001" << endl;
  cout << alu->toString();
  //testing beq
  alu->determineALUOperation("01", "100000");
  cout << "Test beq" << '\n';
  cout << "ALU Operation Code: 01" << '\n';
  cout << "Function Code: 000000" << '\n';
  cout << "ALU Operation: 0110" << endl;
  cout << alu->toString();
  //testing lw/sw
  alu->determineALUOperation("00", "100000");
  cout << "Test sw/lw" << '\n';
  cout << "ALU Operation Code: 00" << '\n';
  cout << "Function Code: 000000" << '\n';
  cout << "ALU Operation: 0010" << endl;
  cout << alu->toString();

  //testing Multiplexer
  Multiplexer *m;
  m = new Multiplexer();
  cout << "Test Multiplexer 1" << endl;
  m->select("00001111", "11110000", 0);
  cout << "MULTIPLEXER" << '\n';
  cout << "Input 0: 00001111" << '\n';
  cout << "Input 1: 11110000" << '\n';
  cout << "Control Signal: 0x0" << '\n';
  cout << "Output: 00001111" << endl;
  cout << m->toString();
  Multiplexer *m2;
  m2 = new Multiplexer();
  cout << "Test Multiplexer 2" << endl;
  m2->select("00001111", "11110000", 1);
  cout << "MULTIPLEXER" << '\n';
  cout << "Input 0: 00001111" << '\n';
  cout << "Input 1: 11110000" << '\n';
  cout << "Control Signal: 0x1" << '\n';
  cout << "Output: 11110000" << endl;
  cout << m2->toString();

  //testing shift left
  ShiftLeft *sl;
  sl = new ShiftLeft();
  cout << "Test Shift Left" << endl;
  sl->shift("11111111");
  cout << "SHIFT LEFT 2" << '\n';
  cout << "Input: 11111111" << '\n';
  cout << "Output: 11111100" << endl;
  cout << sl->toString();
  sl->shiftAdd("11111111");
  cout << "SHIFT LEFT 2" << '\n';
  cout << "Input: 11111111" << '\n';
  cout << "Output: 1111111100" << endl;
  cout << sl->toString();

  //testing sign extend
  SignExtend *s;
  s = new SignExtend();
  cout << "Test Sign Extend" << endl;
  s->extendTo32("10");
  cout << "SIGN EXTEND 32" << '\n';
  cout << "Input: 10" << '\n';
  cout << "Output: 111111111111111110" << endl;
  cout << s->toString();
  s->extendTo32("01");
  cout << "SIGN EXTEND 32" << '\n';
  cout << "Input: 01" << '\n';
  cout << "Output: 000000000000000001" << endl;
  cout << s->toString();

  exit(1);


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
