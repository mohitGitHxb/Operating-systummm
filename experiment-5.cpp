#include <iostream>
#include <thread>
#include <mutex>
#define NUM_THREADS 5
using namespace std;

int counter = 0;
mutex mtx;

void criticalSection(int threadID)
{
    lock_guard<mutex> lock(mtx);
    cout << "Thread #" << threadID << " is in critical section" << endl;
    counter++;
    cout << "Thread #" << threadID << " is in non-critical section" << endl;
}

int main()
{
    thread threads[NUM_THREADS];
    for (int t = 0; t < NUM_THREADS; t++)
    {
        cout << "Creating thread " << t << endl;
        threads[t] = thread(criticalSection, t);
    }
    for (int t = 0; t < NUM_THREADS; t++)
    {
        threads[t].join();
    }
    cout << "Counter value after execution: " << counter << endl;
    return 0;
}

/*
Aim: Write a program to implement critical section problem.

Algorithm:
1. Define `NUM_THREADS` to control the number of threads.
2. Implement `criticalSection` function to simulate mutual exclusion using a mutex to increment a shared counter.
3. In `main`, create `NUM_THREADS` threads, each executing `criticalSection` with a unique thread ID. After all threads join back, print the final value of the shared counter..


*/