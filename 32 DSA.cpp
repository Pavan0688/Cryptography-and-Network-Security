#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/dsa.h>
#include <openssl/rand.h>

void generate_dsa_key(DSA **dsa) {
    *dsa = DSA_generate_parameters(1024, NULL, 0, NULL, NULL, NULL, NULL);
    DSA_generate_key(*dsa);
}

void sign_message(const char *message, DSA *dsa, unsigned char *signature) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1((unsigned char *)message, strlen(message), hash);
    
    DSA_sign(0, hash, SHA_DIGEST_LENGTH, signature, NULL, dsa);
}

int verify_signature(const char *message, DSA *dsa, const unsigned char *signature) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1((unsigned char *)message, strlen(message), hash);

    return DSA_verify(0, hash, SHA_DIGEST_LENGTH, signature, DSA_size(dsa), dsa);
}

int main() {
    DSA *dsa;
    generate_dsa_key(&dsa);

    const char *message = "Hello, DSA!";
    
    unsigned char signature1[DSA_size(dsa)];
    sign_message(message, dsa, signature1);
    
    unsigned char signature2[DSA_size(dsa)];
    sign_message(message, dsa, signature2);

    int result1 = verify_signature(message, dsa, signature1);
    int result2 = verify_signature(message, dsa, signature2);

    printf("Signature 1 verification result: %s\n", (result1 == 1) ? "Success" : "Failure");
    printf("Signature 2 verification result: %s\n", (result2 == 1) ? "Success" : "Failure");

    DSA_free(dsa);

    return 0;
}

