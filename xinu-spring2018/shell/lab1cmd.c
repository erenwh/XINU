/**
  * This is a added feature to my XINU
  * It takes two integers and add them together
  * The command has been assign into the cmd table using keywork "add"
  * TO use it, the correct format should be:"
  * add digitValue1 digitValue2"
  * Any other input then digits will get prompt of the character that is not a digit,
  * and force to terminate the program.
  * Han Wang @ Purdue
  *
  **/
#include <xinu.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
shellcmd lab1cmd(int argc, char *argv[]) {
    // check if argument number is correct
    if (argc != 3) {
        printf("please use \"add val1 val2 \"\n");
        return -1;
    }

    // bool for value check
    int alegit = 0;

    // check if argvs are digits
    // argv[1]
    int size = strlen(argv[1]);
    for (int i = 0; i < size ; i++) {
        if (isdigit(argv[1][i]))
        {
            // if char is a digit
            alegit = 1;
            continue;
        }
        else
        {
            // if char is not a digit, mark it, print error and change bool break out
            printf("%c is not a digit, argv[1] check fail\n", argv[1][i]);
            alegit = 0;
            break;
            return -1;
        }
    }

    // bool for value check
    int blegit = 0;

    // check if argvs are digits
    // argv[2]
    size = strlen(argv[2]);
    for (int i = 0; i < size ; i++) {
        if (isdigit(argv[2][i]))
        {
            // if char is a digit
            blegit = 1;
            continue;
        }
        else
        {
            // if char is not a digit, mark it, print error and change bool break out
            printf("%c is not a digit, argv[2] check fail\n", argv[2][i]);
            blegit = 0;
            break;
            return -1;
        }
    }
    //if both legit, add!
    if (alegit == 1 && blegit == 1) {
        int32 a = atoi(argv[1]);
        int32 b = atoi(argv[2]);
        int32 result = a + b;
        printf("%d + %d = %d\n", a, b, result);
    }

    
    return 0;

}
