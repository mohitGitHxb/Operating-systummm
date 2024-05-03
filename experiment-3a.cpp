#include <bits/stdc++.h>

using namespace std;

struct Process
{
    int processID;
    int arrivalTime;
    int burstTime;
    int completionTime;
};

void computeCompletionTime(vector<Process> &processes)
{
    int currentTime = 0;
    for (auto &process : processes)
    {
        if (currentTime < process.arrivalTime)
            currentTime = process.arrivalTime;
        process.completionTime = currentTime + process.burstTime;
        currentTime = process.completionTime;
    }
}

float calculateAverageTurnaroundTime(const vector<Process> &processes)
{
    float totalTurnaroundTime = 0;
    for (const auto &process : processes)
        totalTurnaroundTime += (process.completionTime - process.arrivalTime);
    return totalTurnaroundTime / processes.size();
}

int main()
{
    vector<Process> processes = {
        {1, 0, 6, 0},
        {2, 2, 4, 0},
        {3, 4, 8, 0},
        {4, 6, 5, 0},
        {5, 8, 3, 0}};

    computeCompletionTime(processes);

    cout << "Process\tCompletion Time\n";
    for (const auto &process : processes)
        cout << process.processID << "\t" << process.completionTime << endl;

    float avgTurnaroundTime = calculateAverageTurnaroundTime(processes);
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;

    return 0;
}

/*
Aim: Write a program to implement CPU scheduling algorithm for FCFS.

Algorithm:
1. The code defines a `Process` struct to represent a process with attributes such as process ID, arrival time, burst time, and completion time.
2. Two functions are defined: `computeCompletionTime(vector<Process>& processes)` to calculate the completion time for each process based on arrival and burst times, and `calculateAverageTurnaroundTime(const vector<Process>& processes)` to compute the average turnaround time for all processes.
3. In the `main()` function, a vector of `Process` objects is initialized with specific arrival and burst times.
4. The `computeCompletionTime()` function is called to determine the completion time for each process, updating the `completionTime` attribute in each `Process` object accordingly.
5. Finally, the completion times for each process are printed along with the average turnaround time for all processes.


*/