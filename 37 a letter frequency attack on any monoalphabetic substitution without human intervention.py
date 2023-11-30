from collections import Counter
import operator

def count_letter_frequencies(text):
    letter_count = Counter(c for c in text if c.isalpha())
    total_letters = sum(letter_count.values())
    frequencies = {letter: count / total_letters for letter, count in letter_count.items()}
    return frequencies

def frequency_attack(ciphertext, top_n=10):
    english_letter_frequencies = {
        'E': 0.12702, 'T': 0.09056, 'A': 0.08167, 'O': 0.07507, 'I': 0.06966,
        'N': 0.06749, 'S': 0.06327, 'H': 0.06094, 'R': 0.05987, 'D': 0.04253,
        'L': 0.04025, 'C': 0.02782, 'U': 0.02758, 'M': 0.02406, 'W': 0.02360,
        'F': 0.02228, 'G': 0.02015, 'Y': 0.01974, 'P': 0.01929, 'B': 0.01492,
        'V': 0.00978, 'K': 0.00772, 'J': 0.00153, 'X': 0.00150, 'Q': 0.00095,
        'Z': 0.00074
    }

    ciphertext_frequencies = count_letter_frequencies(ciphertext)

    for key in list(ciphertext_frequencies.keys()):
        if key not in english_letter_frequencies:
            del ciphertext_frequencies[key]

    mapping = {}
    for cipher_letter, _ in sorted(ciphertext_frequencies.items(), key=lambda x: x[1], reverse=True):
        if len(mapping) == 26:
            break

        best_match = max(
            english_letter_frequencies.keys(),
            key=lambda x: english_letter_frequencies[x] * ciphertext_frequencies.get(x, 0)
        )

        mapping[cipher_letter] = best_match
        del english_letter_frequencies[best_match]

    plaintexts = []
    for i in range(top_n):
        plaintext = ''.join(mapping.get(letter, letter) for letter in ciphertext)
        plaintexts.append(plaintext)
        mapping = {key: value for key, value in zip(mapping.values(), mapping.keys())}

    return pl
if __name__ == "__main__":
   
    ciphertext = "GWC uivioml bw nqvl bpm zqopb apqnb."

    possible_plaintexts = frequency_attack(ciphertext, top_n=10)

    print("Top 10 Possible Plaintexts:")
    for i, plaintext in enumerate(possible_plaintexts, 1):
        print(f"{i}. {plaintext}")
