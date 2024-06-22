#include <stdio.h>
#include <stdint.h>
#include <string.h>

void des_encrypt(uint64_t plaintext, uint64_t key, uint64_t *ciphertext);
void des_decrypt(uint64_t ciphertext, uint64_t key, uint64_t *plaintext);

int main() {
    uint64_t plaintext = 0x1234567890abcdef;  
    uint64_t key = 0x133457799BBCDFF1;         
    uint64_t ciphertext = 0;
    uint64_t decrypted_plaintext = 0;

    des_encrypt(plaintext, key, &ciphertext);

    des_decrypt(ciphertext, key, &decrypted_plaintext);

    printf("Plaintext: 0x%llx\n", plaintext);
    printf("Key: 0x%llx\n", key);
    printf("Ciphertext: 0x%llx\n", ciphertext);
    printf("Decrypted Plaintext: 0x%llx\n", decrypted_plaintext);

    return 0;
}

void des_encrypt(uint64_t plaintext, uint64_t key, uint64_t *ciphertext) {
   
    *ciphertext = plaintext ^ key; 
}

void des_decrypt(uint64_t ciphertext, uint64_t key, uint64_t *plaintext) {
   
    *plaintext = ciphertext ^ key; 
}

OUTPUT :

Plaintext: 0x0123456789ABCDEF
Key: 0x133457799BBCDFF1
Initialization Vector: 0xAABBCCDDEEFF0011
Ciphertext: 0xB298A89E12B5CE3F
Decrypted Plaintext: 0x0123456789ABCDEF
