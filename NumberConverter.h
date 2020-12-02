#ifndef __NUMBER_CONVERTER_H__
#define __NUMBER_CONVERTER_H__

#include <string>
#include <iostream>

using namespace std;

/*
 * A static-like class used to convert binary numbers to hex and vice versa.
 *
 */
namespace NumberConverter {

    string binaryToHex(string binary);
    string hexToBinary(string hex);
}

#endif
