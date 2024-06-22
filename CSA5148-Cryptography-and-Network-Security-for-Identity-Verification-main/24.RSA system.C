#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int extendedEuclid(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    
    int x1, y1;
    int gcd_val = extendedEuclid(b, a % b, &x1, &y1);
    
    *x = y1;
    *y = x1 - (a / b) * y1;
    
    return gcd_val;
}

int modInverse(int a, int m) {
    int x, y;
    int gcd_val = extendedEuclid(a, m, &x, &y);
    
    if (gcd_val != 1) {
      
        return -1;
    } else {
       
        x = (x % m + m) % m;
        return x;
    }
}

int main() {
    int e = 31;
    int n = 3599;
    int p, q;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            p = i;
            q = n / i;
            break;
        }
    }
    
    int phi_n = (p - 1) * (q - 1);
    
    int d = modInverse(e, phi_n);
  
    printf("Private key (d) = %d\n", d);
    
    return 0;
}

OUTPUT :

Private key (d) = 3071
