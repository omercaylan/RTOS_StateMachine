/**
 * @file StateMachine.c
 * @author Ömer Çaylan (omer-ceylan17@hotmail.com)
 * @brief state machine feature 
 * ! Timeout
 * ! Jump
 * ! State control
 * ! Clear structure open to development
 * @version 0.1
 * @date 2020-06-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "StateMachine.h"
//TODO State machine create
//TODO USE Thread
//TODO Use clock
//TODO Check all size
//TODO fix header file

static uint32_t timeoutConter = 0;
static bool isTimeoutEnable = false;
static StateFunction_type runningState;

static StateControl_t stateControl = {
    .nextStateAvaible = true,
    .timeout = 0,
    .upState = 0,
    .downState = 0};

State Sm_StateA(void)
{
    printf("State A");
    return JUMP;
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
     {Sm_StateA, STATE_A, 10, 2},
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

static void StateMachine(void)
{
    if (stateControl.nextStateAvaible == true)
    {
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
        if (isTimeoutOccur() == true)
        {
            exit(1);
            stateControl.nextStateAvaible = true;
            stateControl.upState = 0;
            stateControl.downState = 0;
        }
    }

    if (stateReturn == SUCCES)
    {
        (void)printf("--%d", StateList[stateControl.upState][stateControl.downState].StateInfo);
        (void)printf("--%d", StateList[stateControl.upState][stateControl.downState].JumpDownState);
        (void)printf("--%d\n", StateList[stateControl.upState][stateControl.downState].TimeoutNumber);

        stateControl.downState++;
        stateControl.nextStateAvaible = true;

        if (StateList[stateControl.upState][stateControl.downState].funk == NULL)
        {
            stateControl.upState = IDLE_STETA;
            stateControl.downState = 0;
        }
    }
    else if (stateReturn == JUMP)
    {
        stateControl.downState = StateList[stateControl.upState][stateControl.downState].JumpDownState;
        stateControl.nextStateAvaible = true;
    }
    else
    {
        /* code */
        //logging system will be added 
    }
};

void One_Ms_Task(void)
{
    //Tasklarin kac saniye calisgini burada control et
    StateMachine();
    //------------------------
}

int main()
{
    (void)printf("stateControl downState=%d\n", stateControl.downState);
    (void)printf("stateControl upState=%d\n", stateControl.upState);
    (void)printf("stateControl timeout=%d\n", stateControl.timeout);
    (void)printf("stateControl nextStateAvaible=%d\n", stateControl.nextStateAvaible);
    (void)printf("\n-----------------------------------\n");
    for (int i = 0; i < 20; i++)
    {
        One_Ms_Task();
    }
    return 0;
}
