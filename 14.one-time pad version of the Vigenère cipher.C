#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

int charToIndex(char ch) {
    return toupper(ch) - 'A';
}

char indexToChar(int index) {
    return index + 'A';
}

void encryptVigenere(char plaintext[], int key[], int keyLength, char ciphertext[]) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            int p = charToIndex(plaintext[i]);
            int k = key[i % keyLength];
            int c = (p + k) % ALPHABET_SIZE;
            ciphertext[i] = indexToChar(c);
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[len] = '\0';
}

void decryptVigenere(char ciphertext[], int key[], int keyLength, char decrypted[]) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            int c = charToIndex(ciphertext[i]);
            int k = key[i % keyLength];
            int p = (c - k + ALPHABET_SIZE) % ALPHABET_SIZE;
            decrypted[i] = indexToChar(p);
        } else {
            decrypted[i] = ciphertext[i]; 
        }
    }
    decrypted[len] = '\0';
}

int main() {
    char plaintext[] = "SENDMOREMONEY";
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    char ciphertext[100];
    char decrypted[100];

    encryptVigenere(plaintext, key, sizeof(key) / sizeof(key[0]), ciphertext);
    printf("Encrypted Ciphertext: %s\n", ciphertext);

    char desiredPlaintext[] = "CASHNOTNEEDED";
    int keyLength = sizeof(key) / sizeof(key[0]);
    int foundKey[keyLength];

    for (int k = 0; k < ALPHABET_SIZE; k++) {
        decryptVigenere(ciphertext, &k, 1, decrypted);
        if (strcmp(decrypted, desiredPlaintext) == 0) {
            foundKey[0] = k;
            for (int i = 1; i < keyLength; i++) {
                foundKey[i] = key[i] - foundKey[0];
                if (foundKey[i] < 0) {
                    foundKey[i] += ALPHABET_SIZE;
                }
            }
            break;
        }
    }

    printf("Found Key: ");
    for (int i = 0; i < keyLength; i++) {
        printf("%d ", foundKey[i]);
    }
    printf("\n");

    return 0;
}

OUTPUT :

Encrypted Ciphertext: ZEOTXFLBOPQZOWQAZENRDOYEEG
Found Key: 9 0 1 7 23 15 21 14 11 11 2 8 9
