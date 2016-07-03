//
// Created by letigre on 5/16/16.
//

#ifndef CRYPTOPALS_CONVERTER_H
#define CRYPTOPALS_CONVERTER_H

#include <iostream>
#include <vector>
#include <bitset>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

class Converter {

    string _input;
    bool _hexGenerated;
    vector<uint8_t> _hex;
    string _result;
    string _byteMask;
    static const string rare_english_letters;
    static const string frequent_english_letters;
    static const string special_characters;
    static const float valid_offset;
    static const string valid_characters;

public:
    static const string base64_chars;
    static const string hex_chars;
    static const map<char, float> english_frequency_map;

    Converter(string input);

    string getHex();

    string xorHexAgainstHex(string input);

    uint32_t getStringLength();

    string hexToString();

    string hexToStringWithXor(uint8_t xorInput);

    static long isValidEnglishText(string input);
    bool hasValidStringForEncoding();
    string getResult();
    string getMask();

private:

    void generateHex();

    vector<uint8_t> generateHex(string input);

    int charToHex(char item);


};


#endif //CRYPTOPALS_CONVERTER_H
