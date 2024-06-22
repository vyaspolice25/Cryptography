#include <stdio.h>
#include <string.h>

const int P10[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
const int P8[] = {6, 3, 7, 4, 8, 5, 10, 9};
const int IP[] = {2, 6, 3, 1, 4, 8, 5, 7};
const int IP_INV[] = {4, 1, 3, 5, 7, 2, 8, 6};
const int EP[] = {4, 1, 2, 3, 2, 3, 4, 1};
const int P4[] = {2, 4, 3, 1};

const int S0[4][4] = {
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {3, 1, 3, 2}
};

const int S1[4][4] = {
    {0, 1, 2, 3},
    {2, 0, 1, 3},
    {3, 0, 1, 0},
    {2, 1, 0, 3}
};

void print_binary(char *label, unsigned char data) {
    printf("%s: ", label);
    for (int i = 7; i >= 0; --i) {
        printf("%d", (data >> i) & 1);
    }
    printf("\n");
}

void permute(unsigned char *input, const int *perm_table, unsigned char *output, int size) {
    for (int i = 0; i < size; ++i) {
        output[i] = (input[perm_table[i] - 1] >> (size - i - 1)) & 1;
    }
}

void left_shift(unsigned char *key, int bits) {
    int temp = key[0];
    for (int i = 0; i < bits; ++i) {
        for (int j = 0; j < 4; ++j) {
            key[j] = key[j + 1];
        }
        key[4] = temp;
        temp = key[0];
    }
}

void generate_subkeys(unsigned char *key, unsigned char *K1, unsigned char *K2) {
    unsigned char temp_key[10];
    permute(key, P10, temp_key, 10);
    left_shift(temp_key, 1);
    permute(temp_key, P8, K1, 8);
    left_shift(temp_key, 2);
    permute(temp_key, P8, K2, 8);
}

void apply_xor(unsigned char *input, unsigned char *key, unsigned char *output, int size) {
    for (int i = 0; i < size; ++i) {
        output[i] = input[i] ^ key[i];
    }
}

void sbox_substitution(unsigned char *input, unsigned char *output) {
    int row = (input[0] << 1) + input[3];
    int col = (input[1] << 1) + input[2];
    unsigned char val = (row == 0 && col == 0) ? S0[0][0] :
                        (row == 0 && col == 1) ? S0[0][1] :
                        (row == 0 && col == 2) ? S0[0][2] :
                        (row == 0 && col == 3) ? S0[0][3] :
                        (row == 1 && col == 0) ? S0[1][0] :
                        (row == 1 && col == 1) ? S0[1][1] :
                        (row == 1 && col == 2) ? S0[1][2] :
                        (row == 1 && col == 3) ? S0[1][3] :
                        (row == 2 && col == 0) ? S0[2][0] :
                        (row == 2 && col == 1) ? S0[2][1] :
                        (row == 2 && col == 2) ? S0[2][2] :
                        (row == 2 && col == 3) ? S0[2][3] :
                        (row == 3 && col == 0) ? S0[3][0] :
                        (row == 3 && col == 1) ? S0[3][1] :
                        (row == 3 && col == 2) ? S0[3][2] :
                        S0[3][3];

    output[0] = (val >> 1) & 1;
    output[1] = val & 1;

    row = (input[4] << 1) + input[7];
    col = (input[5] << 1) + input[6];
    val = (row == 0 && col == 0) ? S1[0][0] :
          (row == 0 && col == 1) ? S1[0][1] :
          (row == 0 && col == 2) ? S1[0][2] :
          (row == 0 && col == 3) ? S1[0][3] :
          (row == 1 && col == 0) ? S1[1][0] :
          (row == 1 && col == 1) ? S1[1][1] :
          (row == 1 && col == 2) ? S1[1][2] :
          (row == 1 && col == 3) ? S1[1][3] :
          (row == 2 && col == 0) ? S1[2][0] :
          (row == 2 && col == 1) ? S1[2][1] :
          (row == 2 && col == 2) ? S1[2][2] :
          (row == 2 && col == 3) ? S1[2][3] :
          (row == 3 && col == 0) ? S1[3][0] :
          (row == 3 && col == 1) ? S1[3][1] :
          (row == 3 && col == 2) ? S1[3][2] :
          S1[3][3];

    output[2] = (val >> 1) & 1;
    output[3] = val & 1;
}

void initial_permutation(unsigned char *input, unsigned char *output) {
    permute(input, IP, output, 8);
}

void inverse_initial_permutation(unsigned char *input, unsigned char *output) {
    permute(input, IP_INV, output, 8);
}

void expansion_permutation(unsigned char *input, unsigned char *output) {
    permute(input, EP, output, 8);
}

void permutation(unsigned char *input, unsigned char *output) {
    permute(input, P4, output, 4);
}

void round_function(unsigned char *R, unsigned char *subkey) {
    unsigned char expanded_R[8];
    unsigned char temp[8];
    unsigned char sbox_output[4];

    expansion_permutation(R, expanded_R);
    apply_xor(expanded_R, subkey, temp, 8);
    
    sbox_substitution(temp, sbox_output);
    permutation(sbox_output, temp);
    
    apply_xor(temp, R, temp, 4);
    
    for (int i = 0; i < 4; ++i) {
        R[i] = temp[i];
    }
}

void generate_key_stream(unsigned char *IV, unsigned char *key, unsigned char *key_stream, int size) {
    unsigned char K1[8], K2[8];
    generate_subkeys(key

OUTPUT :

Plaintext (binary): 10101010
Key (binary): 1110001110
IV (binary): 11001100

--- Encryption ---
Ciphertext (binary): 11100010

--- Decryption ---
Decrypted plaintext (binary): 10101010
