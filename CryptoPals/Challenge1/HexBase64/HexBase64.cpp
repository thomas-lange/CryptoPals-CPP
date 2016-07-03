#include "HexBase64.h"

using namespace std;
namespace HexBase64 {
    static const string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    struct hex24 {
        uint32_t h6 : 4;
        uint32_t h5 : 4;
        uint32_t h4 : 4;
        uint32_t h3 : 4;
        uint32_t h2 : 4;
        uint32_t h1 : 4;
    };

    struct base64 {
        uint32_t b4 : 6;
        uint32_t b3 : 6;
        uint32_t b2 : 6;
        uint32_t b1 : 6;
    };

    union hexBase64 {
        uint32_t ui;
        base64 b64;
        hex24 h24;
    };


    const char* hexToBase64(const char* input) {
        uint64_t length = strlen(input);
        string payload;
        int i = 0;
        while (i < length) {
            hexBase64 hb64 {0};
            uint8_t item;
            for (int j = 1; j < 7; ) {
                if (i >= length) {
                    item = 0;
                } else {
                    item = charToHex(input[i++]);
                }
                if (item >= 0) {
                    item = (uint8_t) item;
                    switch (j) {
                        case 1:
                            hb64.h24.h1 = item;
                            break;
                        case 2:
                            hb64.h24.h2 = item;
                            break;
                        case 3:
                            hb64.h24.h3 = item;
                            break;
                        case 4:
                            hb64.h24.h4 = item;
                            break;
                        case 5:
                            hb64.h24.h5 = item;
                            break;
                        case 6:
                            hb64.h24.h6 = item;
                            break;
                    }
                    j++;
                }
            }
            payload.push_back(base64_chars[hb64.b64.b1]);
            payload.push_back(base64_chars[hb64.b64.b2]);
            payload.push_back(base64_chars[hb64.b64.b3]);
            payload.push_back(base64_chars[hb64.b64.b4]);
        }
        uint baseStringLength = payload.length() - 1;
        uint padding = length % 3;
        for (int i = 0; i < padding; i++) {
            payload.replace(baseStringLength - i, 1, "=");
        }
        return payload.c_str();
    }

    int charToHex(char item) {
        if (item >= 'A' && item <= 'Z' ) {
            return item - 'A' + 10;
        } else if (item >= '0' && item <= '9') {
            return item - '0';
        } else if (item >= 'a' && item <= 'z' ) {
            return item - 'a'  + 10;
        }
        return -1;
    }


}