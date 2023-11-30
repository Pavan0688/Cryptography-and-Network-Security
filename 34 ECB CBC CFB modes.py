BLOCK_SIZE = 8  
def add_padding(plaintext):
    padding_bits = BLOCK_SIZE - (len(plaintext) % BLOCK_SIZE)
    
    if padding_bits != BLOCK_SIZE:
        padding = '1' + '0' * (padding_bits - 1)  
        plaintext += padding
    
    return plaintext

if __name__ == "__main__":
    plaintext = "Hello, World!"  
    padded_plaintext = add_padding(plaintext)

    print("Padded plaintext:", padded_plaintext)
