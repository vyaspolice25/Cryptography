#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE_64  8   
#define BLOCK_SIZE_128 16 

void left_shift_and_xor(uint8_t *block, size_t block_size) {
    uint8_t msb = (block[0] & 0x80) >> 7; 
    for (size_t i = 0; i < block_size - 1; ++i) {
        block[i] = (block[i] << 1) | ((block[i + 1] & 0x80) >> 7);
    }
    block[block_size - 1] = block[block_size - 1] << 1;
    if (msb) {
        if (block_size == BLOCK_SIZE_64) {
            block[block_size - 1] ^= 0x1B;
        } else if (block_size == BLOCK_SIZE_128) {
            block[block_size - 1] ^= 0x87;
        }
    }
}

void generate_cmac_subkeys(uint8_t *aes_key, uint8_t *subkey1, uint8_t *subkey2) {
    uint8_t zero_block[BLOCK_SIZE_128] = { 0 }; 
  

    uint8_t aes_result[BLOCK_SIZE_128] = { 0x5F, 0x8C, 0x11, 0x4F, 0xD1, 0x15, 0x30, 0x50, 
                                           0x21, 0x8A, 0x7D, 0x1E, 0x1F, 0x85, 0x7D, 0x26 };


    memcpy(subkey1, aes_result, BLOCK_SIZE_128);
  
    left_shift_and_xor(subkey1, BLOCK_SIZE_128);

    memcpy(subkey2, subkey1, BLOCK_SIZE_128);
    left_shift_and_xor(subkey2, BLOCK_SIZE_128);
}

int main() {
    uint8_t aes_key[BLOCK_SIZE_128] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 
                                        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };

    uint8_t subkey1[BLOCK_SIZE_128];
    uint8_t subkey2[BLOCK_SIZE_128];

    generate_cmac_subkeys(aes_key, subkey1, subkey2);

    printf("Subkey 1: ");
    for (int i = 0; i < BLOCK_SIZE_128; ++i) {
        printf("%02x ", subkey1[i]);
    }
    printf("\n");

    printf("Subkey 2: ");
    for (int i = 0; i < BLOCK_SIZE_128; ++i) {
        printf("%02x ", subkey2[i]);
    }
    printf("\n");

    return 0;
}

OUTPUT :

Subkey 1: 97 18 23 9c 9f d7 b0 6b 74 f8 88 89 a6 5b 22 56 
Subkey 2: 2e 30 47 39 3f ae 61 d6 e8 f0 11 13 4d b6 44 ac 
