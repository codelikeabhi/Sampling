#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>   
using namespace std;

// Function to generate the circulant matrix
vector<vector<int>> CyclicMatrix(const vector<int>& vec) {
    int n = vec.size();
    vector<vector<int>> matrix(n, vector<int>(n)); //empty matrix of n*n
    
    for (int i = 0; i < n; ++i) {
        matrix[i][0] = vec[i]; // Initialize the first column with the input vector
    }

    for (int j = 1; j < n; ++j) {
        
        matrix[0][j] = -matrix[n-1][j-1];  // Negate last element and put at front
        
        for (int i = 1; i < n; ++i) {
            matrix[i][j] = matrix[i-1][j-1];  // put rest element as it is
        }
    }

    return matrix;
}

// Function to sample a submatrix from the circulant matrix based on a seed
vector<vector<int>> sampleSubmatrix(const vector<vector<int>>& matrix, int seed, int numRows, int numCols) {
    int n = matrix.size();
    vector<vector<int>> submatrix(numRows, vector<int>(numCols));

    // Use seed to determine the starting row and column
    srand(seed);
    int startRow = rand() % (n - numRows + 1); // Random start row
    int startCol = rand() % (n - numCols + 1); // Random start column

    // Extract the submatrix
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            submatrix[i][j] = matrix[startRow + i][startCol + j];
        }
    }

    return submatrix;
}

// Function to print a matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<int> vec = {2, 8, 11, 15, 24, 9, 1, 0, 7, 10, 56, 28, 99, 19, 12, 14, 16};

    vector<vector<int>> circulantMatrix = CyclicMatrix(vec);

    int seed = static_cast<int>(time(0)); // Use current time as a seed

    // Define the submatrix size
    int numRows = 2;  // Number of rows in the submatrix
    int numCols = 3;  // Number of columns in the submatrix

    vector<vector<int>> submatrix = sampleSubmatrix(circulantMatrix, seed, numRows, numCols);

    cout << "Circulant Matrix: " << endl;
    printMatrix(circulantMatrix);

    cout << "\nSampled Submatrix (Seed " << seed << "): " << endl;
    printMatrix(submatrix);

    return 0;
}
