#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long long mod_exp(unsigned long long a, unsigned long long b, unsigned long long q) {
    unsigned long long result = 1;

    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % q;
        }
        a = (a * a) % q;
        b /= 2;
    }

    return result;
}

unsigned long long diffie_hellman(unsigned long long base, unsigned long long prime, unsigned long long secret) {
    return mod_exp(base, secret, prime);
}

int main() {
    
    unsigned long long prime = 23; 
    unsigned long long base = 5;   

    unsigned long long alice_secret = 6;

    unsigned long long bob_secret = 15;

    unsigned long long alice_public = diffie_hellman(base, prime, alice_secret);
    unsigned long long bob_public = diffie_hellman(base, prime, bob_secret);

    unsigned long long alice_shared_secret = diffie_hellman(bob_public, prime, alice_secret);
    unsigned long long bob_shared_secret = diffie_hellman(alice_public, prime, bob_secret);

    printf("Alice's Shared Secret: %llu\n", alice_shared_secret);
    printf("Bob's Shared Secret: %llu\n", bob_shared_secret);

    return 0;
}

