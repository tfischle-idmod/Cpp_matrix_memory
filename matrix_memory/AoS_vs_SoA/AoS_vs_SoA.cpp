// AoS_vs_SoA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip> 
#include <chrono>

#define N 10000
#define TIME_LOOP 5000L

static int32_t _age[N];
static int32_t next_id = 0;

class SoA {
public:
    SoA() { my_id = next_id;
            next_id++; };
    int32_t getAge() { return _age[my_id]; };
    void setAge(int32_t age) { _age[my_id] = age; };

private:
    int32_t my_id;
    double stuff[10];
};


class Aclass {
public:
    Aclass() {};
    int32_t getAge() { return age; };
    void setAge(int32_t age) { this->age = age; };
    void incAge(int32_t inc_age) { this->age += inc_age; }

private:
    int32_t age;
    //double stuff[10];
};

int main()
{
    int32_t temp;
    // unsync the I/O of C and C++. 
    std::ios_base::sync_with_stdio(false);

    std::vector<SoA> aos;
    std::vector<Aclass> aclass;
    for (int i = 0; i < N; ++i)
    {
        aos.push_back(SoA());
        aclass.push_back(Aclass());
    }

    for (int i = 0; i < N; ++i)
    {
        _age[i] = rand() % 80;
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int t = 0; t < TIME_LOOP; ++t)
    {
        for (int i = 0; i < N; ++i)
        {
            //std::cout << aos[i].getAge() << std::endl;
            aos[i].setAge(aos[i].getAge() + 1);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    // Calculating total time taken by the program. 
    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)TIME_LOOP;
    time_taken *= 1e-6;
    std::cout << "Time taken by loop is : " << std::fixed << time_taken << std::setprecision(9);
    std::cout << " ms" << std::endl;


    start = std::chrono::high_resolution_clock::now();
    for (int t = 0; t < TIME_LOOP; ++t)
    {
        for (int i = 0; i < N; ++i)
        {
            //std::cout << age[i] << std::endl;
            _age[i]++;
        }
    }
    end = std::chrono::high_resolution_clock::now();

    // Calculating total time taken by the program. 
    time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)TIME_LOOP;
    time_taken *= 1e-6;
    std::cout << "Time taken by loop is : " << std::fixed << time_taken << std::setprecision(9);
    std::cout << " ms" << std::endl;


    
    start = std::chrono::high_resolution_clock::now();
    for (int t = 0; t < TIME_LOOP; ++t)
    {
        for (int i = 0; i < N; ++i)
        {
            //aclass[i].setAge(aos[i].getAge() + 1);
            aclass[i].incAge(1);
        }
    }
    end = std::chrono::high_resolution_clock::now();

    // Calculating total time taken by the program. 
    time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)TIME_LOOP;
    time_taken *= 1e-6;
    std::cout << "Time taken by loop is : " << std::fixed << time_taken << std::setprecision(9);
    std::cout << "ms" << std::endl;
}

