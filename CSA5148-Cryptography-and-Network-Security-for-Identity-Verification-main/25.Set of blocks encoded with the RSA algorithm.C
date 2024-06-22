#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void gcd(mpz_t result, mpz_t a, mpz_t b) {
    mpz_t temp;
    mpz_init(temp);
    
    while (!mpz_cmp_ui(b, 0)) {
        mpz_set(temp, b);
        mpz_mod(b, a, b);
        mpz_set(a, temp);
    }
    
    mpz_set(result, a);
    
    mpz_clear(temp);
}

void extendedEuclid(mpz_t gcd, mpz_t x, mpz_t y, mpz_t a, mpz_t b) {
    mpz_t old_r, r, old_s, s, old_t, t, quotient, temp;
    mpz_inits(old_r, r, old_s, s, old_t, t, quotient, temp, NULL);
    
    mpz_set(old_r, a);
    mpz_set(r, b);
    mpz_set_ui(old_s, 1);
    mpz_set_ui(s, 0);
    mpz_set_ui(old_t, 0);
    mpz_set_ui(t, 1);
    
    while (mpz_cmp_ui(r, 0) > 0) {
        mpz_fdiv_q(quotient, old_r, r);
        
        mpz_set(temp, r);
        mpz_set(r, old_r);
        mpz_submul(old_r, quotient, r);
        
        mpz_set(temp, s);
        mpz_set(s, old_s);
        mpz_submul(old_s, quotient, s);
        
        mpz_set(temp, t);
        mpz_set(t, old_t);
        mpz_submul(old_t, quotient, t);
    }
    
    mpz_set(gcd, old_r);
    mpz_set(x, old_s);
    mpz_set(y, old_t);
    
    mpz_clears(old_r, r, old_s, s, old_t, t, quotient, temp, NULL);
}

int main() {
    mpz_t n, e, m, d, p, q, gcd_result, phi_n, x, y;
    mpz_inits(n, e, m, d, p, q, gcd_result, phi_n, x, y, NULL);
    
    mpz_set_str(n, "3599", 10);   
    mpz_set_str(e, "31", 10);    
    mpz_set_str(m, "1234", 10);  
   
    gcd(gcd_result, m, n);
    
 
    if (mpz_cmp_ui(gcd_result, 1) > 0 && mpz_cmp(gcd_result, n) < 0) {
    
        mpz_set(p, gcd_result);
        mpz_div(q, n, p); 
        
        mpz_sub_ui(p, p, 1);   
        mpz_sub_ui(q, q, 1);  
        mpz_mul(phi_n, p, q);
        
        extendedEuclid(gcd_result, d, x, e, phi_n);
        
        if (mpz_sgn(d) < 0) {
            mpz_add(d, d, phi_n);
        }
        gmp_printf("Private key (d) = %Zd\n", d);
    } else {
        printf("Unable to find a common factor with n.\n");
    }
    
  mpz_clears(n, e, m, d, p, q, gcd_result, phi_n, x, y, NULL);
    
    return 0;
}

output :

Private key (d) = 2363
