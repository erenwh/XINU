#include <xinu.h>

int newProcess(const char* filename) {

    pid_t pid;
    int status;
    char *newargv[] = { filename, NULL }; // new argument array
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
