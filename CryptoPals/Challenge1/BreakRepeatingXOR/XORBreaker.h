//
// Created by letigre on 5/24/16.
//

#ifndef CRYPTOPALS_XORBREAKER_H
#define CRYPTOPALS_XORBREAKER_H

using namespace std;

#include <cstdint>
#include <string>
#include "LanguageChecker.h"

struct hexField;
union charItem;
struct Item;


class XORBreaker {
    string _payload;
    string _input;
    uint64_t _keysize;
    uint64_t _keyLengthStart;
    uint64_t _keyLengthEnd;
    float _expectedDistance;
    vector<Item> _hammingDistances;

public:
    XORBreaker(string payload);
    static uint64_t hammingDistance(string first, string second);
    static uint16_t bitOffsetBetweenTwoChars(char a, char b);
    string hexStringToText(string input);
    void setInputTypeToHexa();
    void setKeylength(int lengthStart, int lengthEnd);
    void generateHammingDistances();
    void setExpectedHammingDistance(float distance);

//    void analyzeBlocks();

    vector<Item> predefineProbableKeySizes();

    vector<Item> decrypt();
    string decryptSingleElement(Item item);


    string generateStringByKeylength(uint64_t position, uint64_t keylength);

    uint8_t getProbableCharForEncoding(string text, Item item);

    string generateResultFromStringAndChar(string data, uint8_t item);
};



struct hexField {
    uint8_t hf2: 4;
    uint8_t hf1: 4;
};

union charItem {
    hexField field;
    char result;
};



struct Item {
    uint64_t keylength;
    uint64_t hamming;
    float hammingRatio;
    string key;
    string result;

    Item(uint64_t _keylength, uint64_t _hamming) {
        keylength = _keylength;
        hamming = _hamming;
        hammingRatio = (float)_hamming / _keylength;
        key.resize(keylength);
    }

    Item() {
        keylength = 0;
        hamming = 0;
        hammingRatio = 0;
        key = "";
        result = "";
    }

    static bool sortByRatio(Item me, Item other) {
        return me.hammingRatio < other.hammingRatio;
    };

    static bool sortBykeylength(Item me, Item other) {
        return me.keylength < other.keylength;
    };
};


#endif //CRYPTOPALS_XORBREAKER_H
