//
// Created by letigre on 5/24/16.
//


#include <string>
#include <stdexcept>
#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>
#include "XORBreaker.h"

using namespace std;

//struct hexField {
//    uint8_t hf2: 4;
//    uint8_t hf1: 4;
//};
//
//union charItem {
//    hexField field;
//    char result;
//};
//
//
//
//struct Item {
//    uint64_t keylength;
//    uint64_t hamming;
//    float hammingRatio;
//
//    Item(uint64_t _keylength, uint64_t _hamming) {
//        keylength = _keylength;
//        hamming = _hamming;
//        hammingRatio = (float)_hamming / _keylength;
//    }
//
//    Item() {
//        keylength = 0;
//        hamming = 0;
//        hammingRatio = 0;
//    }
//
//    void setUp (uint64_t _keylength, uint64_t _hamming) {
//        keylength = _keylength;
//        hamming = _hamming;
//        hammingRatio = (float) (_hamming / _keylength);
//    }
//};
//
//bool sortByRatio (Item me, Item other) {
//    return me.hammingRatio < other.hammingRatio;
//};
//
//
//vector<Item> getHammingDistances(string input, int lengthStart, int lengthEnd) {
//    int start = min(lengthStart, lengthEnd);
//    int end = max(lengthStart, lengthEnd) + 1;
//    if (end * 2 > input.size()) {
//        throw invalid_argument("The input needs to be at least twice the sice of the maximum lenght!");
//    }
//    vector<Item> results;
//    for (int i = start; i < end; ++i) {
//        results.push_back(Item(i, XORBreaker::hammingDistance(input.substr(0, i), input.substr(i, i ))));
//    }
//    sort(results.begin(), results.end(), sortByRatio);
//    return results;
//}
//
//uint8_t hexaToDecimal(char input) {
//    if (input >= 'A' && input <= 'Z' ) {
//        return input - 'A' + 10;
//    } else if (input >= '0' && input <= '9') {
//        return input - '0';
//    } else if (input >= 'a' && input <= 'z' ) {
//        return input - 'a'  + 10;
//    }
//    throw invalid_argument("Not a valid hex character");
//}
//
//
//char twoHexItemsToChar(char first, char second) {
//    charItem payload;
//    payload.field.hf1 = hexaToDecimal(first);
//    payload.field.hf2 = hexaToDecimal(second);
//    return payload.result;
//}
//
//string hexStringToText(string input) {
//    uint64_t length = input.size() - 1;
//    string payload;
//    payload.reserve((length / 2) + 1);
//    int i = 0;
//    while (i < length) {
//        payload.push_back(twoHexItemsToChar(input.at(i), input.at(i+1)));
//        i += 2;
//    }
//    return payload;
//}
//




int main () {
    string in3 = "3d1f04530a0019000111491811161a0803081c06492f2e214841041512060d044115071b57042b0b0502121a1e0c572e2141491e1253094915081d091b0e411c180c05001d0c495f000048080504532927334d53273b5b41161c0a5e41151a061a413107061b045309051004111a08594127000004411c180c05001d0c4900081f0449140e1e18080504531c1e184111011d044112060d57161a0405571101070d02021648061904530a0003411a06490504071d1b194f533c011615530a0003410401051b41110d49121006090557151c4858570815481d1f04531c1e18411007040700010d0d57031a1c1a5716161a0c57051a0e0f121316061d5b41434800114107000c0e41040d1b124116191c160d5d48311813530d0714130a181d1e0e1d480004411007041a0e1d04105714000d0d57081d481a1217161a081b410011041a04071a0014411001191f04011b495f0400180c14081204050e41322d3a5e4f53294904181e0d1d050810480a1e111b0d1b570800481a1e0c0304105700530b000709161a491e0f531f011e021b481d1f0453030c0e411a1b490212160c49110e01480c190201111903081c0649160f17480d120201111903081c064907131c0b0c04125d483d1f0453302625411c180c05001d0c491e12531b0657000318051e0417481d184116090a1f4111011d5703161c1e12041d481d1f04531c0c0f1553110602410409070341070749120f101a100715530907134107000c570a1611490e0e064f051b41100006181216464932191205191b040048080504530a0c0315161a490309120649000e010c1a5b411f0d1d5012531c081c04531c01124104071b134151100605435d483e12410409070341070749120f101a10071553011d57161a1c0157151b0d491c040a484b140d164a4757271a1a1a0341040d491f00050d49030e530b061917161a1d57151b0d491e0f031d1d57001d0c490309164802121853010757031a06080518531a0c0713161b0c1915121c00180f";

    XORBreaker foo(in3);
    foo.setInputTypeToHexa();
    foo.setKeylength(3, 10);
    vector<Item> result = foo.decrypt();
    return 0;
}