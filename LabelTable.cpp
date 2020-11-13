#include "LabelTable.h"


void LabelTable::addLabels(string filename)
  // Read file to find and store all labels and their respective addresses.
{
  ifstream in;
  in.open(filename.c_str());


  if(in.fail()){
    cout << "bad format in file " << filename << endl;

  } else {
    string line;                   // Line in file
    int currentAddress = 0x400000; // Default starting address
    LabelEntry le;                 // Holds label and address

    while (getline(in, line)){
      // Look at every character in current line for a ':'
      for (int i = 0; i < static_cast<int>(line.length()); i++){

         if (line.at(i) == ':') {
           string label = line.substr(0,i);
           // Store label name and its address
           le.name = label;
           le.address = currentAddress;
           myVector.push_back(le);
         }
      }
      currentAddress += 4;
    }
  }

  in.close();
}


int LabelTable::getAddressOfLabel(string labelName)
  // Fetch the address of the label labelName. Return -1 if no such
  // label exists.
{
  for (int i = 0; i < static_cast<int>(myVector.size()); i++){
    if (labelName.compare(myVector.at(i).name) == 0){
      return myVector.at(i).address;
    }
  }
  return -1;
}


void LabelTable::printString()
  // Print out all the labels and its addresses currently stored in this object
{
  cout << "vector size: " << to_string(myVector.size()) << endl;

  for (int i = 0; i < static_cast<int>(myVector.size()); i++){
    cout << to_string(i) << " Label Name: " << myVector.at(i).name
      << " Address: " << to_string(myVector.at(i).address)
      << "  Name Length: "<< to_string(myVector.at(i).name.size()) << endl;
  }
}
