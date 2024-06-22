#include <stdio.h>
#include <string.h>
#include <ctype.h>

void vigenereEncrypt(char plaintext[], char key[], char ciphertext[]);

int main() {
    char key[100], plaintext[100], ciphertext[100];

    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    vigenereEncrypt(plaintext, key, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

void vigenereEncrypt(char plaintext[], char key[], char ciphertext[]) {
    int i, j;
    int textLen = strlen(plaintext);
    int keyLen = strlen(key);
    char keyStream[textLen];

    for (i = 0, j = 0; i < textLen; i++) {
        if (isalpha(plaintext[i])) {
            keyStream[i] = toupper(key[j % keyLen]);
            j++;
        } else {
            keyStream[i] = plaintext[i]; // Non-alphabet characters are unchanged
        }
    }

    for (i = 0; i < textLen; i++) {
        if (isupper(plaintext[i])) {
            ciphertext[i] = ((plaintext[i] - 'A') + (keyStream[i] - 'A')) % 26 + 'A';
        } else if (islower(plaintext[i])) {
            ciphertext[i] = ((plaintext[i] - 'a') + (keyStream[i] - 'A')) % 26 + 'a';
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabet characters are unchanged
        }
    }
    ciphertext[textLen] = '\0';
}

OUOTPUT :

Enter the keyword: KEY
Enter the plaintext: HELLO WORLD
Ciphertext: RIJVS UYVJN
