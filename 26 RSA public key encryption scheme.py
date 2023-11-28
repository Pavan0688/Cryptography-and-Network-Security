from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives import serialization

def generate_key_pair():
    private_key = rsa.generate_private_key(
        public_exponent=65537,
        key_size=2048,
        backend=default_backend()
    )
    public_key = private_key.public_key()

    return public_key, private_key

def simulate_key_leak(old_private_key):
    # Simulate Bob generating a new public and private key pair
    return generate_key_pair()

def main():
    # Generate the initial public and private key pair
    original_public_key, original_private_key = generate_key_pair()

    # Simulate Bob leaking his private key
    leaked_private_key = original_private_key

    # Bob generates a new public and private key pair
    new_public_key, new_private_key = simulate_key_leak(leaked_private_key)

    print("Original Public Key:", original_public_key)
    print("Original Private Key:", original_private_key)

    print("\nLeaked Private Key:", leaked_private_key)

    print("\nNew Public Key:", new_public_key)
    print("New Private Key:", new_private_key)

if __name__ == "__main__":
    main()
