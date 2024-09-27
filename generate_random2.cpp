#include <bits/stdc++.h>
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

vector<int> generateRandomBinaryData(int size) {
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


int main() {

int size = 256;
vector<int> binaryData = generateRandomBinaryData(size);

for (int bit : binaryData) {
    cout << bit << " ";
}


cout << "\nEntropy of the generated binary data: " << calculateEntropy(binaryData) << endl;

return 0;
}