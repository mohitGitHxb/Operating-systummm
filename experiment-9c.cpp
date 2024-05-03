#include <bits/stdc++.h>
#define NUM_FRAMES 3
using namespace std;
void fifoPageReplacement(const vector<int> &pageReferences)
{
    vector<int> frames(NUM_FRAMES, -1);
    int pageFaults = 0;
    int oldestIndex = 0;
    for (int i = 0; i < pageReferences.size(); i++)
    {
        int currentPage = pageReferences[i];
        bool pageFound = false;
        for (int j = 0; j < NUM_FRAMES; j++)
        {
            if (frames[j] == currentPage)
            {
                pageFound = true;
                break;
            }
        }
        if (!pageFound)
        {
            frames[oldestIndex] = currentPage;
            pageFaults++;
            oldestIndex = (oldestIndex + 1) % NUM_FRAMES;
        }
        cout << "Step " << (i + 1) << ": ";
        for (int j = 0; j < NUM_FRAMES; j++)
        {
            if (frames[j] != -1)
                cout << frames[j] << " ";
            else
                cout << "- ";
        }
        if (!pageFound)
            cout << "(Page Fault)";
        cout << endl;
    }
    cout << "\nTotal Page Faults: " << pageFaults << endl;
}
int main()
{
    vector<int> pageReferences = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    fifoPageReplacement(pageReferences);
    return 0;
}

/*
Aim: Write a program to implement FIFO page replacement algorithm.

Algorithm:
Define a function ‘findOldest()’ to find the index of the oldest page in memory by iterating through the frames and finding the index of the page with the lowest value.
Implement a function ‘fifoPageReplacement()’ to perform FIFO page replacement:
Initialize an array of frames (‘frames’) to represent the frames in memory, initially set to -1 to indicate empty frames.
Initialize variables to track page faults and the index of the oldest page.
Iterate through each page reference in the page reference string.
For each page reference:
Check if the page is already present in one of the frames. If it is, continue to the next page reference.
If the page is not present in any frame, replace the oldest page in memory with the current page and update the oldest index.
Print the current state of frames along with the page fault indication.
After processing all page references, print the total number of page faults.
In the ‘main()’ function, define a page reference string and call the ‘fifoPageReplacement()’ function to perform FIFO page replacement.


*/