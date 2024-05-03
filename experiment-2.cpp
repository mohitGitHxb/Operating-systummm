#include <iostream>
#include <thread>
#include <vector>

using namespace std;

#define NUM_THREADS 5

void doSomething(int id) { cout << "Thread #" << id << " says hello!\n"; }

void spawnThreads(int n)
{
    vector<thread> threads(n);
    for (int i = 0; i < n; i++)
        threads[i] = thread(doSomething, i + 1);
    for (auto &thread : threads)
        thread.join();
}

int main()
{
    spawnThreads(NUM_THREADS);
    cout << "All threads have completed.\n";
    return 0;
}

/*
Aim: Write a program to implement threads.

Algorithm:
1. The code defines a function `doSomething(int id)` that simply outputs a message indicating the thread number.
2. Another function `spawnThreads(int n)` creates a vector of threads and assigns each thread to execute the `doSomething` function with a unique ID.
3. In the `main()` function, `spawnThreads(NUM_THREADS)` is called to create and execute a specified number of threads.
4. Each thread executes `doSomething` function concurrently, printing a message with its respective ID.
5. Finally, `join()` ensures that the main thread waits for all created threads to finish before printing "All threads have completed" and returning.


*/