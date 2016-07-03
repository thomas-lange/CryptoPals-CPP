#include <stdio.h>
#include "HexBase64.h"

using namespace std;


int main() {
    printf("\n\n");
    printf("In HexBase64 Conversion\n");
    printf("===========================\n");
    printf("Version1\n\n");

    printf("Rendering Base64 for(Hex): 0123456789abcdef");
    printf("\n");
    const char* foo = HexBase64::hexToBase64("0123456789abcdef");
    printf(foo);

    printf("\n\n");
    printf("Rendering Base64 for(Hex): 49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d");
    printf("\n");
    foo = HexBase64::hexToBase64("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d");
    printf(foo);
    printf("\n\n");

    return 0;
}