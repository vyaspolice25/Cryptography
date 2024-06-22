#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

float englishFreq[26] = {8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0, 0.2, 0.8, 4.0, 2.4,
                         6.7, 7.5, 1.9, 0.1, 6.0, 6.3, 9.1, 2.8, 1.0, 2.4, 0.2, 2.0, 0.1};

void decrypt(char *ciphertext, char *key, char *plaintext) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = key[ciphertext[i] - base];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

float calculateFrequencyScore(char *plaintext) {
    int count[26] = {0};
    int totalLetters = 0;

    for (int i = 0; i < strlen(plaintext); i++) {
        if (isalpha(plaintext[i])) {
            count[tolower(plaintext[i]) - 'a']++;
            totalLetters++;
        }
    }

    float score = 0.0;
    for (int i = 0; i < 26; i++) {
        float freq = (float)count[i] / totalLetters * 100.0;
        score += fabs(freq - englishFreq[i]);
    }

    return score;
}

void performFrequencyAttack(char *ciphertext, int topN) {
    char plaintext[strlen(ciphertext) + 1];
    char key[26];
    float scores[topN];
    char possiblePlaintexts[topN][strlen(ciphertext) + 1];

    strcpy(key, "abcdefghijklmnopqrstuvwxyz");

    do {
        decrypt(ciphertext, key, plaintext);
        float score = calculateFrequencyScore(plaintext);

        for (int j = 0; j < topN; j++) {
            if (score < scores[j] || j == 0) {
                if (j < topN - 1) {
                    memmove(scores + j + 1, scores + j, (topN - j - 1) * sizeof(float));
                    memmove(possiblePlaintexts[j + 1], possiblePlaintexts[j], (topN - j - 1) * (strlen(ciphertext) + 1) * sizeof(char));
                }
                scores[j] = score;
                strcpy(possiblePlaintexts[j], plaintext);
                break;
            }
        }

    } while (next_permutation(key, key + 26));

    printf("Top %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN; i++) {
        printf("%d. %s\n", i + 1, possiblePlaintexts[i]);
    }
}

int next_permutation(char *begin, char *end) {
    char *ptr, *temp, ch;
    ptr = end - 1;
    while (ptr > begin && *ptr <= *(ptr - 1)) ptr--;
    if (ptr == begin) return 0;
    temp = ptr--;
    while (temp < end && *temp > *ptr) temp++;
    temp--;
    ch = *ptr;
    *ptr++ = *temp;
    *temp = ch;
    for (temp = end - 1; ptr < temp; ptr++, temp--) {
        ch = *ptr;
        *ptr = *temp;
        *temp = ch;
    }
    return 1;
}

int main() {
    char ciphertext[] = "Falszztysyjzyjkywjrztyjztyynaryjkyswarztyegyyj";
    int topN = 10;

    performFrequencyAttack(ciphertext, topN);

    return 0;
}

OUTPUT :

Falszztysyjzyjkywjrztyjztyynaryjkyswarztyegyyj
