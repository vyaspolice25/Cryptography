#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>

void aes_cbc_encrypt(const unsigned char *plaintext, int plaintext_len,
                     const unsigned char *key, const unsigned char *iv,
                     unsigned char *ciphertext) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);
    AES_cbc_encrypt(plaintext, ciphertext, plaintext_len, &aes_key, iv, AES_ENCRYPT);
}

void aes_cbc_decrypt(const unsigned char *ciphertext, int ciphertext_len,
                     const unsigned char *key, const unsigned char *iv,
                     unsigned char *plaintext) {
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);
    AES_cbc_encrypt(ciphertext, plaintext, ciphertext_len, &aes_key, iv, AES_DECRYPT);
}

int main() {
   
    unsigned char aes_key[] = "0123456789abcdef";

    unsigned char iv[] = "abcdefghijklmnop";

    unsigned char plaintext[] = "Hello, CBC Mode Encryption!";

    unsigned char ciphertext[256]; 
    aes_cbc_encrypt(plaintext, strlen(plaintext), aes_key, iv, ciphertext);

    printf("Ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    unsigned char decrypted_plaintext[256]; 

    aes_cbc_decrypt(ciphertext, strlen(plaintext), aes_key, iv, decrypted_plaintext);

    printf("Decrypted Plaintext: %s\n", decrypted_plaintext);

    return 0;
}
 OUTPUT :

 Ciphertext: a5b52b6b10fb9f9604e1a56f89a13a187e9fb8c1627d1c4276b315b0db62a5ae
