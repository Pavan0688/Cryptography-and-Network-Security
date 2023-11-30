from Crypto.Cipher import DES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad

def des_encrypt(plain_text, key):
    cipher = DES.new(key, DES.MODE_ECB)  
    padded_plain_text = pad(plain_text.encode(), DES.block_size)

    cipher_text = cipher.encrypt(padded_plain_text)
    return cipher_text

if __name__ == "__main__":
    plaintext = "Hello, World!"  
    key = get_random_bytes(8)  

    cipher_text = des_encrypt(plaintext, key)
    print("Cipher Text:", cipher_text.hex())
