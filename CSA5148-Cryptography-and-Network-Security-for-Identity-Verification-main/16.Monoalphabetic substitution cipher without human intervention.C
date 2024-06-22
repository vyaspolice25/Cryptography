#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

float englishFrequencies[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025,
    2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
    1.974, 0.074
};

void calculateFrequencies(char *text, float frequencies[]) {
    int totalLetters = 0;
    memset(frequencies, 0, ALPHABET_SIZE * sizeof(float));

    for (char *p = text; *p; p++) {
        if (isalpha(*p)) {
            totalLetters++;
            frequencies[tolower(*p) - 'a']++;
        }
    }

    if (totalLetters > 0) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            frequencies[i] = (frequencies[i] / totalLetters) * 100.0;
        }
    }
}

void letterFrequencyAttack(char *ciphertext, int topPlaintexts) {
    float observedFrequencies[ALPHABET_SIZE];
    calculateFrequencies(ciphertext, observedFrequencies);

    float chiSquared[ALPHABET_SIZE];
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        float shiftedFrequencies[ALPHABET_SIZE] = {0};
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            int index = (i + shift) % ALPHABET_SIZE;
            shiftedFrequencies[index] = observedFrequencies[i];
        }

        float chiSq = 0.0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (englishFrequencies[i] > 0) {
                chiSq += pow(shiftedFrequencies[i] - englishFrequencies[i], 2) / englishFrequencies[i];
            }
        }
        chiSquared[shift] = chiSq;
    }

    int top = (topPlaintexts > ALPHABET_SIZE) ? ALPHABET_SIZE : topPlaintexts;
    printf("Top %d possible plaintexts:\n", top);

    for (int t = 0; t < top; t++) {
        int minIndex = 0;
        for (int i = 1; i < ALPHABET_SIZE; i++) {
            if (chiSquared[i] < chiSquared[minIndex]) {
                minIndex = i;
            }
        }

        printf("Shift %d: ", minIndex);
        for (char *p = ciphertext; *p; p++) {
            if (isalpha(*p)) {
                char base = isupper(*p) ? 'A' : 'a';
                char plain = (char)(((tolower(*p) - 'a' - minIndex + ALPHABET_SIZE) % ALPHABET_SIZE) + base);
                printf("%c", plain);
            } else {
                printf("%c", *p);
            }
        }
        printf("\n");

        chiSquared[minIndex] = FLT_MAX;
    }
}

int main() {
    char ciphertext[] = "WTAADMMHGULU";
    int topPlaintexts = 5;

    letterFrequencyAttack(ciphertext, topPlaintexts);

    return 0;
}

OUTPUT :

Top 5 possible plaintexts:
Shift 18: INTERVIEWWITC
Shift 5: QIIPBBXXODHQ
Shift 8: FNNOVVSSKQMS
Shift 2: YJJLLPPJXKLG
Shift 7: GMMNUUTTJTRN

