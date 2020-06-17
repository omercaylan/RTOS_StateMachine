#include <stdint.h>
#include <stdlib.h>
#include "Timeout.h"
#include "stdbool.h"

static int timeoutParameter = 0;
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
        timeoutParameter = true;
    }
    else
    {
        timeoutParameter--;
        timeoutParameter = false;
    }
}