#include <bits/stdc++.h>

using namespace std;
const int QUANTUM = 2;

struct Process
{
    int processID;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void roundRobin(vector<Process> &processes)
{
    int currentTime = 0;
    int remainingProcesses = processes.size();

    while (remainingProcesses > 0)
    {
        for (int i = 0; i < processes.size(); i++)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0)
            {
                int executeTime = min(processes[i].remainingTime, QUANTUM);
                currentTime += executeTime;
                processes[i].remainingTime -= executeTime;
                if (processes[i].remainingTime == 0)
                {
                    remainingProcesses--;
                    processes[i].completionTime = currentTime;
                    processes[i].turnaroundTime =
                        processes[i].completionTime - processes[i].arrivalTime;
                    processes[i].waitingTime =
                        processes[i].turnaroundTime - processes[i].burstTime;
                }
            }
        }
    }
}

void calculateAverageTimes(const vector<Process> &processes, float &avgTurnaroundTime, float &avgWaitingTime)
{
    float totalTurnaroundTime = 0, totalWaitingTime = 0;
    for (const auto &process : processes)
    {
        totalTurnaroundTime += process.turnaroundTime;
        totalWaitingTime += process.waitingTime;
    }
    avgTurnaroundTime = totalTurnaroundTime / processes.size();
    avgWaitingTime = totalWaitingTime / processes.size();
}

int main()
{
    vector<Process> processes = {
        {1, 0, 6, 6, 0, 0, 0},
        {2, 2, 4, 4, 0, 0, 0},
        {3, 4, 8, 8, 0, 0, 0},
        {4, 6, 5, 5, 0, 0, 0},
        {5, 8, 3, 3, 0, 0, 0}};
    roundRobin(processes);
    float avgTurnaroundTime, avgWaitingTime;
    calculateAverageTimes(processes, avgTurnaroundTime, avgWaitingTime);
    cout << "Process\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;
    for (const auto &process : processes)
    {
        cout << process.processID << "\t"
             << process.completionTime << "\t\t"
             << process.turnaroundTime << "\t\t"
             << process.waitingTime << endl;
    }
    cout << "Average Turnaround Time: " << fixed << avgTurnaroundTime << endl;
    cout << "Average Waiting Time: " << fixed << avgWaitingTime << endl;
    return 0;
}
/*
Aim: Write a program to implement CPU scheduling algorithm for Round Robin.

Algorithm:
1. The code implements the Round Robin scheduling algorithm for a set of processes with a time quantum of 2 units.
2. A `Process` struct is defined to hold process attributes such as process ID, arrival time, burst time, remaining time, completion time, turnaround time, and waiting time.
3. The `roundRobin()` function iterates through processes, executing each for a time quantum or until completion, updating remaining time and process status accordingly.
4. After scheduling, the main function calculates the turnaround time and waiting time for each process and then prints these values along with completion times.
5. Finally, it calculates and prints the average turnaround time and average waiting time for all processes.


*/