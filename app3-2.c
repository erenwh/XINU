#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int newProcess(const char *filename);

int main(int argc, char * argv[]) {
    if (argc < 2) {
        printf("%s\n", "arguement error");
    } else {
        newProcess(argv[1]);
    }
}
