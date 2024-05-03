#include <iostream>
#include <unistd.h>
#include <cstdlib>

#define READ_END 0
#define WRITE_END 1

using namespace std;

int main()
{
    int pipefd[2];
    char buffer[100];

    if (pipe(pipefd) == -1)
    {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        close(pipefd[WRITE_END]);
        read(pipefd[READ_END], buffer, sizeof(buffer));
        cout << "Parent received message from child: " << buffer << std::endl;
        close(pipefd[READ_END]);
    }
    else
    {
        close(pipefd[READ_END]);
        write(pipefd[WRITE_END], "Hello Child!", sizeof("Hello Child!"));
        close(pipefd[WRITE_END]);
    }

    return 0;
}
