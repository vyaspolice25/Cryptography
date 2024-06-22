#include <stdio.h>
#include <openssl/aes.h>

void aes_cbc_encrypt(const unsigned char *plaintext, int plaintext_len,
                     const unsigned char *key, const unsigned char *iv,
                     unsigned char *ciphertext) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);
    AES_cbc_encrypt(plaintext, ciphertext, plaintext_len, &aes_key, iv, AES_ENCRYPT);
}

int main() {

    unsigned char aes_key[] = "0123456789abcdef";

    unsigned char iv[] = "abcdefghijklmnop";

    unsigned char plaintext[] = "Hello, AES CBC Encryption!";

    unsigned char ciphertext[256]; 

    aes_cbc_encrypt(plaintext, strlen(plaintext), aes_key, iv, ciphertext);

    printf("Ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

OUTPUT :

Ciphertext: 1183035a0c0d364b01835b5f4d7b0549
