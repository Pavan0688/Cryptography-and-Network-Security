from collections import Counter
import string


def decrypt(text, key):
    decrypted_text = ''
    for char in text:
        if char.isalpha():
            shifted = ord(char) - key
            if char.islower():
                if shifted < ord('a'):
                    shifted += 26
            elif char.isupper():
                if shifted < ord('A'):
                    shifted += 26
            decrypted_text += chr(shifted)
        else:
            decrypted_text += char
    return decrypted_text
def frequency_attack(ciphertext, top_n=10):
   
    letter_count = Counter(ciphertext.lower())
    total_letters = sum(letter_count.values())

    english_freq = {
        'e': 12.02, 't': 9.10, 'a': 8.12, 'o': 7.68, 'i': 7.31, 'n': 6.95, 's': 6.28, 'r': 6.02,
        'h': 5.92, 'd': 4.32, 'l': 3.98, 'u': 2.88, 'c': 2.71, 'm': 2.61, 'f': 2.30, 'y': 2.11,
        'w': 2.09, 'g': 2.03, 'p': 1.82, 'b': 1.49, 'v': 1.11, 'k': 0.69, 'x': 0.17, 'q': 0.11,
        'j': 0.10, 'z': 0.07
    }

    deviations = {}
    for letter, freq in english_freq.items():
        observed_freq = (letter_count[letter] / total_letters) * 100
        deviations[letter] = abs(freq - observed_freq)

    possible_keys = sorted(deviations, key=deviations.get)[:top_n]

    possible_plaintexts = []
    for key in possible_keys:
        decrypted = decrypt(ciphertext, ord(key) - ord('a'))
        possible_plaintexts.append(decrypted)

    return possible_plaintexts

if __name__ == "__main__":
  
    ciphertext = "Vjku c vq ujg, cpf vq dg eqorwvgt, cpf vjku c arrgekpi qh vjg fcpvjgt. C vq ujg, cpf vjg qh vjku vq dg qh vjg fcpvjgt."

    top_plaintexts = frequency_attack(ciphertext, top_n=10)
    for i, plaintext in enumerate(top_plaintexts, 1):
        print(f"Plaintext {i}: {plaintext}")
