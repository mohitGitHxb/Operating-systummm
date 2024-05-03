#include <bits/stdc++.h>

using namespace std;
const int NUM_FRAMES = 3;

int findLRU(const vector<int> &pages, const vector<int> &frames, int n)
{
    int index = -1, lru = 999999;
    for (int i = 0; i < n; i++)
    {
        auto it = find(frames.begin(), frames.end(), pages[i]);
        if (it == frames.end())
            return i;
        int j = distance(frames.begin(), it);
        if (j < lru)
        {
            lru = j;
            index = i;
        }
    }
    return index;
}

void lruPageReplacement(const vector<int> &pages)
{
    vector<int> frames(NUM_FRAMES, -1);
    bool isPageFault = true;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++)
    {
        auto it = find(frames.begin(), frames.end(), pages[i]);
        if (it == frames.end())
        {
            int index = findLRU(pages, frames, i);
            frames[index] = pages[i];
            pageFaults++;
            isPageFault = true;
        }
        cout << "Step " << i + 1 << ": ";

        for (int j = 0; j < NUM_FRAMES; j++)
        {
            if (frames[j] != -1)
            {
                cout << frames[j] << " ";
            }
            else
            {
                cout << "- ";
            }
        }
        if (isPageFault)
        {
            cout << "(Page Fault)";
            isPageFault = false;
        }
        cout << endl;
    }
    cout << "\nTotal Page Faults: " << pageFaults << endl;
}

int main()
{
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    lruPageReplacement(pages);
    return 0;
}

/*
Aim: Write a program to implement LRU page replacement algorithm.

Algorithm:
Initialize an array ‘frames’ to represent the frames in memory, initially set to -1 to indicate empty frames.
Iterate through each page in the page reference string.
For each page:
Check if the page is already present in one of the frames. If it is, continue to the next page.
If the page is not present in any frame, find the least recently used (LRU) page in the frames using the ‘findLRU()’ function.
Replace the LRU page with the current page in the frames.
Increment the page fault counter.
Print the current state of frames along with the page fault indication.
After processing all pages, print the total number of page faults.
The ‘findLRU()’ function finds the index of the least recently used page in the frames by iterating through the pages seen so far and finding the page that has been used the longest time ago.


*/