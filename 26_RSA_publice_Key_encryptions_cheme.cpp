#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

void generate_key_pair(RSA **pub_key, RSA **priv_key) {
    *pub_key = RSA_generate_key(2048, RSA_F4, NULL, NULL);
    *priv_key = RSAPrivateKey_dup(*pub_key);
}

void encrypt_decrypt_example() {
    RSA *pub_key = NULL;
    RSA *priv_key = NULL;

    generate_key_pair(&pub_key, &priv_key);

    const char *original_data = "Hello, RSA!";
    int data_len = strlen(original_data);

    unsigned char encrypted_data[256];
    memset(encrypted_data, 0, sizeof(encrypted_data));

    unsigned char decrypted_data[256];
    memset(decrypted_data, 0, sizeof(decrypted_data));

    int encrypt_len = RSA_public_encrypt(data_len, (unsigned char *)original_data, encrypted_data, pub_key, RSA_PKCS1_PADDING);
    if (encrypt_len == -1) {
        fprintf(stderr, "Encryption failed\n");
        exit(EXIT_FAILURE);
    }

    int decrypt_len = RSA_private_decrypt(encrypt_len, encrypted_data, decrypted_data, priv_key, RSA_PKCS1_PADDING);
    if (decrypt_len == -1) {
        fprintf(stderr, "Decryption failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Original Data: %s\n", original_data);
    printf("Encrypted Data: ");
    for (int i = 0; i < encrypt_len; ++i) {
        printf("%02x", encrypted_data[i]);
    }
    printf("\n");
    printf("Decrypted Data: %s\n", decrypted_data);

    RSA_free(pub_key);
    RSA_free(priv_key);
}

int main() {
    encrypt_decrypt_example();

    return 0;
}

