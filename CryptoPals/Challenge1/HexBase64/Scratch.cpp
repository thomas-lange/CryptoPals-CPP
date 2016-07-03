//
// Created by letigre on 5/15/16.
//

static const string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


struct a_s {
    uint8_t b : 4;
    uint8_t a : 4;
};

struct b_s {
    uint8_t b : 2;
    uint8_t a : 6;
};


union c_u {
    a_s a;
    b_s b;
    uint8_t c;
};


void bitFields() {
    /***
     * 1. Playing with structs and bitfields
    ***/
    c_u c;
    c.b.a = 0;
    c.b.b = 1;
    cout<<bitset<8>(c.c)<<std::endl;
    int x = 9995;
    cout<<std::bitset<sizeof(x)*8>(x)<<std::endl;
    cout<<std::bitset<sizeof(int)>(x)<<std::endl;
}


void binaryShift() {
    /***
 * Playing with binary shifts and the like
 ***/
    //
    uint32_t ui32 = 0;
    cout<<std::bitset<sizeof(ui32)*8>(ui32)<<std::endl;
    cout<<std::endl;
    uint32_t item;
    // Zahlen von 0-5 (Hexa) in einen uint geschrieben
    for (int i = 0; i < 6; i++) {
        ui32 |= i << 24 - (i * 4);
        cout<<i<<std::endl;
        cout<<std::bitset<sizeof(ui32)*8>(ui32)<<std::endl;
    }

    cout<<std::endl;

    // Lesen der Zahlen als Hex (4Bit)
    for (int i = 0; i < 6; i++) {
        item = (ui32 >> 24 - (i * 4)) & 15;
        cout<<std::bitset<32>(item)<<std::endl;
    }

    cout<<std::endl;

//    // Lesen der Zahlen als Base64 (6Bit)
    for (int i = 0; i < 6; i++) {
        item = (ui32 >> 24 - (i * 6)) & 63;
        cout<<std::bitset<32>(item)<<std::endl;
        cout<<item<<std::endl;
        cout<<base64_chars[item]<<std::endl;
    }

    cout<<std::bitset<sizeof(ui32)*8>(ui32)<<std::endl;
}


/***
 * Set first (width) Bytes to item at position
 * This will null out the existing bytes previously!
 */
uint32_t setToUint32AtWidth(uint32_t item, uint32_t value, uint from, uint width) {
    uint32_t mask = ~0u;
    mask >>= 32 - width;
    value &= mask;
    cout<<std::bitset<32>(value)<<std::endl;
    mask <<= from;
    cout<<std::bitset<32>(item)<<std::endl;
    item ^= mask; // null corresponding area
    cout<<std::bitset<32>(mask)<<std::endl;
    cout<< std::bitset<32>(item)<< "<<<" << std::endl;
    value <<= from;
    cout<<std::bitset<32>(value)<<std::endl;
    cout<<std::bitset<32>(item & value)<<std::endl;
    cout<<std::endl;
    return item & value;
}