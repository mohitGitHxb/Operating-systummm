#include <bits/stdc++.h>
#define NUM_FRAMES 3
using namespace std;

int findOptimal(const vector<int> &pageReferences,
                const vector<int> &frames, int currentIndex)
{
    int farthestIndex = -1;
    int farthestDistance = INT_MIN;
    for (int i = 0; i < NUM_FRAMES; i++)
    {
        int j;
        for (j = currentIndex; j < pageReferences.size(); j++)
        {
            if (frames[i] == pageReferences[j])
            {
                if (j > farthestDistance)
                {
                    farthestDistance = j;
                    farthestIndex = i;
                }
                break;
            }
        }
        if (j == pageReferences.size())
            return i;
    }
    return (farthestIndex == -1) ? 0 : farthestIndex;
}

void optimalPageReplacement(const vector<int> &pageReferences)
{
    vector<int> frames(NUM_FRAMES, -1);
    int pageFaults = 0;
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
            int victimIndex = findOptimal(pageReferences, frames, i + 1);
            frames[victimIndex] = currentPage;
            pageFaults++;
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
    optimalPageReplacement(pageReferences);
    return 0;
}

/*
Aim: Write a program to implement optimal page replacement algorithm.

Algorithm:
Define a function ‘findOptimal()’ to find the page that will not be used for the longest period of time in the future by iterating through the remaining page references and finding the farthest reference for each page in the frames.
Implement a function ‘optimalPageReplacement()’ to perform Optimal page replacement:
Initialize an array of frames (‘frames’) to represent the frames in memory, initially set to -1 to indicate empty frames.
Initialize variables to track page faults.
Iterate through each page reference in the page reference string.
For each page reference:
Check if the page is already present in one of the frames. If it is, continue to the next page reference.
If the page is not present in any frame, replace the page with the optimal choice based on future references.
Print the current state of frames along with the page fault indication.
After processing all page references, print the total number of page faults.
In the ‘main()’ function, define a page reference string and call the ‘optimalPageReplacement()’ function to perform Optimal page replacement.


*/