#include <stdio.h>

int modInverse(int a, int m);
void affineDecrypt(char ciphertext[], int a, int b, char plaintext[]);
int findFrequency(char ciphertext[], char letter);

int main() {
    char ciphertext[100], plaintext[100];
    int a, b;
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 

    int y1 = 1; 
    int y2 = 20;
    int x1 = 4; 
    int x2 = 19; 

    int a_inverse, temp;
    
    temp = (x1 - x2 + 26) % 26;
    a = ((y1 - y2 + 26) % 26 * modInverse(temp, 26)) % 26;
    
    if (a == -1) {
        printf("No valid solution for a.\n");
        return 1;
    }

    b = (y1 - a * x1 + 26) % 26;

    affineDecrypt(ciphertext, a, b, plaintext);

    printf("Plaintext: %s\n", plaintext);

    return 0;
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 0) {
            return x;
        }
    }
    return -1;
}

void affineDecrypt(char ciphertext[], int a, int b, char plaintext[]) {
    int a_inverse = modInverse(a, 26);
    int i;
    
    if (a_inverse == -1) {
        printf("No modular inverse for a.\n");
        return;
    }

    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            int y = toupper(ciphertext[i]) - 'A';
            int x = (a_inverse * (y - b + 26)) % 26;
            plaintext[i] = x + 'A';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0'; 
}

OUTPUT :

Enter the ciphertext: BUNBKDULBN
Plaintext: EXAMPLETXT

