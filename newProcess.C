#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
int newProcess(const char *filename) {
    pid_t pid;
    int status;
    char *newargv[] = {(char *) filename, NULL }; // new argument array
    char *newenviron[] = { NULL }; // new enviroment variable

    pid = fork();

    if (pid < 0) {
        perror("fork error");
        exit(-1);
    } else if (pid == 0) {
        //child
        status = execve(filename,newargv, newenviron);
        perror("exe error");
        exit(1);
    } else {
        //parent
        if(waitpid(pid, &status, 0) < 0) {
            perror("waitpid error");
            exit(1);
        }
    }
}
