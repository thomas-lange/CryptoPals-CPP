//
// Created by letigre on 5/23/16.
//

#include "Encrypter.h"

int main() {
    Encrypter e;
    string ret = e.encrypt("Burning 'em, if you ain't quick and nimble\n"
                                   "I go crazy when I hear a cymbal", "ICE");
    printf(ret.c_str());
}