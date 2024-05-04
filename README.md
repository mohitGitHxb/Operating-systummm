# Operating Systems Practical File

## Index

1. [Experiment 1](#experiment-1)
2. [Experiment 2](#experiment-2)
3. [Experiment 3a](#experiment-3a)
4. [Experiment 3b](#experiment-3b)
5. [Experiment 3c](#experiment-3c)
6. [Experiment 3d](#experiment-3d)
7. [Experiment 4](#experiment-4)
8. [Experiment 5](#experiment-5)
9. [Experiment 6a](#experiment-6a)
10. [Experiment 6b](#experiment-6b)
11. [Experiment 7a](#experiment-7a)
12. [Experiment 7b](#experiment-7b)
13. [Experiment 8](#experiment-8)
14. [Experiment 9a](#experiment-9a)
15. [Experiment 9b](#experiment-9b)
16. [Experiment 9c](#experiment-9c)
17. [Experiment 9d](#experiment-9d)

## Experiment 1
### Aim
Write a program to implement process creation and termination for an operating system (fork, wait, signal, exit, etc.).

### Algorithm
1. Forking: The program creates a new process using `fork()`, which duplicates the current process, creating a parent process and a child process.
2. Child Process: The child process executes a function (`childProcess()`) that displays its process ID (`getpid()`), waits for 3 seconds (`sleep(3)`), and then exits using `exit(0)`.
3. Parent Process: The parent process executes a function (`parentProcess()`) that displays its process ID (`getpid()`), waits for the child process to terminate using `wait(NULL)`, and then prints a message indicating the child process has terminated.
4. Error Handling: If `fork()` fails (returns -1), an error message is printed using `perror()` and the program exits with a status of 1.
5. Main Function: In the `main()` function, the program determines whether it's in the parent or child process based on the return value of `fork()`, and then executes the appropriate process function (`childProcess()` or `parentProcess()`). Finally, it prints "Exiting..." and returns 0.

## Experiment 2
### Aim
Write a program to implement threads.

### Algorithm
1. The code defines a function `doSomething(int id)` that simply outputs a message indicating the thread number.
2. Another function `spawnThreads(int n)` creates a vector of threads and assigns each thread to execute the `doSomething` function with a unique ID.
3. In the `main()` function, `spawnThreads(NUM_THREADS)` is called to create and execute a specified number of threads.
4. Each thread executes `doSomething` function concurrently, printing a message with its respective ID.
5. Finally, `join()` ensures that the main thread waits for all created threads to finish before printing "All threads have completed" and returning.

## Experiment 3a
### Aim
Write a program to implement CPU scheduling algorithm for FCFS.

### Algorithm
1. The code defines a `Process` struct to represent a process with attributes such as process ID, arrival time, burst time, and completion time.
2. Two functions are defined: `computeCompletionTime(vector<Process>& processes)` to calculate the completion time for each process based on arrival and burst times, and `calculateAverageTurnaroundTime(const vector<Process>& processes)` to compute the average turnaround time for all processes.
3. In the `main()` function, a vector of `Process` objects is initialized with specific arrival and burst times.
4. The `computeCompletionTime()` function is called to determine the completion time for each process, updating the `completionTime` attribute in each `Process` object accordingly.
5. Finally, the completion times for each process are printed along with the average turnaround time for all processes.

## Experiment 3b
### Aim
Write a program to implement CPU scheduling algorithm for SJF.

### Algorithm
1. The code defines a `Process` struct with attributes representing process ID, arrival time, burst time, completion time, and waiting time.
2. A function `computeCompletionTime()` schedules processes using the Shortest Job First (SJF) algorithm, updating completion and waiting times accordingly.
3. The main function initializes a vector of `Process` objects with predefined data representing processes' arrival and burst times.
4. After computing completion and waiting times, the main function prints each process's ID along with its completion and waiting times.
5. Finally, it calculates and prints the average waiting time for all processes based on their waiting times.

## Experiment 3c
### Aim
Write a program to implement CPU scheduling algorithm for Round Robin.

### Algorithm
1. The code implements the Round Robin scheduling algorithm for a set of processes with a time quantum of 2 units.
2. A `Process` struct is defined to hold process attributes such as process ID, arrival time, burst time, remaining time, completion time, turnaround time, and waiting time.
3. The `roundRobin()` function iterates through processes, executing each for a time quantum or until completion, updating remaining time and process status accordingly.
4. After scheduling, the main function calculates the turnaround time and waiting time for each process and then prints these values along with completion times.
5. Finally, it calculates and prints the average turnaround time and average waiting time for all processes.

## Experiment 3d
### Aim
Write a program to implement CPU scheduling algorithm for Preemptive Priority Scheduling.

### Algorithm
1. The code defines a `Process` struct representing a process with attributes such as process ID, arrival time, burst time, priority, turnaround time, and waiting time.
2. It also defines a `Compare` struct with an overloaded `operator()` to compare processes based on their priority for use in the priority queue.
3. The `preemptivePriority()` function implements the preemptive priority scheduling algorithm, where processes are executed based on their priority, with higher priority processes being executed first.
4. Inside the main loop of `preemptivePriority()`, the code selects the process with the highest priority from the priority queue and executes it for the required time quantum or until completion, updating process status accordingly.
5. After scheduling, the main function prints the turnaround time and waiting time for each process.

## Experiment 4
### Aim
Write a program to implement inter process communication.

### Algorithm
1. The code sets up inter-process communication using a pipe, allowing data exchange between a parent and child process.
2. It creates a pipe using the `pipe()` function and checks for errors during pipe creation.
3. After forking a child process, the parent process closes the write end of the pipe and reads data from the read end using `read()`.
4. The child process closes the read end of the pipe, writes a message to the write end using `write()`, and then closes the write end.
5. Finally, both parent and child processes close the remaining ends of the pipe to release system resources.

## Experiment 5
### Aim
Write a program to implement critical section problem.

### Algorithm
1. Define `NUM_THREADS` to control the number of threads.
2. Implement `criticalSection` function to simulate mutual exclusion using a mutex to increment a shared counter.
3. In `main`, create `NUM_THREADS` threads, each executing `criticalSection` with a unique thread ID. After all threads join back, print the final value of the shared counter.

## Experiment 6a
### Aim
Write a program to implement producer-consumer problem using bounded buffer.

### Algorithm
1. Producer-Consumer Problem: The code addresses the classic synchronization problem where multiple producers produce items and multiple consumers consume them concurrently from a shared buffer.
2. Thread Synchronization: It employs mutexes (`mtx`) and condition variables (`cv_empty` and `cv_full`) to ensure thread safety and coordination between producers and consumers when accessing the shared buffer.
3. Buffer Implementation: The shared buffer is implemented as a circular array (`buffer`) with a fixed size (`BUFFER_SIZE`). Producers insert items into the buffer, and consumers remove items from it.
4. Producer Function: The `producer` function generates random items and inserts them into the buffer. It waits on the `cv_empty` condition variable when the buffer is full, signaling that it needs space to produce more items.
5. Consumer Function: The `consumer` function retrieves items from the buffer. It waits on the `cv_full` condition variable when the buffer is empty, indicating that it needs items to consume.

## Experiment 6b
### Aim
Write a program to implement producer-consumer problem using unbounded buffer.

### Algorithm
1. Buffer Structure: Defines a buffer structure consisting of a linked list implementation (`Node` structure) and synchronization primitives (`std::mutex`, `std::condition_variable`) to manage access to the buffer.
2. Initialization and Destruction: Functions `buffer_init` and `buffer_destroy` respectively initialize and destroy the buffer, setting up the initial state and cleaning up resources like memory allocations.
3. Insertion and Removal: `buffer_insert` and `buffer_remove` functions respectively add data to the buffer and remove data from it. They ensure thread safety using mutex locks and condition variables to control access to the buffer.
4. Producer and Consumer Threads: `producer` and `consumer` functions represent the producer and consumer threads. The producer generates data and inserts it into the buffer, while the consumer retrieves data from the buffer for processing.
5. Main Function: Creates the producer and consumer threads,waits for them to finish (`join`), signals the end of production to the consumer thread, and cleans up the buffer resources after both threads have finished.

## Experiment 7a
### Aim
Write a program to implement readers-writers problem using semaphores.

### Algorithm
1. Initialize and start threads for readers and writers using `std::thread`, assigning specific IDs.
2. Readers increment `read_count` while locking `mutex`, also locking `rw_mutex` if they are the first reader.
3. Writers attempt to acquire `rw_mutex` for exclusive resource access, perform writing, and release the lock.
4. Readers acquire `mutex` before accessing `read_count`, locking `rw_mutex` if they are the first reader.
5. Main function waits for all threads to finish with `join()`.

## Experiment 7b
### Aim
Write a program to implement the dining philosophers problem using semaphores.

### Algorithm
1. The program simulates the dining philosophers problem, where philosophers alternate between thinking and eating using chopsticks, with a maximum number of meals set to 10.
2. Each philosopher is represented by a separate thread, managed by the C++ `<thread>` library, allowing concurrent execution of their actions.
3. Chopsticks are represented by `std::mutex` objects to control access to them, ensuring that only one philosopher can use a chopstick at a time.
4. A global mutex (`mutex`) is used to control access to the shared variable `num_meals`, which tracks the total number of meals consumed.
5. The main function initializes the chopsticks, creates philosopher threads, and waits for them to finish dining by joining their threads.

## Experiment 8
### Aim
Write a program to implement banker's algorithm.

### Algorithm
1. Initialize available, maximum, allocation, and need matrices.
2. Define a function 'calculateNeed()' to calculate the need matrix, which represents the resources that each process still needs to complete its execution.
3. Define a function 'isSafeState()' to check if the system is in a safe state by simulating resource allocation and checking if the system can safely grant resources to processes without encountering a deadlock.
4. Define a function 'bankersAlgorithm()' to simulate the Banker's Algorithm:
    a. Calculate the need matrix.
    b. Initialize a process sequence array with the sequence of processes to execute.
    c. Check if the system is in a safe state using the 'isSafeState()' function.
    d. If the system is in a safe state, print the safe sequence of processes to execute.
    e. If the system is in an unsafe state (deadlock detected), print a message indicating the deadlock.
5. In the 'main()' function, call the 'bankersAlgorithm()' function to run the Banker's Algorithm.

## Experiment 9a
### Aim
Write a program to implement LRU page replacement algorithm.

### Algorithm
1. Initialize an array 'frames' to represent the frames in memory, initially set to -1 to indicate empty frames.
2. Iterate through each page in the page reference string.
3. For each page:
    a. Check if the page is already present in one of the frames. If it is, continue to the next page.
    b. If the page is not present in any frame, find the least recently used (LRU) page in the frames using the 'findLRU()' function.
    c. Replace the LRU page with the current page in the frames.
    d. Increment the page fault counter.
    e. Print the current state of frames along with the page fault indication.
4. After processing all pages, print the total number of page faults.
5. The 'findLRU()' function finds the index of the least recently used page in the frames by iterating through the pages seen so far and finding the page that has been used the longest time ago.

## Experiment 9b
### Aim
Write a program to implement LRU-approximation page replacement algorithm.

### Algorithm
1. Define a 'Page' structure to represent a page, which includes a page ID and a boolean flag ('referenced') to indicate whether the page has been referenced.
2. Implement a function 'initializePage()' to initialize a page with a given page ID and set the referenced flag to false.
3. Implement a function 'findVictim()' to find the victim page using LRU-Approximation. It selects the page with the least recently referenced bit as the victim.
4. Implement a function 'lruApproximationPageReplacement()' to perform LRU-Approximation page replacement:
    a. Initialize an array of pages ('frames') to represent the frames in memory, initially set to empty pages.
    b. Iterate through each page reference in the page reference string.
    c. For each page reference:
        i. Check if the page is already present in one of the frames. If it is, set the referenced bit for that page and continue to the next page reference.
        ii. If the page is not present in any frame, find a victim page using the 'findVictim()' function and replace it with the current page.
        iii. Print the current state of frames along with the page fault indication.
    d. After processing all page references, print the total number of page faults.
5. In the 'main()' function, define a page reference string and call the 'lruApproximationPageReplacement()' function to perform LRU-Approximation page replacement.

## Experiment 9c
### Aim
Write a program to implement FIFO page replacement algorithm.

### Algorithm
1. Define a function 'findOldest()' to find the index of the oldest page in memory by iterating through the frames and finding the index of the page with the lowest value.
2. Implement a function 'fifoPageReplacement()' to perform FIFO page replacement:
    a. Initialize an array of frames ('frames') to represent the frames in memory, initially set to -1 to indicate empty frames.
    b. Initialize variables to track page faults and the index of the oldest page.
    c. Iterate through each page reference in the page reference string.
    d. For each page reference:
        i. Check if the page is already present in one of the frames. If it is, continue to the next page reference.
        ii. If the page is not present in any frame, replace the oldest page in memory with the current page and update the oldest index.
        iii. Print the current state of frames along with the page fault indication.
    e. After processing all page references, print the total number of page faults.
3. In the 'main()' function, define a page reference string and call the 'fifoPageReplacement()' function to perform FIFO page replacement.

## Experiment 9d
### Aim
Write a program to implement optimal page replacement algorithm.

### Algorithm
1. Define a function 'findOptimal()' to find the page that will not be used for the longest period of time in the future by iterating through the remaining page references and finding the farthest reference for each page in the frames.
2. Implement a function 'optimalPageReplacement()' to perform Optimal page replacement:
    a. Initialize an array of frames ('frames') to represent the frames in memory, initially set to -1 to indicate empty frames.
    b. Initialize variables to track page faults.
    c. Iterate through each page reference in the page reference string.
    d. For each page reference:
        i. Check if the page is already present in one of the frames. If it is, continue to the next page reference.
        ii. If the page is not present in any frame, replace the page with the optimal choice based on future references.
        iii. Print the current state of frames along with the page fault indication.
    e. After processing all page references, print the total number of page faults.
3. In the 'main()' function, define a page reference string and call the 'optimalPageReplacement()' function to perform Optimal page replacement.
