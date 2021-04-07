// Shows the impact indexing has on runtime
// Disable optimization
//

//#include "stdafx.h"
#include <iostream>
#include <intrin.h>
#include <chrono>
#include <iomanip> 

#define N 3000L
#define TIME_LOOP 500L
float_t m1[N][N];    // 3000x3000x4byte = 36MB, 12MB L3 cache size is 12MB
float_t m2[N][N];

int main()
{
    float_t temp;

    // init m2, m2 should be in cache
    for (auto& v : m2) {
        std::fill(std::begin(v), std::end(v), -1);
    }

    // unsync the I/O of C and C++. 
    std::ios_base::sync_with_stdio(false);

    auto start = std::chrono::high_resolution_clock::now();

    for (int t = 0; t < TIME_LOOP; ++t)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                temp = m1[j][i];    //loop over m1, that shouldn't be in the cache
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    // Calculating total time taken by the program. 
    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()/(double)TIME_LOOP;

    time_taken *= 1e-9;

    std::cout << "Time taken by loop is : " << std::fixed << time_taken << std::setprecision(9);
    std::cout << " sec" << std::endl;


    // init, m1 
    for (auto& v : m1) {
        std::fill(std::begin(v), std::end(v), -1);
    }


    // see https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/
    start = std::chrono::high_resolution_clock::now();

    for (int t = 0; t < TIME_LOOP; ++t)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                temp = m2[i][j];    // loop over m2, m1 in cache
            }
        }
    }

    end = std::chrono::high_resolution_clock::now();

    // Calculating total time taken by the program. 
    time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()/(double)TIME_LOOP;

    time_taken *= 1e-9;

    std::cout << "Time taken by loop is : " << std::fixed << time_taken << std::setprecision(9);
    std::cout << " sec" << std::endl;

    return 0;
}

