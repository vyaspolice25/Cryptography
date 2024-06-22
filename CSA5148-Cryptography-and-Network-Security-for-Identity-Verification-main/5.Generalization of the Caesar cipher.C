#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b);
void affineEncrypt(char plaintext[], int a, int b, char ciphertext[]);

int main() {
    char plaintext[100], ciphertext[100];
    int a, b;

    printf("Enter the value of a: ");
    scanf("%d", &a);
    printf("Enter the value of b: ");
    scanf("%d", &b);

    if (gcd(a, 26) != 1) {
        printf("Invalid value of a. It must be coprime with 26.\n");
        return 1;
    }

    printf("Enter the plaintext: ");
    getchar(); // Consume the newline character left by scanf
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    affineEncrypt(plaintext, a, b, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void affineEncrypt(char plaintext[], int a, int b, char ciphertext[]) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            int p = toupper(plaintext[i]) - 'A';
            int c = (a * p + b) % 26;
            ciphertext[i] = c + 'A';
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabet characters remain unchanged
        }
    }
    ciphertext[i] = '\0'; // Null-terminate the ciphertext string
}

OUTPUT :

Enter the value of a: 5
Enter the value of b: 8
Enter the plaintext: HELLO WORLD
Ciphertext: RCLLA BPRLD
