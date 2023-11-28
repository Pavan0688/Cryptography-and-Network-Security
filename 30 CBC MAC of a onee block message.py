from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding
import os

def cbc_mac(key, message):
    cipher = Cipher(algorithms.AES(key), modes.ECB(), backend=default_backend())
    encryptor = cipher.encryptor()

    padder = padding.PKCS7(algorithms.AES.block_size).padder()
    padded_message = padder.update(message) + padder.finalize()

    ciphertext = encryptor.update(padded_message) + encryptor.finalize()

    return ciphertext

def adversary_attack(key, message):
   
    two_block_message = message + (bytes(len(message)) * len(message))
    cbc_mac_two_blocks = cbc_mac(key, two_block_message)

    print("Original CBC-MAC:", cbc_mac(key, message).hex())
    print("Adversary's CBC-MAC for X || (X ⊕ T):", cbc_mac_two_blocks.hex())

def main():
    key = os.urandom(16)  
    message = b"Hello, CBC-MAC!"

    print("Original Message:", message.decode('utf-8'))
    print("Key:", key.hex())

    mac = cbc_mac(key, message)
    print("CBC-MAC for one-block message:", mac.hex())

    adversary_attack(key, message)

if __name__ == "__main__":
    main()
