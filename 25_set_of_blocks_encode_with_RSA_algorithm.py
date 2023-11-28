from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import serialization, hashes

def generate_key_pair():
    private_key = rsa.generate_private_key(
        public_exponent=65537,
        key_size=2048,
        backend=default_backend()
    )
    public_key = private_key.public_key()

    return public_key, private_key

def encrypt_decrypt_example():
    pub_key, priv_key = generate_key_pair()

    original_data = b"Hello, RSA!"

    encrypted_data = pub_key.encrypt(
        original_data,
        padding.OAEP(
            mgf=padding.MGF1(algorithm=hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None
        )
    )
    p_hex = "c3f1a1e93cf3c81f"
    p = int(p_hex, 16)

    n_hex = "c7e6636a7e22cc9a56d5a33e4a55c63d26c10a8ee1cc6d0f7b731e0fb62d6e32"
    n = int(n_hex, 16)
    q = n // p

    d = rsa.rsa_crt_dmp1(d=priv_key.dmp1, p=p, q=q)

    priv_key.d = d
    priv_key.p = p
    priv_key.q = q

    decrypted_data = priv_key.decrypt(
        encrypted_data,
        padding.OAEP(
            mgf=padding.MGF1(algorithm=hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None
        )
    )

    print("Original Data:", original_data.decode('utf-8'))
    print("Encrypted Data:", encrypted_data.hex())
    print("Decrypted Data:", decrypted_data.decode('utf-8'))

if __name__ == "__main__":
    encrypt_decrypt_example()
