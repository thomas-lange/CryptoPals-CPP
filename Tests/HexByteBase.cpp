#include <iostream>
#include <vector>

using namespace std;

char hexa[] = "0123456789abcdef";


vector<uint8_t> stringToByteArray(string input) {
    int size = input.size();
    vector<uint8_t> payload;
    for (int i = 0; i < size; i++) {
        payload.push_back(input.at(i));
    }
    return payload;
}

string byteArrayToHexa(vector<uint8_t> input) {
    int size = input.size();
    string payload;
    payload.reserve(size * 2);
    for (int i = 0; i < size; i++) {
        payload.push_back(hexa[input[i] >> 4]);
        payload.push_back(hexa[input[i] & 0xF]);
    }
    return payload;
}

void printAsHexa(vector<uint8_t> input) {
    int size = input.size();
    for (int i = 0; i < size; i++) {
        cout << hex << (int) input.at(i);
    }
}



int main()
{
    cout << "Hello World" << endl; 
    string foo = "kjasdhkljsdhklsjdhkjsdkjhsdkjhksjhdfkhsdkjhdfgkjnbklj3nq5ekhbtaoduneqovjheoqrt";
//   cout << foo.size() << endl;
    vector<uint8_t> bar = stringToByteArray(foo);
//   cout << bar.size() << endl;
    string abc = byteArrayToHexa(bar);
    cout << "=========================" << endl;
    cout << abc << endl;
    cout << "=========================" << endl;
    printAsHexa(bar);
      
   return 0;
}
