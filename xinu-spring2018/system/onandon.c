#include <xinu.h>
void onandon() {
    while(TRUE){
    putc(CONSOLE, 'x');
    sleep(2);}
}
