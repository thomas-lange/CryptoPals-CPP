//
// Created by letigre on 6/22/16.
//

#ifndef CRYPTOPALS_LANGUAGECHECKER_H
#define CRYPTOPALS_LANGUAGECHECKER_H


#include <iostream>
#include <vector>
#include <bitset>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

class LanguageChecker {

    static const string rare_english_letters;
    static const string frequent_english_letters;
    static const string special_characters;
    static const float valid_offset;
    static const string valid_characters;
    static const map<char, float> english_frequency_map;

public:
    static int isValidEnglishText(string input);
};


#endif //CRYPTOPALS_LANGUAGECHECKER_H
