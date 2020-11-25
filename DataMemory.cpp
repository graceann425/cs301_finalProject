#include "DataMemory.h"

DataMemory::DataMemory(string filename){
  ifstream input;
  input.open(filename.c_str());

  if(input.fail()){
    cout << "Error: Bad format in your file" << filename << endl;
  }

  else{

  }




}//end setInData() funtion
