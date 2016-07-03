//
// Created by letigre on 5/23/16.
//

#include <stdexcept>
#include "Encrypter.h"

struct halves {
    uint8_t h2: 4;
    uint8_t h1: 4;
};


union item {
    char item;
    halves h;
};

char hex[] = "0123456789abcdef";

string Encrypter::encrypt(string input, string key) {
    uint64_t length = key.size();
    if (length == 0) {
        return input;
    }
    uint64_t position = 0;
    string payload;
    payload.reserve(length * 2);
    item i;
    for (char &c: input) {
        i.item = c ^ key.at(position);
        payload.push_back(hex[i.h.h1]);
        payload.push_back(hex[i.h.h2]);
        position = (position + 1) % length;
    }
    return payload;
}

