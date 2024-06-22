#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MOD 26

int charToInt(char ch) {
    return toupper(ch) - 'A';
}

char intToChar(int num) {
    return num + 'A';
}

int determinant(int key[2][2]) {
    return key[0][0] * key[1][1] - key[0][1] * key[1][0];
}

int modularInverse(int a, int m) {
    a = (a % m + m) % m; 
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}

void cofactor(int key[2][2], int cofactor[2][2]) {
    cofactor[0][0] = key[1][1];
    cofactor[0][1] = -key[0][1];
    cofactor[1][0] = -key[1][0];
    cofactor[1][1] = key[0][0];
}

void adjugate(int key[2][2], int adj[2][2]) {
    adj[0][0] = key[1][1];
    adj[0][1] = -key[1][0];
    adj[1][0] = -key[0][1];
    adj[1][1] = key[0][0];
}

void inverseMatrix(int key[2][2], int inv_key[2][2]) {
    int det = determinant(key);
    int det_inv = modularInverse(det, MOD);

    if (det_inv == -1) {
        printf("Matrix inversion failed: determinant is zero or has no modular inverse.\n");
        exit(1);
    }

    int adj[2][2];
    adjugate(key, adj);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            inv_key[i][j] = (adj[i][j] * det_inv) % MOD;
            if (inv_key[i][j] < 0) {
                inv_key[i][j] += MOD;
            }
        }
    }
}

void encryptHill(char plaintext[], int key[2][2], char ciphertext[]) {
    int len = strlen(plaintext);
    int encrypted[len];

    for (int i = 0; i < len; i += 2) {
        int p1 = charToInt(plaintext[i]);
        int p2 = (i + 1 < len) ? charToInt(plaintext[i + 1]) : 0; 

        int c1 = (key[0][0] * p1 + key[0][1] * p2) % MOD;
        int c2 = (key[1][0] * p1 + key[1][1] * p2) % MOD;

        encrypted[i] = c1;
        encrypted[i + 1] = c2;
    }

    for (int i = 0; i < len; i++) {
        ciphertext[i] = intToChar(encrypted[i]);
    }
    ciphertext[len] = '\0';
}

void decryptHill(char ciphertext[], int key[2][2], char decrypted[]) {
    int len = strlen(ciphertext);
    int decrypted_num[len];

    int inv_key[2][2];
    inverseMatrix(key, inv_key);

    for (int i = 0; i < len; i += 2) {
        int c1 = charToInt(ciphertext[i]);
        int c2 = charToInt(ciphertext[i + 1]);

        int p1 = (inv_key[0][0] * c1 + inv_key[0][1] * c2) % MOD;
        int p2 = (inv_key[1][0] * c1 + inv_key[1][1] * c2) % MOD;

        decrypted_num[i] = p1;
        decrypted_num[i + 1] = p2;
    }

    for (int i = 0; i < len; i++) {
        decrypted[i] = intToChar(decrypted_num[i]);
    }
    decrypted[len] = '\0';
    
}

int main() {
    char plaintext[] = "meetmeattheusualplaceattenratherthaneightoclock";
    char ciphertext[1000];
    char decrypted[1000];

    int key[2][2] = {
        {9, 4},
        {5, 7}
    };

    encryptHill(plaintext, key, ciphertext);

    decryptHill(ciphertext, key, decrypted);

    printf("Plaintext: %s\n", plaintext);
    printf("Key Matrix:\n");
    printf("  %d %d\n", key[0][0], key[0][1]);
    printf("  %d %d\n", key[1][0], key[1][1]);
    printf("Encrypted Message: %s\n", ciphertext);
    printf("Decrypted Message: %s\n", decrypted);

    return 0;
}

OUTPUT :

Plaintext: meet me at the usual place at ten rather than eight oclock
Ciphertext: XAUSQPLXWWCVOETBGSWUWXAGMZXAXUTPGAYLARXFCAPPAJALZVWM
Decrypted Message: MUCJEBEGIQIPTDFEGAIILEWILUEETIETBHZBEPBBEIOTHDYCBSSU
