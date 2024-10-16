import time
from connector import Algorithm

class EncryptionChecker:
    def __init__(self, encryptor):
        self.encryptor = encryptor
    
    def listen_for_tokens(self, tokens: list) -> None:

        while tokens:
            for token in tokens[:]:  # Copy the token list to iterate
                if token in self.encryptor.encryption_store:
                    encrypted_data = self.encryptor.encryption_store[token]
                    print(f"Encrypted data for token {token}: {encrypted_data}")
                    tokens.remove(token)  

            time.sleep(1)


if __name__ == "__main__":
    key = 'K'
    encryptor = Algorithm(key)

    # Process multiple encryption requests
    token1 = encryptor.process_encryption("Hello, World!")
    token2 = encryptor.process_encryption("Another message")
    token3 = encryptor.process_encryption("More data to encrypt")

    # List of tokens to monitor
    tokens_to_check = [token1, token2, token3]

    # Create a new checker
    checker = EncryptionChecker(encryptor)
    
    # Start listening for the encrypted data for all tokens
    checker.listen_for_tokens(tokens_to_check)
