#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void encrypt(char *plaintext, char *key_stream) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; ++i) {
        if (isalpha(plaintext[i])) {
            int shift = key_stream[i] - 'A'; 
            if (islower(plaintext[i])) {
                plaintext[i] = 'a' + (plaintext[i] - 'a' + shift) % 26;
            } else {
                plaintext[i] = 'A' + (plaintext[i] - 'A' + shift) % 26;
            }
        }
    }
}

void decrypt(char *ciphertext, char *key_stream) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; ++i) {
        if (isalpha(ciphertext[i])) {
            int shift = key_stream[i] - 'A'; 
            if (islower(ciphertext[i])) {
                ciphertext[i] = 'a' + (ciphertext[i] - 'a' - shift + 26) % 26;
            } else {
                ciphertext[i] = 'A' + (ciphertext[i] - 'A' - shift + 26) % 26;
            }
        }
    }
}

void generate_key_stream(char *key_stream, int length) {
    srand(time(NULL));
    for (int i = 0; i < length; ++i) {
        key_stream[i] = 'A' + rand() % 26; 
    }
    key_stream[length] = '\0'; 
}

int main() {
    char plaintext[1000];
    char key_stream[1000];
    char ciphertext[1000];

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

    int len = strlen(plaintext);

    generate_key_stream(key_stream, len);

    strcpy(ciphertext, plaintext); 
    encrypt(ciphertext, key_stream);

    printf("Encrypted ciphertext: %s\n", ciphertext);

    decrypt(ciphertext, key_stream);

    printf("Decrypted plaintext: %s\n", ciphertext);

    return 0;
}

OUTPUT :

Enter plaintext: Hello, World!

Encrypted ciphertext: Cqcys, Zjwrl!
Decrypted plaintext: Hello, World!
