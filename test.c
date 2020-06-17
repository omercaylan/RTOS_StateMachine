#include <stdlib.h>
#include <stdio.h>
typedef enum
{
    FAILED,
    SUCCES,
    RESTART,
    ERROR_CODE_ONE,
    ERROR_CODE_TWO,
    ERROR_TIMEOUT,
    ERROR_NUMBER_OF_RERUNS
} State;

typedef State (*StateFunction_type)();

int main()
{
    StateFunction_type fonk = NULL;
    if (fonk == NULL)
        printf("NULLL\n");
    return 0;
}