#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

void cbc_mac(const unsigned char *key, const unsigned char *message, size_t message_length, unsigned char *mac) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);

    memset(mac, 0, AES_BLOCK_SIZE);

    for (size_t i = 0; i < message_length; i += AES_BLOCK_SIZE) {
       
        for (size_t j = 0; j < AES_BLOCK_SIZE; ++j) {
            mac[j] ^= message[i + j];
        }

        AES_encrypt(mac, mac, &aes_key);
    }
}

int main() {
   
    unsigned char key[16] = "secretkey123456";

    unsigned char message[32] = "This is a two-block message.";

    unsigned char mac[AES_BLOCK_SIZE];

    cbc_mac(key, message, sizeof(message), mac);

    printf("CBC-MAC for the two-block message:\n");
    for (size_t i = 0; i < AES_BLOCK_SIZE; ++i) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    return 0;
}

