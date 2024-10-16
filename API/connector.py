import time
import threading

class Algorithm:
    def __init__(self, key: str):
        self.key = ord(key)
        self.encryption_store = {}

    def generate_token(self) -> str:
        return str(time.time())

    def encrypt(self, message: str, token: str) -> str:
        print(f"Starting encryption for token: {token}")
        time.sleep(10)
        encrypted_message = ''.join(chr(ord(char) ^ self.key) for char in message)

        self.encryption_store[token] = encrypted_message
        print(f"Encryption complete for token: {token}")

        return encrypted_message

    def process_encryption(self, message: str) -> str:
        token = self.generate_token()
        thread = threading.Thread(target=self.encrypt, args=(message, token))
        thread.start()
        return token

    def decrypt(self, encrypted_message: str) -> str:
        decrypted_message = ''.join(chr(ord(char) ^ self.key) for char in encrypted_message)
        return decrypted_message

