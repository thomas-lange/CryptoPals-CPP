//
// Created by letigre on 5/16/16.
//

#include <iostream>
#include "Converter.h"

using namespace std;

int main() {
    Converter c("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
    string result;
    for (int i = 0; i < 256; i++) {
        result = c.hexToStringWithXor(i);
        if (Converter::isValidEnglishText(result)) {
            printf(">> %d / %c >> ", i, i);
            printf(result.c_str());
            cout<< "\nBitset for given value: " << bitset<16>(i)<<endl;
        }
    }
    return 0;
}