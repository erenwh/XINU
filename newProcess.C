#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
int newProcess(const char *filename) {
    pid_t pid;//store pid
    int status;//keep track of status of the process
    char *newargv[] = {(char *) filename, NULL }; // new argument array
    char *newenviron[] = { NULL }; // new enviroment variable

    pid = fork();//creating child process

    if (pid < 0) {//error when forking
        perror("fork error");
        exit(-1);
    } else if (pid == 0) {
        //child
        status = execve(filename,newargv, newenviron);//execute filename with newargv and NULL environ
        perror("exe error");//error check
        exit(1);
    } else {
        //parent
        if(waitpid(pid, &status, 0) < 0) {//waiting for child and determin when to kill
            perror("waitpid error");
            exit(1);
        }
    }
}
