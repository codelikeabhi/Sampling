#include <bits/stdc++.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
using namespace std;

float calculateEntropy(vector<int> Nums){
    int count0 = 0;
    int count1 = 0;
    
    // Count the occurrences of 0s and 1s
    for (int bit : Nums) {
        if (bit == 0) {
            count0++;
        } else if (bit == 1) {
            count1++;
        }
    }
    
    double p0 = static_cast<double>(count0) / Nums.size();
    double p1 = static_cast<double>(count1) / Nums.size();
    
    // Calculate entropy 
    double entropy = 0.0;
    if (p0 > 0) {
        entropy -= p0 * log2(p0);
    }
    if (p1 > 0) {
        entropy -= p1 * log2(p1);
    }
    
    return entropy;
}

vector<int> prngDataGenerator(int size) {
    vector<int> data;

    if (size % 2 != 0) {
        cerr << "Size must be even for balanced binary data." <<endl;
        return data;
    }

    data.resize(size / 2, 0);
    data.insert(data.end(), size / 2, 1);

    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    shuffle(data.begin(), data.end(), gen);

    return data;
}

vector<int> trngDataGenerator(int size){

    vector<int> data;

    for (int i = 0; i < size; i++) {
        data.push_back(rand() % 2);
    }

    return data;
}

// Function to convert vector of bits to vector of bytes
vector<unsigned char> bitsToBytes(const vector<int>& bits) {
    vector<unsigned char> bytes(bits.size() / 8, 0);
    for (size_t i = 0; i < bits.size(); ++i) {
        bytes[i / 8] |= bits[i] << (7 - (i % 8));
    }
    return bytes;
}

// Function to convert bytes back to bits
vector<int> bytesToBits(const vector<unsigned char>& bytes) {
    vector<int> bits(bytes.size() * 8, 0);
    for (size_t i = 0; i < bytes.size(); ++i) {
        for (int bit = 0; bit < 8; ++bit) {
            bits[i * 8 + bit] = (bytes[i] >> (7 - bit)) & 1;
        }
    }
    return bits;
}

// AES-256 encryption function
vector<int> aes256_encrypt(const vector<int>& messageBits, const vector<int>& keyBits) {
    // Convert bits to bytes
    vector<unsigned char> keyBytes = bitsToBytes(keyBits);
    vector<unsigned char> messageBytes = bitsToBytes(messageBits);

    // AES-256 requires a 256-bit key (32 bytes) and a 128-bit IV (16 bytes)
    unsigned char iv[16];
    RAND_bytes(iv, sizeof(iv)); // Generate a random IV

    // Prepare for encryption
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, keyBytes.data(), iv);

    // Buffer for encrypted message (AES block size is 16 bytes)
    vector<unsigned char> ciphertext(messageBytes.size() + 16);  // Change AES_BLOCK_SIZE to 16
    int len;
    int ciphertext_len;

    // Perform encryption
    EVP_EncryptUpdate(ctx, ciphertext.data(), &len, messageBytes.data(), messageBytes.size());
    ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len);
    ciphertext_len += len;

    // Cleanup
    EVP_CIPHER_CTX_free(ctx);

    // Resize to actual ciphertext length
    ciphertext.resize(ciphertext_len);

    // Convert ciphertext bytes to bits
    return bytesToBits(ciphertext);
}

int main() {
    int size = 256; // 256 bits for both the key and the message
    vector<int> Key = prngDataGenerator(size);
    vector<int> Message = trngDataGenerator(size);

    // Encrypt the message using AES-256
    vector<int> encryptedMessageBits = aes256_encrypt(Message, Key);

    // Print the encrypted message in bits
    cout << "Encrypted message (in bits):" << endl;
    for (int bit : encryptedMessageBits) {
        cout << bit;
    }
    cout << endl;

    cout<<"Size of encrypted message: " << encryptedMessageBits.size() << endl;

    cout<<"Entropy of TRNG Data: "<< calculateEntropy(Message)<<endl;
    cout<<"Entropy of PRNG Data: "<< calculateEntropy(Key)<<endl;
    cout<<"Entropy of Encrypted Data: "<< calculateEntropy(encryptedMessageBits)<<endl;


    return 0;
}
