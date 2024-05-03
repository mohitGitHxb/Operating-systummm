#include <bits/stdc++.h>
#define NR 3
#define NW 2
using namespace std;

mutex m1, m2;
int rc = 0;

void wt(int id)
{
    cout << "Writer " << id << " is trying to write.\n";
    lock_guard<mutex> lock(m2);
    cout << "Writer " << id << " is writing.\n";
    cout << "Writer " << id << " finished writing.\n";
}

void rt(int id)
{
    cout << "Reader " << id << " is trying to read.\n";
    {
        lock_guard<mutex> lock(m1);
        rc++;
        if (rc == 1)
            m2.lock();
    }
    cout << "Reader " << id << " is reading.\n";
    cout << "Reader " << id << " finished reading.\n";
    {
        lock_guard<mutex> lock(m1);
        rc--;
        if (rc == 0)
            m2.unlock();
    }
}

int main()
{
    vector<thread> r(NR), w(NW);

    for (int i = 0; i < max(NR, NW); i++)
    {
        if (i < NW)
            w[i] = thread(wt, i + 1);
        if (i < NR)
            r[i] = thread(rt, i + 1);
    }

    for (auto &th : w)
        if (th.joinable())
            th.join();
    for (auto &th : r)
        if (th.joinable())
            th.join();

    return 0;
}

/*
Aim: Write a program to implement readers-writers problem using semaphores.

Algorithm:
1. Initialize and start threads for readers and writers using `std::thread`, assigning specific IDs.
2. Readers increment `read_count` while locking `mutex`, also locking `rw_mutex` if they are the first reader.
3. Writers attempt to acquire `rw_mutex` for exclusive resource access, perform writing, and release the lock.
4. Readers acquire `mutex` before accessing `read_count`, locking `rw_mutex` if they are the first reader.
5. Main function waits for all threads to finish with `join()`.

*/