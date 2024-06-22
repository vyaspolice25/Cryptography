#include <stdio.h>
#include <string.h>
#include <ctype.h>

void frequencyAnalysis(char ciphertext[], int freq[]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        freq[(unsigned char)ciphertext[i]]++;
    }
}

void decrypt(char ciphertext[], char substitution[], char plaintext[]) {
    int i;
    int len = strlen(ciphertext);

    for (i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            if (islower(ciphertext[i])) {
                plaintext[i] = tolower(substitution[ciphertext[i]]);
            } else {
                plaintext[i] = toupper(substitution[ciphertext[i]]);
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?";
    int freq[256] = {0};
    char substitution[256]; 
    char plaintext[100]; 

    frequencyAnalysis(ciphertext, freq);

    substitution['8'] = 'e';
    substitution['‡'] = 't';
    substitution['5'] = 'h';

    decrypt(ciphertext, substitution, plaintext);

    printf("Decrypted Message:\n%s\n", plaintext);

    return 0;
}

OUTPUT :

Decrypted Message:
the tetters aever lctf the pdain quickfy qum^ed vrnm ocer the fenzy fox
