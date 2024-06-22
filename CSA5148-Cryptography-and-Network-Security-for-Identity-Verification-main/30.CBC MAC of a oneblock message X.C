#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <openssl/aes.h>

unsigned char key[16] = { 
    0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 
    0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c 
};
void encrypt_block(const unsigned char *plaintext, unsigned char *ciphertext, const unsigned char *iv) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);
    AES_cbc_encrypt(plaintext, ciphertext, AES_BLOCK_SIZE, &aes_key, iv, AES_ENCRYPT);
}

void compute_cbc_mac(const unsigned char *message, unsigned char *mac) {
    unsigned char iv[AES_BLOCK_SIZE] = { 0 }; 
    encrypt_block(message, mac, iv); 
}

int main() {
    unsigned char X[AES_BLOCK_SIZE] = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 
                                        0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a };
    
    unsigned char T[AES_BLOCK_SIZE]; 
    unsigned char X_concat_XxorT[2 * AES_BLOCK_SIZE]; 
    unsigned char T_prime[AES_BLOCK_SIZE];

    compute_cbc_mac(X, T);
    
    memcpy(X_concat_XxorT, X, AES_BLOCK_SIZE);
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        X_concat_XxorT[AES_BLOCK_SIZE + i] = X[i] ^ T[i];
    }

    compute_cbc_mac(X_concat_XxorT, T_prime);

    printf("MAC for X: ");
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        printf("%02x ", T[i]);
    }
    printf("\n");
    
    printf("MAC for X || (X ⊕ T): ");
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        printf("%02x ", T_prime[i]);
    }
    printf("\n");

    return 0;
}

OUTPUT : 

MAC for X: 3d a3 19 3d 3b 1a 34 69 d8 6e 1e 2b 31 9b 9f c6 
MAC for X || (X ⊕ T): 3d a3 19 3d 3b 1a 34 69 d8 6e 1e 2b 31 9b 9f c6 
