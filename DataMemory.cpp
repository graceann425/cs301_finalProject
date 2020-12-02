#include "DataMemory.h"

DataMemory::DataMemory(string filename){
  ifstream input;
  input.open(filename.c_str());

  if(input.fail()){
    cout << "Error: Bad format in your file" << filename << endl;
  }

  else{
    string line;

    while (getline(input, line)){

      if (line.size() == 0 || line.at(0) == '#')
        continue;

      MemoryEntry me;
      string address = "";
      string data = "";
      bool isData = false;

      std::size_t idx = 0;

      while (idx < line.size()){
        char c = line.at(idx);
        if (c == ' ' || c == '\t'){
          idx++;
        } else if (c == '#'){
          break;
        } else if (c == ':'){
          isData = true;
          idx++;
        } else if (isData){
          data += c;
          idx++;
        } else {
          address += c;
          idx++;
        }
      }
      me.address = address;
      me.data = data;
      memory.push_back(me);
    }
  }

  InAddress = "";
  InData = "";
  OutData = "";

}//end setInData() funtion



void DataMemory::readData()
{
  for (int i = 0; i < static_cast<int>(memory.size()); i++) {
    string memAddress = memory.at(i).address;

    if (InAddress.compare(memAddress) == 0) {
      OutData = memory.at(i).data;
      return;
    }
  }
  cerr << "Memory Address not Found. Terminating program.\n";
  exit(1);
}


void DataMemory::writeData()
{
  for (int i = 0; i < static_cast<int>(memory.size()); i++) {
    string memAddress = memory.at(i).address;

    if (InAddress.compare(memAddress) == 0) {
      memory.at(i).data = InData;
      return;
    }
  }
  cerr << "Memory Address not Found. Terminating program.\n";
  exit(1);
}


string DataMemory::printInputsAndOutput()
{
  stringstream s;

  s << "DATA MEMORY \n" << hex
    << "In\n"
    << "Address: ";
    if (InAddress.size() != 0)
      s << "0x" << InAddress;

  s << "\nWrite Data: ";
    if (InData.size() != 0)
      s << "0x" << InData;

  s << "\nOut"
    << "\nRead Data: ";
    if (OutData.size() != 0){
      if (OutData.at(0) == '0' && OutData.at(1) == 'x'){
        s << OutData << "\n";
      } else {
        s << "0x" << OutData << "\n";
      }
    }
  return s.str();
}

//print all the memory stored in this object
string DataMemory::printDataMemory()
{
  stringstream s;

  s << "DATA MEMORY \n";

  for (int i = 0; i < static_cast<int>(memory.size()); i++)
    s << memory.at(i).address << ":" << memory.at(i).data << "\n";

  return s.str();
}


void DataMemory::reset()
{
  InAddress = "";
  InData = "";
  OutData = "";
}
