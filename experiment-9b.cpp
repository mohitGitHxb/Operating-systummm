#include <bits/stdc++.h>
#define NUM_FRAMES 3
using namespace std;

struct Page
{
    int pageID;
    bool referenced;
    Page(int id) : pageID(id), referenced(false) {}
};

int findVictim(vector<Page> &frames)
{
    int minIndex = 0;
    for (int i = 1; i < frames.size(); i++)
        if (frames[i].referenced < frames[minIndex].referenced)
            minIndex = i;
    return minIndex;
}

void lruApproximationPageReplacement(const vector<int> &pageReferences)
{
    vector<Page> frames(NUM_FRAMES, Page(-1));
    int pageFaults = 0;

    for (int i = 0; i < pageReferences.size(); i++)
    {
        int currentPage = pageReferences[i];
        bool pageFound = false;

        for (int j = 0; j < NUM_FRAMES; j++)
        {
            if (frames[j].pageID == currentPage)
            {
                frames[j].referenced = true;
                pageFound = true;
                break;
            }
        }
        if (!pageFound)
        {
            int victimIndex = findVictim(frames);
            frames[victimIndex] = Page(currentPage);
            pageFaults++;
        }
        cout << "Step " << (i + 1) << ": ";
        for (int j = 0; j < NUM_FRAMES; j++)
        {
            if (frames[j].pageID != -1)
                cout << frames[j].pageID << "(" << frames[j].referenced << ") ";
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
    lruApproximationPageReplacement(pageReferences);
    return 0;
}

/*

Aim: Write a program to implement LRU-approximation page replacement algorithm.

Algorithm:
Define a ‘Page’ structure to represent a page, which includes a page ID and a boolean flag (‘referenced’) to indicate whether the page has been referenced.
Implement a function ‘initializePage()’ to initialize a page with a given page ID and set the referenced flag to false.
Implement a function ‘findVictim()’ to find the victim page using LRU-Approximation. It selects the page with the least recently referenced bit as the victim.
Implement a function ‘lruApproximationPageReplacement()’ to perform LRU-Approximation page replacement:
Initialize an array of pages (‘frames’) to represent the frames in memory, initially set to empty pages.
Iterate through each page reference in the page reference string.
For each page reference:
Check if the page is already present in one of the frames. If it is, set the referenced bit for that page and continue to the next page reference.
If the page is not present in any frame, find a victim page using the ‘findVictim()’ function and replace it with the current page.
Print the current state of frames along with the page fault indication.
After processing all page references, print the total number of page faults.
In the ‘main()’ function, define a page reference string and call the ‘lruApproximationPageReplacement()’ function to perform LRU-Approximation page replacement.


*/