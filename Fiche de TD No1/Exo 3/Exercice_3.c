#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 50

int main(){
    int fd[2];
    pid_t pid;

    //creation of the pipe
    if (pipe(fd) < 0){
        perror("pipe");
        return 1;
    }

    //child process creation failed
    pid = fork();
    if (pid < 0){
        perror("fork");
        return 1;
    }
    //creation of the child process
    else if(pid == 0){
        close(fd[1]); //the write extreme end is closed to the child process

        char received[BUFFER_SIZE];
        ssize_t bytes_read = read(fd[0], received, sizeof(received));
        if (bytes_read < 0){
            perror("read");
            return 1;
        }
        printf("Hello 3GI, this is the value: %s\n", received);
        close(fd[0]);
    }
    else{
        close(fd[0]); //the read extreme end is closed to the parent process

        char sent[BUFFER_SIZE];
        printf("Laisser un message(max = 20): ");
        fgets(sent,sizeof(sent),stdin);
        ssize_t bytes_written = write(fd[1], sent, sizeof(sent));
        if (bytes_written < 0){
            perror("write");
            return 1;
        }
        close(fd[1]);
        wait(NULL); //wait for the child process to finish executing
    }
    return 0;
}

