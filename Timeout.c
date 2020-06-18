/**
 * @file Timeout.c
 * @author Ömer Çaylan (omer-ceylan17@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-06-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */


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

int isTimeoutOccur(void)
{
    return timeutOccur;
}

int checkTime(void)
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