import sys
import time
import threading
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QLineEdit, QTextEdit, QVBoxLayout, QWidget
from connector import Algorithm
from listener import EncryptionChecker 

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.algorithm = Algorithm('K')  
        self.tokens = []
        self.initUI()
        
        self.start_listener()

    def initUI(self):
        layout = QVBoxLayout()
        
        self.input_box = QLineEdit(self)
        self.input_box.setPlaceholderText("Enter the message to encrypt")
        layout.addWidget(self.input_box)
        
        self.send_button = QPushButton("Encrypt", self)
        self.send_button.clicked.connect(self.send_request)
        layout.addWidget(self.send_button)
        
        self.result_display = QTextEdit(self)
        self.result_display.setReadOnly(True)
        layout.addWidget(self.result_display)


        container = QWidget()
        container.setLayout(layout)
        self.setCentralWidget(container)

    def send_request(self):
        message = self.input_box.text()

        if message:
            token = self.algorithm.process_encryption(message)
            self.tokens.append(token)
            self.result_display.append(f"Token generated: {token}")
            self.input_box.clear()

    def start_listener(self):
        self.listener_thread = threading.Thread(target=self.run_listener)
        self.listener_thread.daemon = True 
        self.listener_thread.start()

    def run_listener(self):
        checker = EncryptionChecker(self.algorithm)
        
        while True:
            for token in self.tokens[:]:  
                if token in self.algorithm.encryption_store:
                    encrypted_data = self.algorithm.encryption_store[token]
                    self.result_display.append(f"Encrypted data for token {token}: {encrypted_data}")
                    self.tokens.remove(token)  
            time.sleep(1)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    main_window = MainWindow()
    main_window.show()
    sys.exit(app.exec_())
