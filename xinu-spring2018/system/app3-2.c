#include <xinu.h>
int main(int argc, char * argv[]) {
    if (argc < 2) {
        printf("%s\n", "arguement error");
    } else {
        newProcess(argv[1]);
    }
}
