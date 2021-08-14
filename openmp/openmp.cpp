#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <omp.h>
#include <io.h>
#include <fstream>

using namespace std::chrono;
using namespace std;


#define SIZE 1000



//initialise random array for matrix a and b
int mat_a[SIZE][SIZE], mat_b[SIZE][SIZE], mat_c[SIZE][SIZE];

void matrix_pop()
{   
    //print matrix a
    std::cout << "Matrix A" << "\n";     
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            mat_a[i][j] = rand() % 10;
            //std::cout << mat_a[i][j] << "\t";    
        }
        //std::cout << "\n";
    }    
    std::cout << "Matrix B" << "\n";
    //print matrix b   
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {   
            mat_b[i][j] = rand() % 10;
            //std::cout << mat_b[i][j] << "\t";
        }
        //std::cout << "\n";
    }  
}

void multmp(int i, int j, int k)
{
    //omp_set_num_threads(omp_get_num_procs());
    omp_set_num_threads(16);
		
    std::cout << "Matrix C" << "\n";   
    #pragma omp parallel for private(i,j,k)
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {   
            //mat_c[i][j] = 0;
            for (k = 0; k < SIZE; k++)
            {
                mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
            }
            //std::cout << mat_c[i][j] << "\t";
        }
        //std::cout << "\n";
    }
		
}

int main() 
{
    int i,j,k;
    int size = 5;
   
    srand(time(0));
    
    matrix_pop();

    auto start = high_resolution_clock::now();
    multmp(i,j,k);
    auto stop = high_resolution_clock::now(); 
    
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nTime taken by function : " << duration.count() << " Microseconds";
     // writing the resulting matrix in the file
    fstream matrixfile;

    matrixfile.open("results.txt", fstream::out);
    matrixfile<< "\nTime taken by function : " << duration.count() << " microseconds"<<"\n";
    matrixfile << "Matrix C"<<"\n";
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            matrixfile << mat_c[i][j] << " ";
        }
        matrixfile << endl;
    }
    matrixfile.close();
    return 0;
}