// AoS_vs_SoA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip> 
#include <chrono>

#define N 10000
#define TIME_LOOP 200L


class Infection {
public:
    Infection(): infection_id(0) {};
    void update() { infection_id++; };

private:
    int32_t infection_id;
    double stuff[100];
};

class Infections {
public:
    Infections(): infections() {};
    std::vector<Infection*> infections;
};

class Individual_ptr {
public:
    Individual_ptr(): infections(nullptr) {};
    Infections* infections;
};

class Individual{
public:
    Individual() {};
    std::vector<Infection> infections;
};



int main()
{
    int32_t temp;
    // unsync the I/O of C and C++. 
    std::ios_base::sync_with_stdio(false);

    std::vector<Individual_ptr> individual_ptr;
    std::vector<Individual> individual;

    for (int i = 0; i < N; ++i)
    {
        Individual_ptr ind;
        Infections* infs = new Infections();
        infs->infections.push_back(new Infection());
        infs->infections.push_back(new Infection());
        ind.infections = infs;
        individual_ptr.push_back(ind);
    }


    auto start = std::chrono::high_resolution_clock::now();
    for (int t = 0; t < TIME_LOOP; ++t)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j= 0; j < individual_ptr[i].infections->infections.size(); j++)
            {
                individual_ptr[i].infections->infections[j]->update();
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    // Calculating total time taken by the program. 
    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)TIME_LOOP;
    time_taken *= 1e-6;
    std::cout << "Time taken by loop is : " << std::fixed << time_taken << std::setprecision(9);
    std::cout << " ms" << std::endl;


    for (int i = 0; i < N; ++i)
    {
        Individual ind;
        ind.infections.push_back(Infection());
        ind.infections.push_back(Infection());
        individual.push_back(ind);
    }


    start = std::chrono::high_resolution_clock::now();
    for (int t = 0; t < TIME_LOOP; ++t)
    {
        for (int i = 0; i < N; ++i)
        {
            for (Infection& inf : individual[i].infections)
            {
                inf.update();
            }
        }
    }
    end = std::chrono::high_resolution_clock::now();

    // Calculating total time taken by the program. 
    time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)TIME_LOOP;
    time_taken *= 1e-6;
    std::cout << "Time taken by loop is : " << std::fixed << time_taken << std::setprecision(9);
    std::cout << " ms" << std::endl;
}

