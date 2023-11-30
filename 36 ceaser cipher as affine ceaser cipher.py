
def encrypt_affine_caesar(plaintext, a, b):
    ciphertext = ""
    for char in plaintext.upper():
        if char.isalpha():
            value = (a * (ord(char) - ord('A')) + b) % 26
            ciphertext += chr(value + ord('A'))
        else:
            ciphertext += char
    return ciphertext

def decrypt_affine_caesar(ciphertext, a, b):
    a_inverse = 0
    for i in range(26):
        if (a * i) % 26 == 1:
            a_inverse = i
            break

    plaintext = ""
    for char in ciphertext.upper():
        if char.isalpha():
            value = (a_inverse * (ord(char) - ord('A') - b)) % 26
            plaintext += chr(value + ord('A'))
        else:
            plaintext += char
    return plaintext


if __name__ == "__main__":
  
    plaintext = "HELLO"
    a = 3
    b = 5
    encrypted_text = encrypt_affine_caesar(plaintext, a, b)
    print(f"Encrypted Text: {encrypted_text}")

    decrypted_text = decrypt_affine_caesar(encrypted_text, a, b)
    print(f"Decrypted Text: {decrypted_text}")
