//
// Created by letigre on 5/16/16.
//



#include "Converter.h"
//#include <string>

using namespace std;

int main() {
    Converter c("1c0111001f010100061a024b53535009181c");
    string s = c.getHex();
    printf(s.c_str());
    printf("\n");

    string x = c.xorHexAgainstHex("686974207468652062756c6c277320657965");
    printf(x.c_str());
    printf("\n");

    return 0;
}