#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

#define NUM_PHILOSOPHERS 5
#define MAX_MEALS 10

using namespace std;

mutex chopsticks[NUM_PHILOSOPHERS];
mutex mtx;
int num_meals = 0;

void philosopher_thread(int philosopher_id);

int main()
{
    thread philosophers[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        philosophers[i] = thread(philosopher_thread, i);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        philosophers[i].join();
    return 0;
}

void philosopher_thread(int philosopher_id)
{
    int left_chopstick = philosopher_id;
    int right_chopstick = (philosopher_id + 1) % NUM_PHILOSOPHERS;

    while (true)
    {
        mtx.lock();
        if (num_meals >= MAX_MEALS)
        {
            cout << "Philosopher " << philosopher_id << " has finished dining.\n"
                 << endl;
            mtx.unlock();
            break;
        }
        mtx.unlock();

        // Pick up chopsticks in a predefined order
        chopsticks[left_chopstick].lock();
        chopsticks[right_chopstick].lock();

        cout << "Philosopher " << philosopher_id << " is eating.\n"
             << endl;
        this_thread::sleep_for(chrono::milliseconds(100));

        chopsticks[left_chopstick].unlock();
        chopsticks[right_chopstick].unlock();

        mtx.lock();
        num_meals++;
        mtx.unlock();

        cout << "Philosopher " << philosopher_id << " is thinking.\n"
             << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

/*
Aim: Write a program to implement the dining philosophers problem using semaphores.

Algorithm:
1. The program simulates the dining philosophers problem, where philosophers alternate between thinking and eating using chopsticks, with a maximum number of meals set to 10.
2. Each philosopher is represented by a separate thread, managed by the C++ `<thread>` library, allowing concurrent execution of their actions.
3. Chopsticks are represented by `std::mutex` objects to control access to them, ensuring that only one philosopher can use a chopstick at a time.
4. A global mutex (`mutex`) is used to control access to the shared variable `num_meals`, which tracks the total number of meals consumed.
5. The main function initializes the chopsticks, creates philosopher threads, and waits for them to finish dining by joining their threads.

*/