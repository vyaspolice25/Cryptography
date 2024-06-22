#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ALPHABET_SIZE 26

void matrixMultiply(int key[2][2], int plain[2], int result[2]) {
    result[0] = (key[0][0] * plain[0] + key[0][1] * plain[1]) % ALPHABET_SIZE;
    result[1] = (key[1][0] * plain[0] + key[1][1] * plain[1]) % ALPHABET_SIZE;
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 1;
}

int determinant(int key[2][2]) {
    return (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % ALPHABET_SIZE;
}

void matrixInverse(int key[2][2], int inverse[2][2]) {
    int det = determinant(key);
    int detInv = modInverse(det, ALPHABET_SIZE);

    inverse[0][0] = key[1][1] * detInv % ALPHABET_SIZE;
    inverse[0][1] = -key[0][1] * detInv % ALPHABET_SIZE;
    inverse[1][0] = -key[1][0] * detInv % ALPHABET_SIZE;
    inverse[1][1] = key[0][0] * detInv % ALPHABET_SIZE;

    if (inverse[0][1] < 0) inverse[0][1] += ALPHABET_SIZE;
    if (inverse[1][0] < 0) inverse[1][0] += ALPHABET_SIZE;
    if (inverse[1][1] < 0) inverse[1][1] += ALPHABET_SIZE;
}

void hillEncrypt(int key[2][2], char plaintext[2], char ciphertext[2]) {
    int plainNum[2], cipherNum[2];

    plainNum[0] = plaintext[0] - 'A';
    plainNum[1] = plaintext[1] - 'A';

    matrixMultiply(key, plainNum, cipherNum);

    ciphertext[0] = cipherNum[0] + 'A';
    ciphertext[1] = cipherNum[1] + 'A';
}
void hillDecrypt(int key[2][2], char ciphertext[2], char plaintext[2]) {
    int cipherNum[2], plainNum[2], keyInverse[2][2];

    cipherNum[0] = ciphertext[0] - 'A';
    cipherNum[1] = ciphertext[1] - 'A';

    matrixInverse(key, keyInverse);
    matrixMultiply(keyInverse, cipherNum, plainNum);

    plaintext[0] = plainNum[0] + 'A';
    plaintext[1] = plainNum[1] + 'A';
}

int main() {
    int key[2][2] = {{3, 2}, {5, 7}}; 
    char plaintext[2] = "PL";
    char ciphertext[2];

    hillEncrypt(key, plaintext, ciphertext);
    printf("Ciphertext: %c%c\n", ciphertext[0], ciphertext[1]);

    char decrypted[2];
    hillDecrypt(key, ciphertext, decrypted);
    printf("Decrypted plaintext: %c%c\n", decrypted[0], decrypted[1]);

    return 0;
}

OUTPUT :

Ciphertext: EU
Decrypted plaintext: PL
