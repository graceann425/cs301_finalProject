#ifndef __DATAMEMORY_H__
#define __DATAMEMORY_H__

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class DataMemory{
  public:
    //constructor
    DataMemory(string filename);
    //deconstructor
    ~DataMemory() {};

    //data to write
    void setInData(string data){
      InData = data;
    };

    //address to write to or read from
    void setInAddress(string address){
      InAddress = address;
    };

    //data read from InAddress
    string getOutData(){
      return OutData;
    };

    /*finds the data stored in InAddress, to get data after this calculation, use
      the previous function getOutData()
    */
    void readData();

    /* Writes InData to the InAddress.
        The methods setInData() and setInAddress() must have been called beforehand.
    */
    void writeData();

    //print InAddress, InData, and OutData
    string printInputsAndOutput();

    //print all the memory stored in this object
    string printDataMemory();

    // reset the value of member variables (excluding vector)
    void reset();

  private:
    string InAddress;
    string InData;
    string OutData;

    //stores address and data pairs
    struct MemoryEntry{
      string address;
      string data;

      MemoryEntry(){
        address = "";
        data = "";
      }; //end MemoryEntry()

    }; //end MemoryEntry

    //stores all memory entries from the memory file
    vector<MemoryEntry>memory;
};

#endif
