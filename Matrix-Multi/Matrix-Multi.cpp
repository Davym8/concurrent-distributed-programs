
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <fstream>

using namespace std::chrono;
using namespace std;

#define arraysize 1000
int a[arraysize][arraysize], b[arraysize][arraysize], c[arraysize][arraysize];

int main(int argc,char** argv)
{   
    //initialise random array for matrix a and b
    
    srand(time(0));
    //print matrix a
    std::cout << "Matrix A Done" << "\n";
    for (int i = 0; i < arraysize; i++)
    {
        for (int j = 0; j < arraysize; j++)
        {
            a[i][j] = rand() % 10;
            //std::cout << a[i][j] << "\t";    
        }
        //std::cout << "\n";
    }
    std::cout << "Matrix B Done" << "\n";
    //print matrix b
    for (int i = 0; i < arraysize; i++)
    {
        for (int j = 0; j < arraysize; j++)
        {   
            b[i][j] = rand() % 10;
            //std::cout << b[i][j] << "\t";
        }
        //std::cout << "\n";
    }
    //start timer
    auto start = high_resolution_clock::now();
    //matrix multiplication C
    std::cout << "Matrix Multiplication C Done"<<"\n";
    for (int i = 0; i < arraysize; i++)
    {
        for (int j = 0; j < arraysize; j++)
        {   
            c[i][j] = 0;
            for (int k = 0; k < arraysize; k++)
            {
                c[i][j] += a[i][k] * b[k][j];               
            }
            //std::cout << c[i][j] << "\t";
        }
        //std::cout << "\n";
    }
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nTime taken by function : " << duration.count() << " microseconds";

    // writing the resulting matrix in the file
    fstream matrixfile;

    matrixfile.open("results.txt", fstream::out);
    matrixfile<< "\nTime taken by function : " << duration.count() << " microseconds"<<"\n";
    matrixfile << "Matrix C"<<"\n";
    for (int i = 0; i < arraysize; i++)
    {
        for (int j = 0; j < arraysize; j++)
        {
            matrixfile << c[i][j] << " ";
        }
        matrixfile << endl;
    }
    matrixfile.close();
    return 0;
}
