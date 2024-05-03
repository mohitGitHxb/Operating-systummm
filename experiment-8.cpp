#include <bits/stdc++.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

using namespace std;

vector<int> available = {10, 5, 7};

vector<vector<int>> maximum = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}};

vector<vector<int>> allocation = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}};

vector<vector<int>> need(MAX_PROCESSES, vector<int>(MAX_RESOURCES));

void calculateNeed()
{
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        for (int j = 0; j < MAX_RESOURCES; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}
bool isSafeState(const vector<int> &work, const vector<bool> &finish, int process)
{
    for (int j = 0; j < MAX_RESOURCES; j++)
    {
        if (need[process][j] > work[j])
        {
            return false;
        }
    }
    return true;
}

bool bankersAlgorithm()
{
    calculateNeed();

    vector<int> work = available;
    vector<bool> finish(MAX_PROCESSES, false);
    vector<int> safeSequence;

    for (int k = 0; k < MAX_PROCESSES; k++)
    {
        bool found = false;
        for (int i = 0; i < MAX_PROCESSES; i++)
        {
            if (!finish[i] && isSafeState(work, finish, i))
            {
                for (int j = 0; j < MAX_RESOURCES; j++)
                {
                    work[j] += allocation[i][j];
                }
                safeSequence.push_back(i);
                finish[i] = true;
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "System is in an unsafe state (deadlock detected)" << endl;
            return false;
        }
    }

    cout << "System is in a safe state" << endl;
    cout << "Safe sequence: ";
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        cout << safeSequence[i] << " ";
    }
    cout << endl;
    return true;
}

int main()
{
    bankersAlgorithm();
    return 0;
}

/*
Aim: Write a program to implement banker’s algorithm.

Algorithm:
Initialize available, maximum, allocation, and need matrices.
Define a function ‘calculateNeed()’ to calculate the need matrix, which represents the resources that each process still needs to complete its execution.
Define a function ‘isSafeState()’ to check if the system is in a safe state by simulating resource allocation and checking if the system can safely grant resources to processes without encountering a deadlock.
Define a function ‘bankersAlgorithm()’ to simulate the Banker's Algorithm:
Calculate the need matrix.
Initialize a process sequence array with the sequence of processes to execute.
Check if the system is in a safe state using the ‘isSafeState()’ function.
If the system is in a safe state, print the safe sequence of processes to execute.
If the system is in an unsafe state (deadlock detected), print a message indicating the deadlock.
In the ‘main()’ function, call the ‘bankersAlgorithm()’ function to run the Banker's Algorithm.


*/