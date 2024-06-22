#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long int mod_exp(long long int base, long long int exp, long long int modulus) {
    long long int result = 1;
    base = base % modulus;
    while (exp > 0) {
        if (exp % 2 == 1) 
            result = (result * base) % modulus;
        exp = exp >> 1;    
        base = (base * base) % modulus;  
    }
    return result;
}

long long int encrypt_character(long long int plaintext_char, long long int e, long long int n) {
    return mod_exp(plaintext_char, e, n);
}

long long int decrypt_character(long long int ciphertext_char, long long int d, long long int n) {
    return mod_exp(ciphertext_char, d, n);
}

int main() {

    long long int e = 65537; 
    long long int n = 124841;

    long long int d = 42841; 

    char plaintext[] = "HELLO";

    long long int encrypted[strlen(plaintext)];

    printf("Plaintext: %s\n", plaintext);
    printf("Encrypted (RSA without padding):\n");
    for (int i = 0; i < strlen(plaintext); i++) {
        long long int plaintext_char = plaintext[i] - 'A'; 
        encrypted[i] = encrypt_character(plaintext_char, e, n);
        printf("%lld ", encrypted[i]);
    }
    printf("\n");

    printf("Decrypted (using Bob's private key):\n");
    for (int i = 0; i < strlen(plaintext); i++) {
        long long int decrypted_char = decrypt_character(encrypted[i], d, n);
        char original_char = decrypted_char + 'A';  
        printf("%c", original_char);
    }
    printf("\n");

    return 0;
}

OUTPUT :

Plaintext: HELLO
Encrypted (RSA without padding):
24640 58234 92060 67965 68653 
Decrypted (using Bob's private key):
HELLO
