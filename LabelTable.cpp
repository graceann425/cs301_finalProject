#include "LabelTable.h"


/**
 * Read file to find and store all labels and their respective addresses.
 *
 * @param filename name of file to read
 */
void LabelTable::addLabels(string filename)
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

      // Ignore blank or comment lines
      if (line.at(0) == '#' || line.size() == 0)
         continue;

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


/**
 * Fetch the address of the label labelName. Return -1 if no such label exists.
 *
 * @param labelName name of label to fetch
 * @return the address in int of the label. return -1 if label not found.
 */
int LabelTable::getAddressOfLabel(string labelName)
{
  for (int i = 0; i < static_cast<int>(myVector.size()); i++){
    if (labelName.compare(myVector.at(i).name) == 0){
      return myVector.at(i).address;
    }
  }
  return -1;
}


/**
 * Print out all the labels and its addresses currently stored in this object.
 */
void LabelTable::printString()
{
  cout << "vector size: " << to_string(myVector.size()) << endl;

  for (int i = 0; i < static_cast<int>(myVector.size()); i++){
    cout << to_string(i) << " Label Name: " << myVector.at(i).name
      << " Address: " << to_string(myVector.at(i).address)
      << "  Name Length: "<< to_string(myVector.at(i).name.size()) << endl;
  }
}
