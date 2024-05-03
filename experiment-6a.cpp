#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cstdlib>
#include <ctime>
#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define NUM_ITEMS 10
using namespace std;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
mutex mtx;
condition_variable cv_empty, cv_full;
void producer();
void consumer();
void insert_item(int item);
int remove_item();
int main()
{
    thread producer_threads[NUM_PRODUCERS];
    thread consumer_threads[NUM_CONSUMERS];
    for (int i = 0; i < NUM_PRODUCERS; ++i)
        producer_threads[i] = thread(producer);
    for (int i = 0; i < NUM_CONSUMERS; ++i)
        consumer_threads[i] = thread(consumer);
    for (int i = 0; i < NUM_PRODUCERS; ++i)
        producer_threads[i].join();
    for (int i = 0; i < NUM_CONSUMERS; ++i)
        consumer_threads[i].join();
    return 0;
}
void producer()
{
    int produced_items = 0;
    while (produced_items < NUM_ITEMS)
    {
        int item = rand() % 100;
        {
            unique_lock<mutex> lock(mtx);
            cv_empty.wait(lock, []
                          { return (in + 1) % BUFFER_SIZE != out; });
            insert_item(item);
            cout << "Producer produced item: " << item << endl;
        }
        cv_full.notify_one();
        ++produced_items;
    }
}
void consumer()
{
    int consumed_items = 0;
    while (consumed_items < NUM_ITEMS)
    {
        {
            unique_lock<mutex> lock(mtx);
            cv_full.wait(lock, []
                         { return in != out; });
            int item = remove_item();
            cout << "Consumer consumed item: " << item << endl;
        }
        cv_empty.notify_one();
        ++consumed_items;
    }
}
void insert_item(int item)
{
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
}
int remove_item()
{
    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    return item;
}

/*
Aim: Write a program to implement producer-consumer problem using bounded buffer.

Algorithm:
1. Producer-Consumer Problem: The code addresses the classic synchronization problem where multiple producers produce items and multiple consumers consume them concurrently from a shared buffer.
2. Thread Synchronization: It employs mutexes (`mtx`) and condition variables (`cv_empty` and `cv_full`) to ensure thread safety and coordination between producers and consumers when accessing the shared buffer.
3. Buffer Implementation: The shared buffer is implemented as a circular array (`buffer`) with a fixed size (`BUFFER_SIZE`). Producers insert items into the buffer, and consumers remove items from it.
4. Producer Function: The `producer` function generates random items and inserts them into the buffer. It waits on the `cv_empty` condition variable when the buffer is full, signaling that it needs space to produce more items.
5. Consumer Function: The `consumer` function retrieves items from the buffer. It waits on the `cv_full` condition variable when the buffer is empty, indicating that it needs items to consume.

*/