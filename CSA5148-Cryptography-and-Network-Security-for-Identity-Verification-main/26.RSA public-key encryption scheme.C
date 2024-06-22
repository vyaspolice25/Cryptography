#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void generate_new_keys(mpz_t n, mpz_t e, mpz_t d, mpz_t p, mpz_t q) {
    mpz_t phi_n, lambda_n, gcd_result, temp;
    mpz_inits(phi_n, lambda_n, gcd_result, temp, NULL);
  
    mpz_mul(n, p, q);
    
    mpz_sub_ui(p, p, 1); 
    mpz_sub_ui(q, q, 1); 
    mpz_mul(phi_n, p, q); 
    
    mpz_set_ui(e, 65537);

    mpz_invert(d, e, phi_n);

    mpz_clears(phi_n, lambda_n, gcd_result, temp, NULL);
}

int main() {
    mpz_t n, e, d, p, q;
    mpz_inits(n, e, d, p, q, NULL);
 
    mpz_set_str(p, "1122221111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111", 10); 
    mpz_set_str(q, "3311111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111", 10); 

    generate_new_keys(n, e, d, p, q);

    gmp_printf("New public key (n, e): (%Zd, %Zd)\n", n, e);
    gmp_printf("New private key d: %Zd\n", d);
   
    mpz_clears(n, e, d, p, q, NULL);
    
    return 0;
}
OUTPUT :

New public key (n, e): (3699934983333333333333333333333333333333333333333333333333333333333333333333333333333333333333333, 65537)
New private key d: 1240965513000000000000000000000000000000000000000000000000000000000000000000000000000000000000001
