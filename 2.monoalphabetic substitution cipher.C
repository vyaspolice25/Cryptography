#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char text[], char ciphertextAlphabet[]);

int main() {
    char text[100];
    char ciphertextAlphabet[27];

    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);

    text[strcspn(text, "\n")] = '\0';

    printf("Enter the 26-letter ciphertext alphabet: ");
    fgets(ciphertextAlphabet, sizeof(ciphertextAlphabet), stdin);

    ciphertextAlphabet[strcspn(ciphertextAlphabet, "\n")] = '\0';

    if (strlen(ciphertextAlphabet) != 26) {
        printf("Ciphertext alphabet must be exactly 26 letters long.\n");
        return 1;
    }

    encrypt(text, ciphertextAlphabet);

    printf("Encrypted text: %s\n", text);

    return 0;
}

void encrypt(char text[], char ciphertextAlphabet[]) {
    for (int i = 0; text[i] != '\0'; i++) {
    
        if (isupper(text[i])) {
            text[i] = toupper(ciphertextAlphabet[text[i] - 'A']);
        }
    
        else if (islower(text[i])) {
            text[i] = tolower(ciphertextAlphabet[text[i] - 'a']);
        }
   
    }
}

OUTPUT :

Enter the plaintext: Hello, World!
Enter the 26-letter ciphertext alphabet: QWERTYUIOPLKJHGFDSAZXCVBNM
Encrypted text: Itssg, Vgksr!

