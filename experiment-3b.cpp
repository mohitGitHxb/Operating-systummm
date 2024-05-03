#include <bits/stdc++.h>

using namespace std;
struct Process
{
    int processID;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
};

void computeCompletionTime(vector<Process> &processes)
{
    int currentTime = 0;
    int totalBurstTime = 0;
    processes[0].waitingTime = 0;
    for (const auto &process : processes)
        totalBurstTime += process.burstTime;
    while (totalBurstTime > 0)
    {
        int minBurstTime = INT_MAX;
        int minIndex = -1;
        for (int i = 0; i < processes.size(); ++i)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].burstTime < minBurstTime && processes[i].burstTime > 0)
            {

                minBurstTime = processes[i].burstTime;
                minIndex = i;
            }
        }
        currentTime += minBurstTime;
        totalBurstTime -= minBurstTime;

        processes[minIndex].completionTime = currentTime;
        processes[minIndex].waitingTime =
            currentTime - processes[minIndex].arrivalTime - processes[minIndex].burstTime;

        processes[minIndex].burstTime = 0;
    }
}

float calculateAverageWaitingTime(const vector<Process> &processes)
{
    float totalWaitingTime = 0;
    for (const auto &process : processes)
        totalWaitingTime += process.waitingTime;
    return totalWaitingTime / processes.size();
}

int main()
{
    vector<Process> processes = {
        {1, 0, 6, 0, 0},
        {2, 2, 4, 0, 0},
        {3, 4, 8, 0, 0},
        {4, 6, 5, 0, 0},
        {5, 8, 3, 0, 0}};
    computeCompletionTime(processes);
    cout << "Process\tCompletion Time\tWaiting Time\n";
    for (const auto &process : processes)
    {
        cout << process.processID << "\t"
             << process.completionTime << "\t\t"
             << process.waitingTime << "\n";
    }
    float avgWaitingTime = calculateAverageWaitingTime(processes);
    cout << "Average Waiting Time: " << avgWaitingTime << "\n";
    return 0;
}

/*
Aim: Write a program to implement CPU scheduling algorithm for SJF.

Algorithm:
1. The code defines a `Process` struct with attributes representing process ID, arrival time, burst time, completion time, and waiting time.
2. A function `computeCompletionTime()` schedules processes using the Shortest Job First (SJF) algorithm, updating completion and waiting times accordingly.
3. The main function initializes a vector of `Process` objects with predefined data representing processes' arrival and burst times.
4. After computing completion and waiting times, the main function prints each process's ID along with its completion and waiting times.
5. Finally, it calculates and prints the average waiting time for all processes based on their waiting times.


*/