//
// Created by letigre on 5/16/16.
//

#include "Converter.h"


const string Converter::base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const string Converter::hex_chars = "0123456789ABCDEF";
const string Converter::frequent_english_letters = "ETAOIN";
const string Converter::rare_english_letters = "SHRDLCUMWFGYPBVKJXQZ";
const string Converter::special_characters = "/*+|<>[]{}()'`´@$%&\"~;:_-,.";
const float Converter::valid_offset = 0.1;
const map<char, float> Converter::english_frequency_map = {{'E', 0.1270},
                                                           {'T', 0.906},
                                                           {'A', 0.817},
                                                           {'O', 0.751},
                                                           {'I', 0.697},
                                                           {'N', 0.675},
                                                           {'S', 0.633},
                                                           {'H', 0.609},
                                                           {'R', 0.599},
                                                           {'D', 0.425},
                                                           {'L', 0.403},
                                                           {'C', 0.278},
                                                           {'U', 0.276},
                                                           {'M', 0.241},
                                                           {'W', 0.236},
                                                           {'F', 0.223},
                                                           {'G', 0.202},
                                                           {'Y', 0.197},
                                                           {'P', 0.193},
                                                           {'B', 0.129},
                                                           {'V', 0.098},
                                                           {'K', 0.077},
                                                           {'J', 0.015},
                                                           {'X', 0.015},
                                                           {'Q', 0.010},
                                                           {'Z', 0.007}};


bool Converter::isValidEnglishText(string input) {
    map<char, uint8_t> comparator;
    uint32_t length = input.size();
    transform(input.begin(), input.end(), input.begin(), ::toupper);
    for (char c: input) {
        comparator[c]++;
        if (c >= 0 && c <= 31) {
            return false;
        }
    }
    uint32_t matchScore = 0;
    int counter = 0;
    for (char c: special_characters) {
        if (comparator[c] > 3 && matchScore > 0) matchScore--;
        counter += comparator[c];
        length--;
    }
    if (counter > input.size() / 7) return false;
    for (char c: frequent_english_letters) {
        if (comparator[c] > 0) matchScore++;
        float val = Converter::english_frequency_map.at(c);
        float percentage = (float) comparator[c] / length;
        if (percentage > (val - valid_offset) && percentage < (val + valid_offset)) {
            matchScore++;
        }
    }
    for (char c: rare_english_letters) {
        if (comparator[c] > 0) matchScore++;
    }

    return matchScore > 16;
}


Converter::Converter(string input) {
    _input = input;
    _hexGenerated = false;
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