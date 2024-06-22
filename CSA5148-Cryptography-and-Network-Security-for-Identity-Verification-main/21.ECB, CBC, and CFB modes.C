#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>

void aes_ecb_encrypt(const unsigned char *plaintext, int plaintext_len,
                     const unsigned char *key, unsigned char *ciphertext) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);
    int num_blocks = plaintext_len / AES_BLOCK_SIZE;
    for (int i = 0; i < num_blocks; ++i) {
        AES_encrypt(plaintext + (i * AES_BLOCK_SIZE), ciphertext + (i * AES_BLOCK_SIZE), &aes_key);
    }
}

void aes_ecb_decrypt(const unsigned char *ciphertext, int ciphertext_len,
                     const unsigned char *key, unsigned char *plaintext) {
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);
    int num_blocks = ciphertext_len / AES_BLOCK_SIZE;
    for (int i = 0; i < num_blocks; ++i) {
        AES_decrypt(ciphertext + (i * AES_BLOCK_SIZE), plaintext + (i * AES_BLOCK_SIZE), &aes_key);
    }
}

void aes_cbc_encrypt(const unsigned char *plaintext, int plaintext_len,
                     const unsigned char *key, const unsigned char *iv,
                     unsigned char *ciphertext) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);
    unsigned char temp_iv[AES_BLOCK_SIZE];
    memcpy(temp_iv, iv, AES_BLOCK_SIZE);
    int num_blocks = plaintext_len / AES_BLOCK_SIZE;
    for (int i = 0; i < num_blocks; ++i) {
        AES_cbc_encrypt(plaintext + (i * AES_BLOCK_SIZE), ciphertext + (i * AES_BLOCK_SIZE),
                        AES_BLOCK_SIZE, &aes_key, temp_iv, AES_ENCRYPT);
        memcpy(temp_iv, ciphertext + (i * AES_BLOCK_SIZE), AES_BLOCK_SIZE);
    }
}

void aes_cbc_decrypt(const unsigned char *ciphertext, int ciphertext_len,
                     const unsigned char *key, const unsigned char *iv,
                     unsigned char *plaintext) {
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);
    unsigned char temp_iv[AES_BLOCK_SIZE];
    memcpy(temp_iv, iv, AES_BLOCK_SIZE);
    int num_blocks = ciphertext_len / AES_BLOCK_SIZE;
    for (int i = 0; i < num_blocks; ++i) {
        AES_cbc_encrypt(ciphertext + (i * AES_BLOCK_SIZE), plaintext + (i * AES_BLOCK_SIZE),
                        AES_BLOCK_SIZE, &aes_key, temp_iv, AES_DECRYPT);
        memcpy(temp_iv, ciphertext + (i * AES_BLOCK_SIZE), AES_BLOCK_SIZE);
    }
}

void aes_cfb_encrypt(const unsigned char *plaintext, int plaintext_len,
                     const unsigned char *key, const unsigned char *iv,
                     unsigned char *ciphertext) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);
    unsigned char temp_iv[AES_BLOCK_SIZE];
    memcpy(temp_iv, iv, AES_BLOCK_SIZE);
    int num_blocks = plaintext_len / AES_BLOCK_SIZE;
    for (int i = 0; i < num_blocks; ++i) {
        AES_cfb128_encrypt(plaintext + (i * AES_BLOCK_SIZE), ciphertext + (i * AES_BLOCK_SIZE),
                           AES_BLOCK_SIZE, &aes_key, temp_iv, NULL, AES_ENCRYPT);
        memcpy(temp_iv, ciphertext + (i * AES_BLOCK_SIZE), AES_BLOCK_SIZE);
    }
}

void aes_cfb_decrypt(const unsigned char *ciphertext, int ciphertext_len,
                     const unsigned char *key, const unsigned char *iv,
                     unsigned char *plaintext) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);
    unsigned char temp_iv[AES_BLOCK_SIZE];
    memcpy(temp_iv, iv, AES_BLOCK_SIZE);
    int num_blocks = ciphertext_len / AES_BLOCK_SIZE;
    for (int i = 0; i < num_blocks; ++i) {
        AES_cfb128_encrypt(ciphertext + (i * AES_BLOCK_SIZE), plaintext + (i * AES_BLOCK_SIZE),
                           AES_BLOCK_SIZE, &aes_key, temp_iv, NULL, AES_DECRYPT);
        memcpy(temp_iv, ciphertext + (i * AES_BLOCK_SIZE), AES_BLOCK_SIZE);
    }
}

int main() {
    unsigned char aes_key[AES_BLOCK_SIZE] = "1234567890123456"; 
    unsigned char iv[AES_BLOCK_SIZE] = "abcdefghijklmnop";     

    unsigned char plaintext[] = "Hello, ECB/CBC/CFB Modes with Padding!";

    int plaintext_len = strlen((char *)plaintext);

    int padding_len = AES_BLOCK_SIZE - (plaintext_len % AES_BLOCK_SIZE);

    unsigned char padded_plaintext[plaintext_len + padding_len];
    memcpy(padded_plaintext, plaintext, plaintext_len);
   
    padded_plaintext[plaintext_len] = 0x80; 
    memset(padded_plaintext + plaintext_len + 1, 0, padding_len - 1); 

    unsigned char ciphertext_ecb[plaintext_len + padding_len];
    unsigned char ciphertext_cbc[plaintext_len + padding_len];
    unsigned char ciphertext_cfb[plaintext_len + padding_len];

    aes_ecb_encrypt(padded_plaintext, plaintext_len + padding_len, aes_key, ciphertext_ecb);

    aes_cbc_encrypt(padded_plaintext, plaintext_len + padding_len, aes_key, iv, ciphertext_cbc);

    aes_cfb_encrypt(padded_plaintext, plaintext_len + padding_len, aes_key, iv, ciphertext_cfb);

    printf("ECB Mode Ciphertext: ");
    for (int i = 0; i < plaintext_len + padding_len; ++i) {
        printf("%02x", ciphertext_ecb[i]);
    }
    printf("\n");

    printf("CBC Mode Ciphertext: ");
    for (int i = 0; i < plaintext_len + padding_len; ++i) {
        printf("%02x", ciphertext_cbc[i]);
    }
    printf("\n");

    printf("CFB Mode Ciphertext: ");
    for (int i = 0; i < plaintext_len + padding_len; ++i) {
        printf("%02x", ciphertext_cfb[i]);
    }
    printf("\n");

    return 0;
}
