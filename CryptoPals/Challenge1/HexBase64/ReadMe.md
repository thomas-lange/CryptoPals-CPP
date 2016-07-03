# Base64 Encoding for Hex

Both input and output will be strings.
The issue here was to be as close to bit operations as possible.

What is Base64:
It is a Mapping from Elements to 6 Byte long elements:

![Mapping](/home/letigre/Notebook/CPP/CryptoPals/Challenge1/HexBase64/Images/CharBase64.png  "Mapping")

|Cryptopals Rule|
|----|
| Always operate on raw bytes, never on encoded strings. Only use hex and base64 for pretty-printing.



**What I did:**
1. I transformed the chars to their respective hex value (obvious)
2. I wrote the values into a union of 2 structs (bitfields)
    - struct1: 6 * 4 bits (hex = 4 bits)
    - struct2: 4 * 6 bits (base64 = 6 bits)
    1. first i wrote each hex value into the struct1 containers
3. then i transformed this union via struct2 into chars again
4. returned the string


## What is good about this implementation?
It is very close to the actual way Base64 works. As this was intended to familarize myself with
Encrypting and Decrypting, this was a good way to start.

## What is bad about this implementation?
It is not portable at all. As bitfield structs are (from what I have gathered so far) very poorly defined
it will conflict with different compilers and little - or big endian machines. This can result in hard to
track and debug issues.

I learned this the hard way, when it took me 2h to find out, that my bitfields started from the end
of the field. This is **very** relevant in this case, as the field has the size of a 32bit uint, and the
elements only reqire 24 bits.

## What would be alternatives?
It should be possible to use bitwise shifting or bitwise or instead.
A example solution from [0x41414141](http://stackoverflow.com/users/2077131/0x41414141) was here:

``` c++

char* hex_to_base64(char *hex, int size)
{
    int size64 = (size * 2) / 3.0;
    size64 += 1;
    char *base64 = calloc(size64, 1);
    size64 -= 1;
    for (int i = size-1; i>= 0; i-=3, size64-=2) {
        base64[size64] |= hex[i];
        if (i > 0) {
            base64[size64] |= ((hex[i - 1] << 4) & 0x3F); //0x3F is 00111111
            base64[size64 - 1] |= (hex[i - 1] >> 2);
        }
        if (i > 1) {
            base64[size64 - 1] |= ((hex[i - 2] << 2));
        }
    }
    return base64;
}


```


## Example Implementation with Binary Operators and witout bitfields :
I tried a simple implementation with binary operators instead of a bit-field. It is shown below:
It consists of:
* a function to place values within a certain range of a uint_32
* a function to retrieve from a given item at a certain range

``` c++

/**
 * Retrieve a specific bit range from a uint32
 */
uint32_t getFromUint32AtWidth(uint32_t &item, uint from, uint width) {
    uint32_t mask = ~0u;
    mask >>= 32 - width;
    return (item >> from) & mask;
}


/***
 * Set first (width) Bytes to item at position
 * This will null out the existing bytes previously!
 */
uint32_t setToUint32AtWidth(uint32_t item, uint32_t value, uint from, uint width) {
    uint32_t mask = ~0u;
    mask >>= 32 - width;
    value &= mask;
    mask <<= from;
    item &= ~mask; // null corresponding area
    value <<= from;
    return item | value;
}


```

This can then be used like:

``` c++

int main() {
    static const string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    uint32_t payload = 0;
    for (uint8_t i = 1; i <= 6 ; i++) {
        payload = setToUint32AtWidth(payload, i, 32 - 4 * i, 4);
    }

    cout<<std::bitset<32>(payload)<<std::endl;
    cout << "Printing Base64" << std::endl;
    for (int i = 1; i <= 4; i++) {
        uint8_t item = getFromUint32AtWidth(payload, 32 - 6 * i, 6);
        char c = base64_chars[item];
        cout<<std::bitset<8>(item)<< " : " << (uint)item<<" : " << c << std::endl;
    }
}

```

**This results in:**

```

00010010001101000101011000000000
Printing Base64
00000100 : 4 : E
00100011 : 35 : j
00010001 : 17 : R
00010110 : 22 : W

```


##Further Ideas:
Best would be, to solve this via a (bitfield) class. This could handle a range of input (like for 4 chars)
 and then hand back the corresponding results. This would reduce a lot of the read and write overhead
 that is still in this very schematic solution.