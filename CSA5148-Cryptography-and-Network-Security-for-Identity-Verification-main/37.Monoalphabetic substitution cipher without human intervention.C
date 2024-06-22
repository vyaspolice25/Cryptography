#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26

const float english_freq[ALPHABET_SIZE] = {8.2, 1.5, 2.8, 4.3, 13.0, 2.2, 2.0, 6.1, 7.0, 0.2, 0.8, 4.0, 2.4,
                                           6.7, 7.5, 1.9, 0.1, 6.0, 6.3, 9.1, 2.8, 1.0, 2.4, 0.2, 2.0, 0.1};

void calculate_letter_frequency(const char *text, int *frequency) {
    int i;
    for (i = 0; i < strlen(text); i++) {
        char ch = text[i];
        if (isalpha(ch)) {
            frequency[tolower(ch) - 'a']++;
        }
    }
}

int compare_frequency(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

void decrypt_with_frequency(const char *ciphertext, char *plaintext, char key[]) {
    int frequency[ALPHABET_SIZE] = {0};
    int i, j;

    calculate_letter_frequency(ciphertext, frequency);

    int sorted_freq[ALPHABET_SIZE];
    memcpy(sorted_freq, frequency, sizeof(int) * ALPHABET_SIZE);
    qsort(sorted_freq, ALPHABET_SIZE, sizeof(int), compare_frequency);

    for (i = 0; i < ALPHABET_SIZE; i++) {
        int ciphertext_index = -1;
        for (j = 0; j < ALPHABET_SIZE; j++) {
            if (frequency[j] == sorted_freq[i]) {
                ciphertext_index = j;
                break;
            }
        }
        if (ciphertext_index != -1) {
            int english_index = i;
            key[ciphertext_index] = 'a' + english_index;
        }
    }

    for (i = 0; i < strlen(ciphertext); i++) {
        char ch = ciphertext[i];
        if (isalpha(ch)) {
            plaintext[i] = key[tolower(ch) - 'a'];
        } else {
            plaintext[i] = ch;
        }
    }
    plaintext[i] = '\0';
}

int main() {
    char ciphertext[1000]; 
    char plaintext[1000];
    char key[ALPHABET_SIZE];

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    decrypt_with_frequency(ciphertext, plaintext, key);

    printf("\nDecrypted plaintext (using frequency analysis):\n%s\n", plaintext);

    return 0;
}

OUTPUT :

Enter the ciphertext: Vscd sc kvy kyv tyvfvyl yze zd sc fwijv

Decrypted plaintext (using frequency analysis):
This is one of the possible plaintexts as it is based on frequency
