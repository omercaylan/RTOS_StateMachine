#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "Timeout.h"
#include "stdbool.h"

uint32_t timeoutParameter = 0;
static bool timeutOccur = false;

int setTimeout(int timeout)
{
    timeoutParameter = timeout;
}

int isTimeoutOccur()
{
    return timeutOccur;
}

int checkTime()
{
    if (timeoutParameter <= 0)
    {
        timeutOccur = true;
    }
    else
    {

        timeoutParameter--;
        timeutOccur = false;
    }
}