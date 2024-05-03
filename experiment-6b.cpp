#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

#define N 5

using namespace std;

struct Node
{
    int data;
    Node *next;
};
struct Buffer
{
    Node *head, *tail;
    mutex mtx;
    condition_variable items;
    bool end;
    Buffer() : head(nullptr), tail(nullptr), end(false) {}
};

void insert(Buffer &b, int data)
{
    Node *n = new Node{data, nullptr};
    lock_guard<mutex> lock(b.mtx);
    if (!b.head)
        b.head = b.tail = n;
    else
    {
        b.tail->next = n;
        b.tail = n;
    }
    b.items.notify_one();
}

int remove(Buffer &b)
{
    unique_lock<mutex> lock(b.mtx);
    b.items.wait(lock, [&]
                 { return b.end || b.head; });
    if (b.end && !b.head)
        return -1;
    Node *n = b.head;
    int data = n->data;
    b.head = b.head->next;
    delete n;
    if (!b.head)
        b.tail = nullptr;
    return data;
}

void producer(Buffer &b)
{
    for (int i = 1; i <= 10; i++)
    {
        insert(b, i);
        cout << "Produced: " << i << '\n';
        this_thread::sleep_for(chrono::seconds(1));
    }
}
void consumer(Buffer &b)
{
    while (true)
    {
        int item = remove(b);
        if (item == -1)
        {
            cout << "End of production. Consumer exiting.\n";
            break;
        }
        cout << "Consumed: " << item << '\n';
        this_thread::sleep_for(chrono::seconds(2));
    }
}

int main()
{
    Buffer b;
    thread p(producer, ref(b)), c(consumer, ref(b));
    p.join();
    b.end = true;
    b.items.notify_one();
    c.join();
    return 0;
}

/*
Aim: Write a program to implement producer-consumer problem using unbounded buffer.

Algorithm:
1. Buffer Structure: Defines a buffer structure consisting of a linked list implementation (`Node` structure) and synchronization primitives (`std::mutex`, `std::condition_variable`) to manage access to the buffer.
2. Initialization and Destruction: Functions `buffer_init` and `buffer_destroy` respectively initialize and destroy the buffer, setting up the initial state and cleaning up resources like memory allocations.
3. Insertion and Removal: `buffer_insert` and `buffer_remove` functions respectively add data to the buffer and remove data from it. They ensure thread safety using mutex locks and condition variables to control access to the buffer.
4. Producer and Consumer Threads: `producer` and `consumer` functions represent the producer and consumer threads. The producer generates data and inserts it into the buffer, while the consumer retrieves data from the buffer for processing.
5. Main Function: Creates the producer and consumer threads, waits for them to finish (`join`), signals the end of production to the consumer thread, and cleans up the buffer resources after both threads have finished.


*/