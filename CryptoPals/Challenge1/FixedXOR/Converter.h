//
// Created by letigre on 5/16/16.
//

#ifndef CRYPTOPALS_CONVERTER_H
#define CRYPTOPALS_CONVERTER_H
#include <iostream>
#include <vector>

using namespace std;


class Converter {
private:
    string _input;
    bool _hexGenerated;
    vector<uint8_t> _hex;

public:
    static const string base64_chars;
    static const string hex_chars;

    Converter(string input);
    string getHex();
    string xorHexAgainstHex(string input);
    vector<uint8_t> generateHex(std::string input);
    int charToHex(char item);
};
#endif //CRYPTOPALS_CONVERTER_H
