//
// Created by letigre on 5/15/16.
//

#ifndef CRYPTOPALS_HEXBASE64_H
#define CRYPTOPALS_HEXBASE64_H


#include <iostream>
#include <cstring>
#include <string>
#include <stdio.h>


namespace HexBase64 {
    int charToHex(char item);
    const char* hexToBase64(const char* input);
};

#endif //CRYPTOPALS_HEXBASE64_H
