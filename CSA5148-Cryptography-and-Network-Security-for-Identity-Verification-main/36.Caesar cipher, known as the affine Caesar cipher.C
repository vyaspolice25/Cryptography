#include <stdio.h>
#include <ctype.h>

char encrypt(char plaintext, int a, int b) {
    if (isalpha(plaintext)) {
        int p = toupper(plaintext) - 'A';
        int C = (a * p + b) % 26; 
        return 'A' + C;
    } else {
        return plaintext;
    }
}

char decrypt(char ciphertext, int a, int b) {
    if (isalpha(ciphertext)) {
        int C = toupper(ciphertext) - 'A';
        int inv_a = -1;
        for (int i = 0; i < 26; i++) {
            if ((a * i) % 26 == 1) {
                inv_a = i;
                break;
            }
        }
        if (inv_a == -1) {
            printf("Error: No multiplicative inverse found for given 'a'\n");
            return ciphertext;
        }
        int p = (inv_a * (C - b + 26)) % 26;
        return 'A' + p; 
    } else {
        return ciphertext;
    }
}

int main() {
    char plaintext[100], ciphertext[100];
    int a, b;

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter values of 'a' and 'b': ");
    scanf("%d %d", &a, &b);

    int i = 0;
    while (plaintext[i] != '\0' && plaintext[i] != '\n') {
        ciphertext[i] = encrypt(plaintext[i], a, b);
        i++;
    }
    ciphertext[i] = '\0';

    printf("Encrypted ciphertext: %s\n", ciphertext);

    i = 0;
    while (ciphertext[i] != '\0') {
        plaintext[i] = decrypt(ciphertext[i], a, b);
        i++;
    }
    plaintext[i] = '\0';

    printf("Decrypted plaintext: %s\n", plaintext);

    return 0;
}

OUTPUT :

Enter plaintext: HELLO
Enter values of 'a' and 'b': 5 8
Encrypted ciphertext: MZGGU
Decrypted plaintext: HELLO
