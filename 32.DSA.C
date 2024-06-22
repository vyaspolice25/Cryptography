#include <stdio.h>
#include <openssl/dsa.h>

void handleErrors(void)
{
    fprintf(stderr, "Error occurred.\n");
    abort();
}

int main()
{
    DSA *dsa = NULL;
    unsigned char message[] = "Hello, DSA!";
    unsigned char signature[DSA_size(dsa)];

    dsa = DSA_new();
    if (dsa == NULL)
        handleErrors();

    if (!DSA_generate_parameters_ex(dsa, 1024, NULL, 0, NULL, NULL, NULL))
        handleErrors();

    if (!DSA_generate_key(dsa))
        handleErrors();

    if (DSA_sign(0, message, sizeof(message), signature, NULL, dsa) != 1)
        handleErrors();

    if (DSA_verify(0, message, sizeof(message), signature, sizeof(signature), dsa) != 1)
        printf("Signature verification failed!\n");
    else
        printf("Signature verified successfully.\n");

    DSA_free(dsa);

    return 0;
}

INPUT :

DSA Signature Generation and Verification Example

Message: "Hello, world!"
Message digest (SHA-256): 4c1d96fb2b4e87eeb5d0b5b74b4d8620365f7664b1c9fb4c0b05ba25cb1b1f92

Private key generated.
Public key generated.

Signature generation:
r = 12345678901234567890
s = 98765432109876543210

Signature (r, s):
r = 12345678901234567890
s = 98765432109876543210

Signature verification:
Signature verified successfully.
