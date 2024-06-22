#include <stdio.h>
#include <ctype.h>

void encrypt(char text[], int k);

int main() {
    char text[100];
    int k;

    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter the shift value (1-25): ");
    scanf("%d", &k);

    if (k < 1 || k > 25) {
        printf("Shift value must be between 1 and 25.\n");
        return 1;
    }

    encrypt(text, k);

    printf("Encrypted text: %s\n", text);

    return 0;
}

void encrypt(char text[], int k) {
    for (int i = 0; text[i] != '\0'; i++) {

        if (isupper(text[i])) {
            text[i] = ((text[i] - 'A' + k) % 26) + 'A';
        }
       
        else if (islower(text[i])) {
            text[i] = ((text[i] - 'a' + k) % 26) + 'a';
        }
    }
}

OUTPUT :

Enter the plaintext: Hello, World!
Enter the shift value (1-25): 3
Encrypted text: Khoor, Zruog!
