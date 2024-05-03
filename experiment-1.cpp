#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;
void childProcess()
{
    cout << "Child process ID: " << getpid() << endl;
    sleep(3);
    cout << "Child process exiting..." << endl;
    exit(0);
}
void parentProcess(pid_t child_pid)
{
    cout << "Parent process ID: " << getpid() << endl;
    cout << "Waiting for child process to finish..." << endl;
    wait(NULL);
    cout << "Child process terminated." << endl;
}
int main()
{
    pid_t child_pid;
    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (child_pid == 0)
        childProcess();
    else
        parentProcess(child_pid);
    cout << "Exiting..." << endl;
    return 0;
}

/*
Aim: Write a program to implement process creation and termination for an operating system (fork, wait, signal, exit, etc.).

Algorithm:
1. Forking: The program creates a new process using `fork()`, which duplicates the current process, creating a parent process and a child process.
2. Child Process: The child process executes a function (`childProcess()`) that displays its process ID (`getpid()`), waits for 3 seconds (`sleep(3)`), and then exits using `exit(0)`.
3. Parent Process: The parent process executes a function (`parentProcess()`) that displays its process ID (`getpid()`), waits for the child process to terminate using `wait(NULL)`, and then prints a message indicating the child process has terminated.
4. Error Handling: If `fork()` fails (returns -1), an error message is printed using `perror()` and the program exits with a status of 1.
5. Main Function: In the `main()` function, the program determines whether it's in the parent or child process based on the return value of `fork()`, and then executes the appropriate process function (`childProcess()` or `parentProcess()`). Finally, it prints "Exiting..." and returns 0.


*/