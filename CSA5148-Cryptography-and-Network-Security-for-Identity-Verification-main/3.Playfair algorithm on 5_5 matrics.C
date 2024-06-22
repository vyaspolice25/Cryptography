#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void prepareKeyTable(char key[], char keyTable[SIZE][SIZE]);
void formatPlaintext(char plaintext[], char formattedText[]);
void playfairEncrypt(char plaintext[], char keyTable[SIZE][SIZE], char ciphertext[]);
void findPosition(char keyTable[SIZE][SIZE], char ch, int *row, int *col);

int main() {
    char key[30], plaintext[100], formattedText[100], ciphertext[100];
    char keyTable[SIZE][SIZE];

    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character

    prepareKeyTable(key, keyTable);

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    formatPlaintext(plaintext, formattedText);
    playfairEncrypt(formattedText, keyTable, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

void prepareKeyTable(char key[], char keyTable[SIZE][SIZE]) {
    int dict[26] = {0};
    int i, j, k, len = strlen(key);

    for (i = 0; i < len; i++) {
        key[i] = toupper(key[i]);
        if (key[i] == 'J') key[i] = 'I'; // Treat 'I' and 'J' as the same letter
    }
    i = 0; j = 0;
    for (k = 0; k < len; k++) {
        if (!dict[key[k] - 'A']) {
            keyTable[i][j] = key[k];
            dict[key[k] - 'A'] = 1;
            j++;
            if (j == SIZE) {
                j = 0;
                i++;
            }
        }
    }

    for (k = 0; k < 26; k++) {
        if (!dict[k] && (char)(k + 'A') != 'J') {
            keyTable[i][j] = (char)(k + 'A');
            j++;
            if (j == SIZE) {
                j = 0;
                i++;
            }
        }
    }
}

void formatPlaintext(char plaintext[], char formattedText[]) {
    int i, j = 0, len = strlen(plaintext);
    char prev = '\0';

    for (i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            plaintext[i] = toupper(plaintext[i]);
            if (plaintext[i] == 'J') plaintext[i] = 'I';
            if (plaintext[i] == prev) {
                formattedText[j++] = prev;
                formattedText[j++] = 'X';
            }
            formattedText[j++] = plaintext[i];
            prev = plaintext[i];
        }
    }
    if (j % 2 != 0) formattedText[j++] = 'X';
    formattedText[j] = '\0';
}

void playfairEncrypt(char plaintext[], char keyTable[SIZE][SIZE], char ciphertext[]) {
    int i, row1, col1, row2, col2;
    int len = strlen(plaintext);

    for (i = 0; i < len; i += 2) {
        findPosition(keyTable, plaintext[i], &row1, &col1);
        findPosition(keyTable, plaintext[i + 1], &row2, &col2);

        if (row1 == row2) {
            ciphertext[i] = keyTable[row1][(col1 + 1) % SIZE];
            ciphertext[i + 1] = keyTable[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            ciphertext[i] = keyTable[(row1 + 1) % SIZE][col1];
            ciphertext[i + 1] = keyTable[(row2 + 1) % SIZE][col2];
        } else {
            ciphertext[i] = keyTable[row1][col2];
            ciphertext[i + 1] = keyTable[row2][col1];
        }
    }
    ciphertext[len] = '\0';
}

void findPosition(char keyTable[SIZE][SIZE], char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (keyTable[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

OUTPUT :

Enter the keyword: playfair example
Enter the plaintext: hello world
Ciphertext: KDMNQYEMXK
