#ifndef __LABELTABLE_H__
#define __LABELTABLE_H__

using namespace std;

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class LabelTable {
  public:
    LabelTable() {};
    ~LabelTable() {};

    // Obtain and store labels from file
    void addLabels(string filename);

    // Fetch address of a label
    int getAddressOfLabel(string labelName);

    // Print all labels and addresses currently stored
    void printString();

  private:
    // Basic unit to store label and address pairs
    struct LabelEntry {
      string name;
      int address;

      LabelEntry() {
        name = "";
        address = 0;
      };
    };

    vector<LabelEntry> myVector; // Vector to hold all label entries
};

#endif
