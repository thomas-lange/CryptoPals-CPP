/**
 * This is kind of a playground
 *
 **/
#include <iostream>
#include <vector>


using namespace std;

class Converter {

    string _input;
    bool _hexGenerated;
    vector<uint8_t> _hex;

public:
    static const string base64_chars;
    static const string hex_chars;

    Converter(string input) {
        _input = input;
        _hexGenerated = false;
    };

    string getHex() {
        if (!_hexGenerated) {
            _hex = generateHex(_input);
            _hexGenerated = true;
        }
        string payload;
        for (uint8_t u: _hex) {
            payload.push_back(hex_chars[u]);
        }
        return payload;
    }

    string xorHexAgainstHex(string input) {
        if (!_hexGenerated) {
            _hex = generateHex(_input);
            _hexGenerated = true;
        }
        vector<uint8_t> xorElement = generateHex(input);
        uint32_t length = _hex.size();
        if (length != xorElement.size()) {
            return string("Sizes of HexElements must match");
        }
        string payload;
        for (uint32_t i = 0; i < length; i++) {
            uint8_t item = _hex[i] ^xorElement[i];
            payload.push_back(hex_chars[item]);
        }
        return payload;
    }

private:
    vector<uint8_t> generateHex(string input) {
        vector<uint8_t> payload;
        for (char c: input) {
            int item = charToHex(c);
            if (item >= 0) {
                payload.push_back(item);
            }
        }
        return payload;
    }

    int charToHex(char item) {
        if (item >= 'A' && item <= 'Z') {
            return item - 'A' + 10;
        } else if (item >= '0' && item <= '9') {
            return item - '0';
        } else if (item >= 'a' && item <= 'z') {
            return item - 'a' + 10;
        }
        return -1;
    }
};


const string Converter::base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const string Converter::hex_chars = "0123456789ABCDEF";


int main() {
    Converter c("1c0111001f010100061a024b53535009181c");
    string s = c.getHex();
    printf(s.c_str());
    printf("\n");

    string x = c.xorHexAgainstHex("686974207468652062756c6c277320657965");
    printf(x.c_str());
    printf("\n");

    return 0;
}