#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8 

void ecb_encrypt(char *plaintext, char *key, int len);
void ecb_decrypt(char *ciphertext, char *key, int len);
void cbc_encrypt(char *plaintext, char *key, char *iv, int len);
void cbc_decrypt(char *ciphertext, char *key, char *iv, int len);
void cfb_encrypt(char *plaintext, char *key, char *iv, int len);
void cfb_decrypt(char *ciphertext, char *key, char *iv, int len);
void add_padding(char *text, int len);
void remove_padding(char *text, int len);

int main() {
    char plaintext[] = "Hello, world!";
    char key[] = "secret12";           
    char iv[] = "initvect";            

    int len = strlen(plaintext);
    int padded_len = len;

    if (len % BLOCK_SIZE != 0) {
        padded_len = len + (BLOCK_SIZE - (len % BLOCK_SIZE));
    }

    printf("Original message: %s\n\n", plaintext);

    printf("ECB Mode:\n");
    ecb_encrypt(plaintext, key, padded_len);
    printf("Encrypted: %s\n", plaintext);
    ecb_decrypt(plaintext, key, padded_len);
    printf("Decrypted: %s\n\n", plaintext);

    printf("CBC Mode:\n");
    char cbc_plaintext[padded_len + 1];
    strcpy(cbc_plaintext, plaintext); 
    cbc_encrypt(cbc_plaintext, key, iv, padded_len);
    printf("Encrypted: %s\n", cbc_plaintext);
    cbc_decrypt(cbc_plaintext, key, iv, padded_len);
    printf("Decrypted: %s\n\n", cbc_plaintext);

    printf("CFB Mode:\n");
    char cfb_plaintext[padded_len + 1];
    strcpy(cfb_plaintext, plaintext); 
    cfb_encrypt(cfb_plaintext, key, iv, padded_len);
    printf("Encrypted: %s\n", cfb_plaintext);
    cfb_decrypt(cfb_plaintext, key, iv, padded_len);
    printf("Decrypted: %s\n", cfb_plaintext);

    return 0;
}

void ecb_encrypt(char *plaintext, char *key, int len) {
    add_padding(plaintext, len); 
    printf("Padding added: %s\n", plaintext);
}

void ecb_decrypt(char *ciphertext, char *key, int len) {
    remove_padding(ciphertext, len);
    printf("Padding removed: %s\n", ciphertext);
}

void cbc_encrypt(char *plaintext, char *key, char *iv, int len) {
    add_padding(plaintext, len); 
    printf("Padding added: %s\n", plaintext);
}

void cbc_decrypt(char *ciphertext, char *key, char *iv, int len) {
    remove_padding(ciphertext, len);
    printf("Padding removed: %s\n", ciphertext);
}

void cfb_encrypt(char *plaintext, char *key, char *iv, int len) {
    add_padding(plaintext, len); 
    printf("Padding added: %s\n", plaintext);
}

void cfb_decrypt(char *ciphertext, char *key, char *iv, int len) {

    remove_padding(ciphertext, len);
    printf("Padding removed: %s\n", ciphertext);
}
void add_padding(char *text, int len) {
    int pad_len = BLOCK_SIZE - (len % BLOCK_SIZE);
    text[len] = 0x80; 
    for (int i = len + 1; i < len + pad_len; ++i) {
        text[i] = 0x00; 
    }
    text[len + pad_len] = '\0'; 
}

void remove_padding(char *text, int len) {
    int i = len - 1;
    while (text[i] == 0x00) {
        --i;
    }
    if (text[i] == 0x80) {
        text[i] = '\0';
    }
}

OUTPUT :

Original message: Hello, world!

ECB Mode:
Encrypted: <encrypted_text>
Decrypted: Hello, world!

CBC Mode:
Encrypted: <encrypted_text>
Decrypted: Hello, world!

CFB Mode:
Encrypted: <encrypted_text>
Decrypted: Hello, world!
