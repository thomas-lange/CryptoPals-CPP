//
// Created by letigre on 5/24/16.
//

#include <stdexcept>
#include <vector>
#include <algorithm>
#include "XORBreaker.h"
#include "LanguageChecker.h"

uint64_t XORBreaker::hammingDistance(string first, string second) {
    uint64_t length = first.size();
    if (first.size() != second.size()) {
        throw invalid_argument("String sizes do not match");
    }
    uint64_t value = 0;
    for (uint64_t i = 0; i < length; i++) {
        value += XORBreaker::bitOffsetBetweenTwoChars(first.at(i), second.at(i));
    }
    return value;
}

uint16_t XORBreaker::bitOffsetBetweenTwoChars(char a, char b) {
    uint16_t difference = a ^ b;
    uint16_t payload = 0;
    while (difference > 0) {
        payload += difference % 2;
        difference /= 2;
    }
    return payload;
}

void XORBreaker::setKeylength(int lengthStart, int lengthEnd) {
    _keyLengthStart = min(lengthStart, lengthEnd);
    _keyLengthEnd = max(lengthStart, lengthEnd);
}


void XORBreaker::generateHammingDistances() {
    if (_keyLengthEnd * 2 > _payload.size()) {
        throw invalid_argument("The input needs to be at least twice the sice of the maximum lenght!");
    }

    for (int i = _keyLengthStart; i <= _keyLengthEnd; ++i) {
        _hammingDistances.push_back(Item(i, XORBreaker::hammingDistance(_payload.substr(0, i), _payload.substr(i, i ))));
    }
    sort(_hammingDistances.begin(), _hammingDistances.end(), Item::sortByRatio);
}

XORBreaker::XORBreaker(string payload) {
    _payload = payload;
    _input = payload;
    _keysize = 0;
    _expectedDistance = 3.25;
    setKeylength(1, 20);
}

void XORBreaker::setInputTypeToHexa() {
    _payload = XORBreaker::hexStringToText(_input);
}

void XORBreaker::setExpectedHammingDistance(float distance) {
    _expectedDistance = distance;
}

uint8_t hexaToDecimal(char input) {
    if (input >= 'A' && input <= 'Z' ) {
        return input - 'A' + 10;
    } else if (input >= '0' && input <= '9') {
        return input - '0';
    } else if (input >= 'a' && input <= 'z' ) {
        return input - 'a'  + 10;
    }
    throw invalid_argument("Not a valid hex character");
}


char twoHexItemsToChar(char first, char second) {
    charItem payload;
    payload.field.hf1 = hexaToDecimal(first);
    payload.field.hf2 = hexaToDecimal(second);
    return payload.result;
}

string XORBreaker::hexStringToText(string input) {
    uint64_t length = input.size() - 1;
    string payload;
    payload.reserve((length / 2) + 1);
    int i = 0;
    while (i < length) {
        payload.push_back(twoHexItemsToChar(input.at(i), input.at(i+1)));
        i += 2;
    }
    return payload;
}

vector<Item> XORBreaker::predefineProbableKeySizes() {
    vector<Item> estimates;
    for(Item i: _hammingDistances) {
        if (i.hammingRatio < _expectedDistance) {
            estimates.push_back(i);
        }
    }
    sort(estimates.begin(), estimates.end(), Item::sortBykeylength);

    return estimates;

}


string XORBreaker::generateStringByKeylength(uint64_t position, uint64_t keylength) {
    string payload;
    uint64_t payloadlength = _payload.size();
    while (position < payloadlength) {
        payload.push_back(_payload.at(position));
        position += keylength;
    }
    return payload;
}



/**
 * TODO: Key Part
 * And it should work!
 * */
string XORBreaker::generateResultFromStringAndChar(string data, uint8_t item) {
    string payload;
    uint64_t length = data.size();
    uint64_t j = 0;
    for (int i = 0; i < length;) {
        uint8_t current = data[i++] << 4;
        if (i < length) {
            current |= data[i++];
        }
        payload.push_back(current ^ item);
    }
    return payload;
}




uint8_t XORBreaker::getProbableCharForEncoding(string text, Item item) {
    long highest = 0;
    long last = 0;
    uint8_t bestMatch = 0;
    for (uint16_t i = 1; i < 255; i++) {
        string copy = generateResultFromStringAndChar(text, i);
        last = LanguageChecker::isValidEnglishText(copy);
        if (last >= highest) {
            highest = last;
            bestMatch = i;
        }
    }
    return bestMatch;
}


string XORBreaker::decryptSingleElement(Item item) {
    string payload;
    for (uint64_t i = 0; i < item.keylength; i++) {
        string fragmentedText = generateStringByKeylength(i, item.keylength);
        char current = getProbableCharForEncoding(fragmentedText, item);
        payload.push_back(current);
    }
    return payload;
}



vector<Item> XORBreaker::decrypt() {
    //get probable keysize
    generateHammingDistances();
    
    // for the best matches run the decrypter
    vector<Item> probableMatches = predefineProbableKeySizes();
    for (Item i: probableMatches) {
        i.key = decryptSingleElement(i);
    }
    return probableMatches;
}



