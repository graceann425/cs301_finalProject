#ifndef __NUMBER_CONVERTER_CPP__
#define __NUMBER_CONVERTER_CPP__

#include "NumberConverter.h"

/**
 * Author: Kent Soledispa
 *
 * A "static" class
 */
namespace NumberConverter {

  string binaryToHex(string binary)
  {
    if (binary.size() == 0)
      return "";

    string hex = "";

    std::size_t start = 0;
    std::size_t end = 4;

    while (end <= binary.size()) {
      string substr = binary.substr(start,4);
      int num = stoi(substr,nullptr,2);

      if (num < 10) {
        hex += to_string(num);

      } else {

        switch (num) {
          case 10:
            hex += "a";	break;
          case 11:
            hex += "b"; break;
          case 12:
            hex += "c";	break;
          case 13:
            hex += "d";	break;
          case 14:
            hex += "e";	break;
          case 15:
            hex += "f";	break;
        }
      }
      start += 4;
      end += 4;
    }

    return hex;
  }

  string hexToBinary(string hex)
  {
  	string binary = "";
  	int count = 0;

  	for (int i=hex.size()-1; i >= 0; i--) {
  		char c = hex.at(i);

  		// If uppercase, make lowercase
  		if (c >= 65 && c <= 90)
  			c += 32;

  		if (c == 'x')
  			break;

  		switch (c) {
  			case '0':
  				binary = "0000" + binary;	break;
  			case '1':
  				binary = "0001" + binary;	break;
  			case '2':
  				binary = "0010" + binary;	break;
  			case '3':
  				binary = "0011" + binary;	break;
  			case '4':
  				binary = "0100" + binary;	break;
  			case '5':
  				binary = "0101" + binary;	break;
  			case '6':
  				binary = "0110" + binary;	break;
  			case '7':
  				binary = "0111" + binary;	break;
  			case '8':
  				binary = "1000" + binary;	break;
  			case '9':
  				binary = "1001" + binary;	break;
  			case 'a':
  				binary = "1010" + binary;	break;
  			case 'b':
  				binary = "1011" + binary; break;
  			case 'c':
  				binary = "1100" + binary;	break;
  			case 'd':
  				binary = "1101" + binary;	break;
  			case 'e':
  				binary = "1110" + binary;	break;
  			case 'f':
  				binary = "1111" + binary;	break;
  		}
  		count += 4;
  	}

  	char bit = binary.at(0);
  	//cout << "before: " << binary << endl;
  	while (count < 32) {
  		binary = bit + binary;
  		//cout << "after: " << binary << endl;
  		count++;
  	}

  	return binary;
  }
}

#endif
