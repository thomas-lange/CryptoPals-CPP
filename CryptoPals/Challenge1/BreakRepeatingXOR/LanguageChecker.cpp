//
// Created by letigre on 6/22/16.
//

#include "LanguageChecker.h"

const string LanguageChecker::frequent_english_letters = "ETAOIN";
const string LanguageChecker::rare_english_letters = "SHRDLCUMWFGYPBVKJXQZ";
const string LanguageChecker::special_characters = "/*+|<>[]{}()@$%&\"~;:_0123456789";

const float LanguageChecker::valid_offset = 0.07;
const map<char, float> LanguageChecker::english_frequency_map = {{'E', 0.01270},
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


int LanguageChecker::isValidEnglishText(string input) {
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
//    NB: We will ignore special characters for now
//    for (char c: special_characters) {
//        if (comparator[c] > 0) {
//            matchScore -= 20 * comparator[c];
//            length--;
//        }
//    }
    for (char c: frequent_english_letters) {
        if (comparator[c] > 0) {
            matchScore += 10;
            float val = LanguageChecker::english_frequency_map.at(c);
            float percentage = (float) comparator[c] / length;
            if (percentage > (val + valid_offset) && percentage < (val - valid_offset)) {
                matchScore +=15;
            }
        }
    }
    for (char c: rare_english_letters) {
        if (comparator[c] > 0 ) {
            matchScore += 5;
            float val = LanguageChecker::english_frequency_map.at(c);
            float percentage = (float) comparator[c] / length;
            if (percentage > (val - valid_offset) && percentage < (val + valid_offset)) {
                matchScore +=15;
            }
        }
    }
    return matchScore;
}