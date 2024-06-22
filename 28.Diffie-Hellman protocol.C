#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long int mod_exp(long long int base, long long int exp, long long int mod) {
    long long int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

int main() {
  
    long long int prime_q = 23;   
    long long int base_g = 5;

    long long int private_A = 6; 

    long long int private_B = 15; 

    long long int public_A = mod_exp(base_g, private_A, prime_q); 
    long long int public_B = mod_exp(base_g, private_B, prime_q); 

    printf("Alice sends public value A to Bob: %lld\n", public_A);
    printf("Bob sends public value B to Alice: %lld\n", public_B);

    long long int secret_A = mod_exp(public_B, private_A, prime_q);
    long long int secret_B = mod_exp(public_A, private_B, prime_q); 

    printf("\nShared secret computed by Alice: %lld\n", secret_A);
    printf("Shared secret computed by Bob: %lld\n", secret_B);

    return 0;
}

OUTPUT :

Alice sends public value A to Bob: 8
Bob sends public value B to Alice: 19

Shared secret computed by Alice: 2
Shared secret computed by Bob: 2
