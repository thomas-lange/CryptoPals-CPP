//
// Created by letigre on 5/16/16.
//

#include "Converter.h"


const string Converter::base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const string Converter::hex_chars = "0123456789ABCDEF";
const string Converter::frequent_english_letters = "ETAOIN";
const string Converter::rare_english_letters = "SHRDLCUMWFGYPBVKJXQZ";
const string Converter::special_characters = "/*+|<>[]{}()@$%&\"~;:_0123456789";

const float Converter::valid_offset = 0.07;
const map<char, float> Converter::english_frequency_map = {{'E', 0.01270},
                                                           {'T', 0.0906},
                                                           {'A', 0.0817},
                                                           {'O', 0.0751},
                                                           {'I', 0.0697},
                                                           {'N', 0.0675},
                                                           {'S', 0.0633},
                                                           {'H', 0.0609},
                                                           {'R', 0.0599},
                                                           {'D', 0.0425},
                                                           {'L', 0.0403},
                                                           {'C', 0.0278},
                                                           {'U', 0.0276},
                                                           {'M', 0.0241},
                                                           {'W', 0.0236},
                                                           {'F', 0.0223},
                                                           {'G', 0.0202},
                                                           {'Y', 0.0197},
                                                           {'P', 0.0193},
                                                           {'B', 0.0129},
                                                           {'V', 0.0098},
                                                           {'K', 0.0077},
                                                           {'J', 0.0015},
                                                           {'X', 0.0015},
                                                           {'Q', 0.0010},
                                                           {'Z', 0.0007}};


long Converter::isValidEnglishText(string input) {
    map<char, uint8_t> comparator;
    uint32_t length = input.size();
    transform(input.begin(), input.end(), input.begin(), ::toupper);
    for (char c: input) {
        comparator[c]++;
        if (c < 10 || (c > 14 && c < 31)) {
            return -50000;
        }
    }
    int matchScore = 0;
    for (char c: special_characters) {
        if (comparator[c] > 0) {
            matchScore -= 20 * comparator[c];
            length--;
        }
    }
    for (char c: frequent_english_letters) {
        if (comparator[c] > 0) {
            matchScore += 10;
            float val = Converter::english_frequency_map.at(c);
            float percentage = (float) comparator[c] / length;
            if (percentage > (val + valid_offset) && percentage < (val - valid_offset)) {
                matchScore +=15;
            }
        }
    }
    for (char c: rare_english_letters) {
        if (comparator[c] > 0 ) {
            matchScore += 5;
            float val = Converter::english_frequency_map.at(c);
            float percentage = (float) comparator[c] / length;
            if (percentage > (val - valid_offset) && percentage < (val + valid_offset)) {
                matchScore +=15;
            }
        }
    }
    return matchScore;
}


Converter::Converter(string input) {
    _input = input;
    _hexGenerated = false;
    _result = "Not yet generated!";
    _byteMask = "Not yet generated!";
};

string Converter::getHex() {
    if (!_hexGenerated) {
        _hex = generateHex(_input);
        _hexGenerated = true;
    }
    string payload;
    for (uint8_t u: _hex) {
        payload.push_back(hex_chars[u]);
    }
    return payload;
}

string Converter::xorHexAgainstHex(string input) {
    generateHex();
    vector<uint8_t> xorElement = generateHex(input);
    uint32_t length = _hex.size();
    if (length != xorElement.size()) {
        return string("Sizes of HexElements must match");
    }
    string payload;
    for (uint32_t i = 0; i < length; i++) {
        uint8_t item = _hex[i] ^xorElement[i];
        payload.push_back(hex_chars[item]);
    }
    return payload;
}

uint32_t Converter::getStringLength() {
    return _input.length();
}

string Converter::hexToString() {
    generateHex();
    string payload;
    uint32_t length = _hex.size();
    for (int i = 0; i < length;) {
        uint8_t item = _hex[i++] << 4;
        if (i < length) {
            item |= _hex[i++];
        }
        payload.push_back(item);
    }
    return payload;
}

string Converter::hexToStringWithXor(uint8_t xorInput) {
    generateHex();
    string payload;
    uint32_t length = _hex.size();
    for (int i = 0; i < length;) {
        uint8_t item = _hex[i++] << 4;
        if (i < length) {
            item |= _hex[i++];
        }
        payload.push_back(item ^ xorInput);
    }
    return payload;
}


vector<uint8_t> Converter::generateHex(string input) {
    vector<uint8_t> payload;
    for (char c: input) {
        int item = charToHex(c);
        if (item >= 0) {
            payload.push_back(item);
        }
    }
    return payload;
}

int Converter::charToHex(char item) {
    if (item >= 'A' && item <= 'Z') {
        return item - 'A' + 10;
    } else if (item >= '0' && item <= '9') {
        return item - '0';
    } else if (item >= 'a' && item <= 'z') {
        return item - 'a' + 10;
    }
    return -1;
}

void Converter::generateHex() {
    if (!_hexGenerated) {
        _hex = generateHex(_input);
        _hexGenerated = true;
    }
}



bool Converter::hasValidStringForEncoding() {
    string result;
    long highest = 0;
    long last = 0;
    for (int i = 1; i < 255; i++) {
        result = hexToStringWithXor(i);
        last = Converter::isValidEnglishText(result);
        if (last > highest) {
            _result = result;
            _byteMask = bitset<16>(i).to_string();
            highest = last;
        }
    }
    return highest > 250;
}



string Converter::getResult() {
    return _result;
}


string Converter::getMask() {
    return _byteMask;
}

