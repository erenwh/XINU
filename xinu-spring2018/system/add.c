#include <stdio.h>
#include <stdint.h>
int main(int argc, char *argv[]) {
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int result;
    result = a - b;
    printf("%i - %i = %i\n", a,b,result);
}
