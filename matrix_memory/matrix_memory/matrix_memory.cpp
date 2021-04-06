// Shows the impact indexing has on runtime
// Disable optimization
//

//#include "stdafx.h"
#include <iostream>
#include <intrin.h>
#include <chrono>
#include <iomanip> 

#define N 1000L
#define TIME_LOOP 200L

int main()
{
    float m[N][N];
    
    // unsync the I/O of C and C++. 
    std::ios_base::sync_with_stdio(false);

    // see https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/
    auto start = std::chrono::high_resolution_clock::now();

    for (int t = 0; t < TIME_LOOP; ++t)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                m[i][j] = 1.0;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    // Calculating total time taken by the program. 
    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()/TIME_LOOP;

    time_taken *= 1e-9;

    std::cout << "Time taken by loop is : " << std::fixed << time_taken << std::setprecision(9);
    std::cout << " sec" << std::endl;


    // see https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/
    start = std::chrono::high_resolution_clock::now();

    for (int t = 0; t < TIME_LOOP; ++t)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                m[j][i] = 2.0;
            }
        }
    }

    end = std::chrono::high_resolution_clock::now();

    // Calculating total time taken by the program. 
    time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()/TIME_LOOP;

    time_taken *= 1e-9;

    std::cout << "Time taken by loop is : " << std::fixed << time_taken << std::setprecision(9);
    std::cout << " sec" << std::endl;


    return 0;
}

