/**
 * @file StateMachine.c
 * @author Ömer Çaylan (omer-ceylan17@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-06-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "Timeout.h"
//TODO: State machine create
//TODO: USE Thread
//TODO: Use clock

typedef enum
{
    IDLE_STETA,      //waiting and next state transion here
    SAFETY_STATE,    //all component init and ram check rom check here
    MAIN_STATE,      //running main state
    DIAGNOSTIC_STATE //diag state
} ALL_SCENARIO_STATE;

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

typedef enum
{
    STATE_A,
    STATE_B,
    STATE_C,
    STATE_D,
    MAX_STETE
} StateType;

typedef State (*StateFunction_type)(void);
typedef struct
{
    StateFunction_type funk;
    StateType StateInfo;
    int TimeoutNumber;
    uint8_t RerunsCount;
} StateMachineType;

typedef struct
{
    uint32_t nextStateAvaible : 1;
    uint32_t timeout;
    ALL_SCENARIO_STATE upState;
    uint8_t downState;
} StateControl_t;

State Sm_StateA(void)
{
    printf("State A");
    return FAILED;
};
State Sm_StateB(void)
{
    printf("State B");
    return SUCCES;
};
State Sm_StateC(void)
{
    printf("State C");
    return SUCCES;
};
State Sm_StateD(void)
{
    printf("State D");
    return SUCCES;
};
State Sm_StateE(void)
{
    printf("State E");
    //setRestartDownState(STATE_A);
    return SUCCES;
};
State Sm_StateF(void)
{
    printf("State F");
    //setRestartDownState(STATE_A);
    return SUCCES;
};
State Sm_StateG(void)
{
    printf("State G");
    //setRestartDownState(STATE_A);
    return SUCCES;
};
State Sm_StateH(void)
{
    printf("State H");
    //setRestartDownState(STATE_A);
    return SUCCES;
};
StateMachineType StateList[][5] = {
    {//First sTate
     {Sm_StateA, STATE_A, 10, 1},
     {Sm_StateB, STATE_B, 0, 2},
     {Sm_StateC, STATE_C, 0, 3},
     {Sm_StateD, STATE_D, 10, 4},
     {NULL, STATE_D, 40, 4}

    },
    {//Second State
     {Sm_StateE, STATE_A, 50, 5},
     {Sm_StateF, STATE_B, 60, 6},
     {Sm_StateG, STATE_C, 70, 7},
     {Sm_StateH, STATE_D, 80, 8},
     {NULL, STATE_D, 40, 4}}

};

StateControl_t stateControl = {true, 0, 0, 0};
StateFunction_type runningState;
int timeoutConter = 0;
bool isTimeoutEnable = false;

static void StateMachine(void)
{

    if (stateControl.nextStateAvaible == true)
    {
        printf("\n-------------------next state avaible \n");
        stateControl.nextStateAvaible = false;
        runningState = StateList[stateControl.upState][stateControl.downState].funk;
        timeoutConter = StateList[stateControl.upState][stateControl.downState].TimeoutNumber;
        if (timeoutConter > 0)
        {
            (void)setTimeout(timeoutConter);
            isTimeoutEnable = true;
        }
        else
        {
            isTimeoutEnable = false;
        }
    }

    State stateReturn = runningState();

    if (isTimeoutEnable == true)
    {
        (void)checkTime();
        if (isTimeoutOccur() == 1)
        {
            exit(1);
            stateControl.nextStateAvaible = true;
            stateControl.upState = 0;
            stateControl.downState = 0;
        }
    }

    if (stateReturn == SUCCES)
    {
        printf("--%d", StateList[stateControl.upState][stateControl.downState].StateInfo);
        printf("--%d", StateList[stateControl.upState][stateControl.downState].RerunsCount);
        printf("--%d\n", StateList[stateControl.upState][stateControl.downState].TimeoutNumber);
        stateControl.downState++;

        stateControl.nextStateAvaible = true;

        if (StateList[stateControl.upState][stateControl.downState].funk == NULL)
        {
            stateControl.upState = IDLE_STETA;
            stateControl.downState = 0;
        }
    }
    else if (stateReturn == RESTART)
    {
        // stateControl.downState = getRestartDownState();
    }
    else
    {
        /* code */
    }
};

void One_Ms_Task()
{
    //Tasklarin kac saniye calisgini burada control et
    StateMachine();

    //------------------------
}
int main()
{
    printf("stateControl downState=%d\n", stateControl.downState);
    printf("stateControl upState=%d\n", stateControl.upState);
    printf("stateControl timeout=%d\n", stateControl.timeout);
    printf("stateControl nextStateAvaible=%d\n", stateControl.nextStateAvaible);
    printf("\n-----------------------------------\n");
    for (int i = 0; i < 20; i++)
    {
        One_Ms_Task();
    }

    return 0;
}
