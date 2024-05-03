#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int processID;
    int arrivalTime;
    int burstTime;
    int priority;
    int turnaroundTime = 0; // Initialize to 0
    int waitingTime = 0;    // Initialize to 0
    int remainingTime;      // Add remaining time for tracking
};

// Comparator for priority queue
struct Compare
{
    bool operator()(Process *p1, Process *p2)
    {
        return p1->priority > p2->priority;
    }
};

void preemptivePriority(vector<Process> &processes)
{
    // Sort processes by arrival time to handle arrival in order
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.arrivalTime < b.arrivalTime; });

    for (auto &process : processes)
    {
        process.remainingTime = process.burstTime; // Initialize remaining time
    }

    priority_queue<Process *, vector<Process *>, Compare> processQueue;
    int currTime = 0, completed = 0;
    int i = 0;

    while (completed != processes.size())
    {
        // Add processes that have arrived by currTime
        while (i < processes.size() && processes[i].arrivalTime <= currTime)
        {
            processQueue.push(&processes[i]);
            i++;
        }

        if (!processQueue.empty())
        {
            Process *currentProcess = processQueue.top();
            processQueue.pop();
            currentProcess->remainingTime -= 1; // Execute for 1 time unit
            currTime++;                         // Increment current time

            if (currentProcess->remainingTime == 0)
            {
                completed++;
                currentProcess->turnaroundTime = currTime - currentProcess->arrivalTime;
                currentProcess->waitingTime = currentProcess->turnaroundTime - currentProcess->burstTime;
            }
            else
            {
                // Re-add the process to the queue if it's not finished
                processQueue.push(currentProcess);
            }
        }
        else
        {
            // If no process is available to execute, just increment the time
            currTime++;
        }
    }
}

void printProcesses(const vector<Process> &processes)
{
    cout << "Process\tTurnaround Time\tWaiting Time\n";
    for (const Process &process : processes)
    {
        cout << process.processID << "\t\t" << process.turnaroundTime << "\t\t\t" << process.waitingTime << endl;
    }
}

int main()
{
    vector<Process> processes = {
        {1, 0, 6, 2},
        {2, 2, 4, 1},
        {3, 4, 8, 3},
        {4, 6, 5, 4},
        {5, 8, 3, 5}};
    preemptivePriority(processes);
    cout << "Process Details:\n";
    printProcesses(processes);
    int totalTurnaroundTime = 0, totalWaitingTime = 0;
    for (const Process &process : processes)
    {
        totalTurnaroundTime += process.turnaroundTime;
        totalWaitingTime += process.waitingTime;
    }
    double avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / processes.size();
    double avgWaitingTime = static_cast<double>(totalWaitingTime) / processes.size();

    cout << "\nAverage Turnaround Time: " << avgTurnaroundTime << endl;
    cout << "Average Waiting Time: " << avgWaitingTime << endl;
    return 0;
}

/*
Aim: Write a program to implement CPU scheduling algorithm for Preemptive Priority Scheduling.

Algorithm:
1. The code defines a `Process` struct representing a process with attributes such as process ID, arrival time, burst time, priority, turnaround time, and waiting time.
2. It also defines a `Compare` struct with an overloaded `operator()` to compare processes based on their priority for use in the priority queue.
3. The `preemptivePriority()` function implements the preemptive priority scheduling algorithm, where processes are executed based on their priority, with higher priority processes being executed first.
4. Inside the main loop of `preemptivePriority()`, the code selects the process with the highest priority from the priority queue and executes it for the required time quantum or until completion, updating process status accordingly.
5. After scheduling, the main function prints the turnaround time and waiting time for each process.

*/