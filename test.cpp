#include "MainProcessor.h"
#include "NumberConverter.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

void testing()
// For testing objects
{

  cout << "----------------------------------TESTING ALU-----------------------------------\n";
  //testing ALU
  ALU *a;
  a = new ALU();
  a->setName("Test ALU");

  //testing add operation
  a->setOperation("0010");
  a->operate("00000000000000000000000000000111", "00000000000000000000000000000110");
  cout << "ADDING\nEXPECTED OUTPUT\n";
  cout << "Test ALU" << '\n';
  cout << "Input 1: 0x00000007" << '\n';
  cout << "Input 2: 0x00000006" << '\n';
  cout << "ALU Operation: 0x2" << '\n';
  cout << "Output: 0x0000000D" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << a->toString();
  cout << "----------------------------------------------------------------------\n";

  a->operate("11111111111111111111111111111000", "11111111111111111111111111111011");
  cout << "ADDING NEGATIVE NUMBERS\nEXPECTED OUTPUT\n";
  cout << "Test ALU" << '\n';
  cout << "Input 1: 0xFFFFFFF8" << '\n';
  cout << "Input 2: 0xFFFFFFFB" << '\n';
  cout << "ALU Operation: 0x2" << '\n';
  cout << "Output: 0xFFFFFFF3" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << a->toString();
  cout << "----------------------------------------------------------------------\n";

  //testing subtract operation
  a->setOperation("0110");
  a->operate("00000000000000000000000000000111", "00000000000000000000000000000110");
  cout << "SUBTRACTING NUMBERS\nEXPECTED OUTPUT\n";
  cout << "Test ALU" << '\n';
  cout << "Input 1: 0x00000007" << '\n';
  cout << "Input 2: 0x00000006" << '\n';
  cout << "ALU Operation: 0x6" << '\n';
  cout << "Output: 0x00000001" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << a->toString();
  cout << "----------------------------------------------------------------------\n";

  a->operate("11111111111111111111111111111000", "11111111111111111111111111111011");
  cout << "SUBTRACTING NUMBERS\nEXPECTED OUTPUT\n";
  cout << "Test ALU" << '\n';
  cout << "Input 1: 0xFFFFFFF8" << '\n';
  cout << "Input 2: 0xFFFFFFFB" << '\n';
  cout << "ALU Operation: 0x00000006" << '\n';
  cout << "Output: 0xFFFFFFFD" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << a->toString();
  cout << "----------------------------------------------------------------------\n";

  //testing and operation
  // a->setOperation("0000");
  // a->operate("00000000000000000000000000000111", "000000000000000000000000000110");
  // cout << "Test ALU" << '\n';
  // cout << "Input 1: 0x00000007" << '\n';
  // cout << "Input 2: 0x00000006" << '\n';
  // cout << "ALU Operation: 0x00000000" << '\n';
  // cout << "Output: 0x00000006" << endl;
  // cout << a->toString();
  //
  // a->operate("11111111111111111111111111111000", "11111111111111111111111111111011");
  // cout << "Test ALU" << '\n';
  // cout << "Input 1: 0xFFFFFFF8" << '\n';
  // cout << "Input 2: 0xFFFFFFFB" << '\n';
  // cout << "ALU Operation: 0x00000000" << '\n';
  // cout << "Output: 0xFFFFFFF8" << endl;
  // cout << a->toString();
  //
  // //testing or operation
  // a->setOperation("0001");
  // a->operate("00000000000000000000000000000111", "000000000000000000000000000110");
  // cout << "Test ALU" << '\n';
  // cout << "Input 1: 0x00000007" << '\n';
  // cout << "Input 2: 0x00000006" << '\n';
  // cout << "ALU Operation: 0x00000001" << '\n';
  // cout << "Output: 0x00000007" << endl;
  // cout << a->toString();
  //
  // a->operate("11111111111111111111111111111000", "11111111111111111111111111111011");
  // cout << "Test ALU" << '\n';
  // cout << "Input 1: 0xFFFFFFF8" << '\n';
  // cout << "Input 2: 0xFFFFFFFB" << '\n';
  // cout << "ALU Operation: 0x00000001" << '\n';
  // cout << "Output: 0xFFFFFFFB" << endl;
  // cout << a->toString();

  //testing set on less than operation
  a->setOperation("0111");
  a->operate("00000000000000000000000000000111", "00000000000000000000000000000110");
  cout << "SUBTRACTING NUMBERS\nEXPECTED OUTPUT\n";
  cout << "Test ALU" << '\n';
  cout << "Input 1: 0x00000007" << '\n';
  cout << "Input 2: 0x00000006" << '\n';
  cout << "ALU Operation: 0x7" << '\n';
  cout << "Output: 0x00000000" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << a->toString();
  cout << "----------------------------------------------------------------------\n";

  a->operate("11111111111111111111111111111000", "11111111111111111111111111111011");
  cout << "TESTING SLT WITH NEGATIVE NUMBERS\n";
  cout << "Test ALU" << '\n';
  cout << "Input 1: 0xFFFFFFF8" << '\n';
  cout << "Input 2: 0xFFFFFFFB" << '\n';
  cout << "ALU Operation: 0x7" << '\n';
  cout << "Output: 0x00000001" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << a->toString();
  cout << "----------------------------------------------------------------------\n";

  delete a;

  //testing ALU Control Unit
  ALUControlUnit *alu;
  alu = new ALUControlUnit();
  cout << "------------------------------TESTING ALU CONTROL UNIT--------------------------\n";
  //testing add
  alu->determineALUOperation("10", "100000");
  cout << "TESTING -ADD- OPERATION" << '\n';
  cout << "ALU Operation Code: 10" << '\n';
  cout << "Function Code: 100000" << '\n';
  cout << "ALU Operation: 0010" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << alu->toString();
  cout << "----------------------------------------------------------------------\n";

  //testing subtract
  alu->determineALUOperation("10", "100010");
  cout << "TESTING -SUBTRACT- OPERATION" << '\n';
  cout << "ALU Operation Code: 10" << '\n';
  cout << "Function Code: 100010" << '\n';
  cout << "ALU Operation: 0110" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << alu->toString();
  cout << "----------------------------------------------------------------------\n";

  // //testing and
  // alu->determineALUOperation("10", "100100");
  // cout << "Test and" << '\n';
  // cout << "ALU Operation Code: 10" << '\n';
  // cout << "Function Code: 100100" << '\n';
  // cout << "ALU Operation: 0000" << endl;
  // cout << "\nACTUAL OUTPUT\n";
  // cout << alu->toString();
  // cout << "----------------------------------------------------------------------\n";
  //
  // //testing or
  // alu->determineALUOperation("10", "100101");
  // cout << "Test or" << '\n';
  // cout << "ALU Operation Code: 10" << '\n';
  // cout << "Function Code: 100101" << '\n';
  // cout << "ALU Operation: 0001" << endl;
  // cout << "\nACTUAL OUTPUT\n";
  // cout << alu->toString();
  // cout << "----------------------------------------------------------------------\n";

  //testing beq
  alu->determineALUOperation("01", "100000");
  cout << "TESTING BEQ" << '\n';
  cout << "ALU Operation Code: 01" << '\n';
  cout << "Function Code: 000000" << '\n';
  cout << "ALU Operation: 0110" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << alu->toString();
  cout << "----------------------------------------------------------------------\n";

  //testing lw/sw
  alu->determineALUOperation("00", "100000");
  cout << "TESTING LW/SW" << '\n';
  cout << "ALU Operation Code: 00" << '\n';
  cout << "Function Code: 000000" << '\n';
  cout << "ALU Operation: 0010" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << alu->toString();
  cout << "----------------------------------------------------------------------\n";
  delete alu;

  //testing Multiplexer
  Multiplexer *m;
  m = new Multiplexer();
  cout << "------------------------------TESTING MULTIPLEXER--------------------------\n";
  cout << "Test Multiplexer 1" << endl;
  m->select("00001111", "11110000", 0);
  cout << "MULTIPLEXER" << '\n';
  cout << "Input 0: 0x00001111" << '\n';
  cout << "Input 1: 0x11110000" << '\n';
  cout << "Control Signal: 0x0" << '\n';
  cout << "Output: 0x00001111" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << m->toString();
  cout << "----------------------------------------------------------------------\n";
  delete m;
  Multiplexer *m2;
  m2 = new Multiplexer();
  cout << "Test Multiplexer 2" << endl;
  m2->select("00001111", "11110000", 1);
  cout << "MULTIPLEXER" << '\n';
  cout << "Input 0: 0x00001111" << '\n';
  cout << "Input 1: 0x11110000" << '\n';
  cout << "Control Signal: 0x1" << '\n';
  cout << "Output: 0x11110000" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << m2->toString();
  cout << "----------------------------------------------------------------------\n";
  delete m2;

  //testing shift left
  ShiftLeft *sl;
  sl = new ShiftLeft();
  cout << "------------------------------TESTING SHIFT LEFT--------------------------------\n";
  cout << "Testing shift()" << endl;
  sl->shift("11111111111111111111111111111111");
  cout << "SHIFT LEFT 2" << '\n';
  cout << "Input: 11111111111111111111111111111111 (0xFFFFFFFF)" << '\n';
  cout << "Output: 11111111111111111111111111111100 (0xFFFFFFFC)" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << sl->toString();
  cout << "----------------------------------------------------------------------\n";
  sl->shiftAdd("11111111111111111111111111");
  cout << "TESTING shiftAdd()" << '\n';
  cout << "Input: 11111111111111111111111111 (0x3FFFFFF)" << '\n';
  cout << "Output: 1111111111111111111111111100 (0xFFFFFFC)" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << sl->toString();
  cout << "----------------------------------------------------------------------\n";
  delete sl;

  //testing sign extend
  SignExtend *s;
  s = new SignExtend();
  cout << "------------------------------TESTING SIGN EXTEND-------------------------------\n";
  s->extendTo32("1000000000000000");
  cout << "EXPECTED" << '\n';
  cout << "Input: 1000000000000000 (0x8000)" << '\n';
  cout << "Output: 11111111111111111000000000000000 (0xFFFF8000)" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << s->toString();
  cout << "----------------------------------------------------------------------\n";
  s->extendTo32("0000000000000001");
  cout << "EXPECTED" << '\n';
  cout << "Input: 0000000000000001 (0x0001)" << '\n';
  cout << "Output: 00000000000000000000000000000001 (0x00000001)" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << s->toString();
  cout << "----------------------------------------------------------------------\n";
  delete s;

  cout << "------------------------------TESTING NumberConverter-------------------------------\n";
  cout << "TESTING METHOD binaryToHex()" << '\n';
  string bi1 = "01011000111011101101000001010001";
  string result1 = NumberConverter::binaryToHex(bi1);
  cout << "EXPECTED\n";
  cout << "Input: " << bi1 << endl;
  cout << "Output: 0x58eed051" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << "Output: " << result1 << endl;
  cout << "----------------------------------------------------------------------\n";

  string bi2 = "1101000001010001";
  string result2 = NumberConverter::binaryToHex(bi2);
  cout << "TESTING METHOD binaryToHex()" << '\n';
  cout << "\nEXPECTED\n";
  cout << "Input: " << bi2 << endl;
  cout << "Output: 0xd051" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << "Output: " << result2 << endl;
  cout << "----------------------------------------------------------------------\n";

  cout << "TESTING METHOD hexToBinary()" << '\n';
  string hex1 = "0x58eed051";
  string result3 = NumberConverter::hexToBinary(hex1);
  cout << "\nEXPECTED\n";
  cout << "Input: " << hex1 << endl;
  cout << "Output: 01011000111011101101000001010001" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << "Output: " << result3 << endl;
  cout << "----------------------------------------------------------------------\n";

  cout << "TESTING METHOD hexToBinary()" << '\n';
  string hex2 = "0x58EeD051";
  string result4 = NumberConverter::hexToBinary(hex1);
  cout << "\nEXPECTED\n";
  cout << "Input: " << hex2 << endl;
  cout << "Output: 01011000111011101101000001010001" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << "Output: " << result4 << endl;
  cout << "----------------------------------------------------------------------\n";

  cout << "TESTING METHOD hexToBinary()" << '\n';
  string hex3 = "58EeD051";
  string result5 = NumberConverter::hexToBinary(hex3);
  cout << "\nEXPECTED\n";
  cout << "Input: " << hex3 << endl;
  cout << "Output: 01011000111011101101000001010001" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << "Output: " << result5 << endl;
  cout << "----------------------------------------------------------------------\n";

  cout << "TESTING METHOD hexToBinary()" << '\n';
  string hex4 = "D051";
  string result6 = NumberConverter::hexToBinary(hex4);
  cout << "\nEXPECTED\n";
  cout << "Input: " << hex4 << endl;
  cout << "Output: 1101000001010001" << endl;
  cout << "\nACTUAL OUTPUT\n";
  cout << "Output: " << result6 << endl;
  cout << "----------------------------------------------------------------------\n";

  exit(1);
}


/**
 * Runs the entire program. argv[1] should be the name of the configuration file.
 *
 */
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

  // fetch() returns false when it tries to access an address out of bounds.
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

  return 1;
}
