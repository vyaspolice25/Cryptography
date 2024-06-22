#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

float englishFreq[26] = {8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0, 0.2, 0.8, 4.0, 2.4,
                         6.7, 7.5, 1.9, 0.1, 6.0, 6.3, 9.1, 2.8, 1.0, 2.4, 0.2, 2.0, 0.1};

void decrypt(char *ciphertext, int shift, char *plaintext) {
    int i;
    for (i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
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
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        float freq = (float)count[i] / totalLetters * 100.0;
        score += fabs(freq - englishFreq[i]);
    }

    return score;
}

void performFrequencyAttack(char *ciphertext, int topN) {
    char plaintext[strlen(ciphertext) + 1];
    float scores[topN];
    char possiblePlaintexts[topN][strlen(ciphertext) + 1];

    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        decrypt(ciphertext, shift, plaintext);
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
    }


    printf("Top %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN; i++) {
        printf("%d. %s\n", i + 1, possiblePlaintexts[i]);
    }
}

int main() {
    char ciphertext[] = "Ymjw yt ajwxjr, ny rjxxflj yt fhyji zsxj fhyji xhnsl, ymj qnyyjw ny yt wjxynslx";
    int topN = 10;

    performFrequencyAttack(ciphertext, topN);

    return 0;
}

OUTPUT :

Ymjw yt ajwxjr, ny rjxxflj yt fhyji zsxj fhyji xhnsl, ymj qnyyjw ny yt wjxynslx
