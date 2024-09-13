#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime> 
#include "Rq.cpp"
using namespace std;

class CRYSTALS_KYBER{
private: 
    int n;
    int k;
    int Q;
    
protected:
    // Creates a 2D array
    Rq** GEN_2D_ARR(int rows, int cols, int n,int q){
        Rq **array = (Rq **)malloc(rows * sizeof(Rq *));
        for (int i = 0; i < rows; i++) {
            array[i] = (Rq *)malloc(cols * sizeof(Rq));
        }
        
        vector<int> zeros(n,0);
    
        for (int i=0; i<rows;i++){
            for (int j=0;j<cols;j++){
                array[i][j] = Rq(zeros,q);
            }        
        }
    
        return array;
    }
    
    Rq** T(Rq** A){ // Transpose of A 
    
        Rq **array = (Rq **)malloc(k * sizeof(Rq *));
            for (int i = 0; i < k; i++) {
                array[i] = (Rq *)malloc(k * sizeof(Rq));
            }
            
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                array[i][j] = A[j][i];
            }
        }
        
        return array;
    }
    
    Rq* GEN_RANDOM_MATRICES(int N, int K,int q){
        vector<int> array(N,0);
        Rq* arr = (Rq*)malloc(k*sizeof(Rq));
        int temp = 0;
        for (int i=0;i<K;i++){
            for(int j=0;j<N;j++){
                do{
                  temp = rand();  // Here we will use gaussian sampler hardware
                } while(temp % Q == 0); 
                array[j] = temp;
            }
            arr[i] = Rq(array,q);
        }
        
        return arr;
    }
    
public:
    
    CRYSTALS_KYBER(int N, int K, int q){
        n = N;
        k = K;
        Q = q;
    }
    
    Rq** GEN_A_matrix(){ // Generates A matrix
        Rq** A = GEN_2D_ARR(k,k,n,Q);
        vector<int> coeffs(n,0);
        int temp=0;
        
        for (int i=0;i<k;i++){
            for (int j=0;j<k;j++){
                for (int k=0;k<n;k++){
                    temp = rand(); // use GaussSampler
                    coeffs[k] = temp;
                }
                
                A[i][j] = Rq(coeffs,Q);
            }
        }
        
        return A;
    }
    
    

    ///Sampling Sub matrix
    Rq* sampleSubmatrix(Rq** A, int seed = 1726141696, int numRows = 2, int numCols = 3) {
        int n = sizeof(A);
        Rq* submatrix = GEN_RANDOM_MATRICES(numRows, numCols, 4);
    
        // Use seed to determine the starting row and column
        srand(seed);
        int startRow = rand() % (n - numRows + 1); // Random start row
        int startCol = rand() % (n - numCols + 1); // Random start column
    
        // Extract the submatrix
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                submatrix[i][j] = A[startRow + i][startCol + j];
            }
        }
    
        return submatrix;
    }

    
    
    
    Rq* GEN_SECRET(){ // Generates Secret Key
        Rq* S = GEN_RANDOM_MATRICES(n,k,Q);
        return S;
    }
    
    Rq* GEN_PK(Rq** A, Rq* S){ // Generates T matrix
        // T = A*S+E;
        Rq* E = GEN_RANDOM_MATRICES(n,k,4);  
        Rq* temp = (Rq*)malloc(k*sizeof(Rq));
        vector<int> coeffs(n,0);
        Rq obj= Rq(coeffs,Q);
        Rq mult = Rq(coeffs,Q);

        for(int i=0;i<k;i++){
            temp[i] = obj;
            for(int j=0;j<k;j++){
                mult = A[i][j]*S[j];
                temp[i] = temp[i] + mult; // Here we will use the NTT hardware accelerator 
            }
            // Insert inverse NTT code here 
            temp[i] = temp[i] + E[i];
        }
        
        return temp;
        
        
    }
    
    void Print(Rq** A){
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                A[i][j].Print();
                cout<<" ";
            }
            cout<<endl;
        }
    }
    
};