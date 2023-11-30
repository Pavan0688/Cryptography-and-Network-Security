#include <stdio.h>

#define BLOCK_SIZE_64 8
#define BLOCK_SIZE_128 16

#define CONST_RB_64 0x1B
#define CONST_RB_128 0x87

void leftShift(unsigned char *input, int size) {
    int i;
    unsigned char overflow = 0;
    for (i = 0; i < size; ++i) {
        unsigned char nextOverflow = input[i] >> 7;
        input[i] = (input[i] << 1) | overflow;
        overflow = nextOverflow;
    }
}

void xorWithConstant(unsigned char *input, int size, unsigned char constant) {
    input[size - 1] ^= constant;
}


void generateSubkey(unsigned char *subkey, int block_size, unsigned char const_Rb) {

    unsigned char block[BLOCK_SIZE_128] = {0};

    leftShift(block, block_size);

    if (block[0] & 0x80) {
        xorWithConstant(block, block_size, const_Rb);
    }

    for (int i = 0; i < block_size; ++i) {
        subkey[i] = block[i];
    }
}

int main() {
    unsigned char subkey_64[BLOCK_SIZE_64];
    unsigned char subkey_128[BLOCK_SIZE_128];

    generateSubkey(subkey_64, BLOCK_SIZE_64, CONST_RB_64);

    generateSubkey(subkey_128, BLOCK_SIZE_128, CONST_RB_128);

    printf("Subkey for 64-bit block size: ");
    for (int i = 0; i < BLOCK_SIZE_64; ++i) {
        printf("%02X ", subkey_64[i]);
    }
    printf("\n");

    printf("Subkey for 128-bit block size: ");
    for (int i = 0; i < BLOCK_SIZE_128; ++i) {
        printf("%02X ", subkey_128[i]);
    }
    printf("\n");

    return 0;
}

