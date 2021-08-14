#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include <io.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

using namespace std::chrono;
using namespace std;
#define SIZE 1000
#define THREAD 2



int mat_a[SIZE][SIZE], mat_b[SIZE][SIZE], mat_c[SIZE][SIZE];
//keep track of threads being used
int step = 0;

void *multiply(void* args)
{
    int cores = step++;
    for (int i = cores * (SIZE / THREAD);i < (cores+1) * (SIZE / THREAD); i++)
    {
        for (int j = 0;j < SIZE; j++)
        {   
            //mat_c[i][j] = 0;
            for (int k = 0; k < SIZE;k++)
            {
                mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
            }
        }
    }
    return NULL;
}

void matrix_pop()
{
    //std::cout << "Matrix A" << "\n";
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            mat_a[i][j] = rand() % 10;
            //std::cout << mat_a[i][j] << "\t";    
        }
        //std::cout << "\n";
    }
    //std::cout << "Matrix B" << "\n";
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

int main()
{   
    srand(time(0));
    //populate matrix a and b
    matrix_pop();
    
    //start timer
    auto start = high_resolution_clock::now();
    pthread_t  *threads = new pthread_t[THREAD];
    
    //create threads for each thread to complete a part of the matrix
    for (int i = 0; i < THREAD; i++) 
    {
        pthread_create(&threads[i], NULL, multiply,NULL);
    }
    
    //joins threads back together to synchronise and finish
    for (int i = 0; i < THREAD; i++) 
    {
        pthread_join(threads[i], NULL);
    }
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    
    std::cout << "Result of Matrix A and B: " << endl;
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++)
        {
            //std::cout << mat_c[i][j] << " "; 
             
        }
        //std::cout << endl;   
    }
    sleep(3);
    cout << "\nTime taken by function : " << duration.count() << " microseconds";

    //write to file and save
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
