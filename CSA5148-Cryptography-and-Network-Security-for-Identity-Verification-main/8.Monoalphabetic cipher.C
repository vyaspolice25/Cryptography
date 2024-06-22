#include <stdio.h>
#include <string.h>
#include <ctype.h>
void generateCipherMapping(char keyword[], char cipherMap[]) {
    int i, j;
    char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
    int keywordLen = strlen(keyword);
    int alphabetLen = 26;

    for (i = 0; i < keywordLen; i++) {
        if (isalpha(keyword[i])) {
            keyword[i] = tolower(keyword[i]); 
            cipherMap[i] = keyword[i];
        }
    }

    j = keywordLen;
    for (i = 0; i < alphabetLen; i++) {
        if (!strchr(keyword, alphabet[i])) {
            cipherMap[j++] = alphabet[i];
        }
    }

    cipherMap[j] = '\0';
}

void encrypt(char plaintext[], char cipherMap[], char ciphertext[]) {
    int i;
    int len = strlen(plaintext);

    for (i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            if (islower(plaintext[i])) {
                ciphertext[i] = tolower(cipherMap[plaintext[i] - 'a']);
            } else {
                ciphertext[i] = toupper(cipherMap[plaintext[i] - 'A']);
            }
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[i] = '\0'; 
}

int main() {
    char keyword[] = "CIPHER";
    char plaintext[] = "hello world";
    char cipherMap[26];
    char ciphertext[100];
    generateCipherMapping(keyword, cipherMap);

    encrypt(plaintext, cipherMap, ciphertext);

    printf("Keyword: %s\n", keyword);
    printf("Generated Cipher Mapping: %s\n", cipherMap);
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

OUTPUT :

Keyword: CIPHER
Generated Cipher Mapping: ciphersabdfgjklmnopqtuvwxyz
Plaintext: hello world
Ciphertext: jemmt mtalt
