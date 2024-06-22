#include <stdio.h>
#include <stdint.h>

const int initial_permutation_key[] = { 57, 49, 41, 33, 25, 17, 9,
                                        1, 58, 50, 42, 34, 26, 18,
                                        10, 2, 59, 51, 43, 35, 27,
                                        19, 11, 3, 60, 52, 44, 36,
                                        63, 55, 47, 39, 31, 23, 15,
                                        7, 62, 54, 46, 38, 30, 22,
                                        14, 6, 61, 53, 45, 37, 29,
                                        21, 13, 5, 28, 20, 12, 4 };

const int compression_permutation[] = { 14, 17, 11, 24, 1, 5,
                                        3, 28, 15, 6, 21, 10,
                                        23, 19, 12, 4, 26, 8,
                                        16, 7, 27, 20, 13, 2,
                                        41, 52, 31, 37, 47, 55,
                                        30, 40, 51, 45, 33, 48,
                                        44, 49, 39, 56, 34, 53,
                                        46, 42, 50, 36, 29, 32 };

const int left_shifts[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

void permute(uint64_t *block, const int *permutation, int size) {
    uint64_t temp = 0;
    uint64_t result = 0;
    for (int i = 0; i < size; i++) {
        temp = (*block >> (64 - permutation[i])) & 0x01ULL;
        result |= (temp << (size - 1 - i));
    }
    *block = result;
}

void generate_subkeys(uint64_t initial_key, uint64_t *subkeys) {
   
    permute(&initial_key, initial_permutation_key, 56);

    uint32_t left = initial_key >> 28;
    uint32_t right = initial_key & 0x0FFFFFFF;

    for (int round = 0; round < 16; round++) {
        
        left = ((left << left_shifts[round]) | (left >> (28 - left_shifts[round]))) & 0x0FFFFFFF;
        right = ((right << left_shifts[round]) | (right >> (28 - left_shifts[round]))) & 0x0FFFFFFF;

        uint64_t combined_key = ((uint64_t)left << 28) | right;

        permute(&combined_key, compression_permutation, 48);

        subkeys[round] = combined_key;
    }
}

int main() {

    uint64_t initial_key = 0x123456789ABCDE;

    uint64_t subkeys[16];

    generate_subkeys(initial_key, subkeys);

    printf("Generated Subkeys:\n");
    for (int i = 0; i < 16; i++) {
        printf("Round %2d: 0x%012llX\n", i + 1, subkeys[i]);
    }

    return 0;
}

OUTPUT :

Generated Subkeys:
Round  1: 0x00001562B84C
Round  2: 0x00002C4B7098
Round  3: 0x00005962B850
Round  4: 0x00004C4B7090
Round  5: 0x0000B762B84C
Round  6: 0x000064B70980
Round  7: 0x0000D162B850
Round  8: 0x0000C84B7090
Round  9: 0x00017562B84C
Round 10: 0x00002CB70980
Round 11: 0x0000B162B850
Round 12: 0x0000244B7090
Round 13: 0x00011562B84C
Round 14: 0x00002C2B7098
Round 15: 0x0000A962B850
Round 16: 0x0000644B7090
