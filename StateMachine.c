#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//TODO: State machine create
//TODO: USE Thread
//TODO: Use clock

typedef enum
{
    IDLE_STETA,
    SAFETY_STATE,
    MAIN_STATE,
    DIAGNOSTIC_STATE
} ALL_SCENARIO_STATE;

typedef enum
{
    FAILED,
    SUCCES,
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

typedef struct
{
    State (*funk)(void);
    StateType StateInfo;
    int TimeoutNumber;
    uint8_t RerunsCount;
} StateMachineType;

State Sm_StateA(void) { printf("State A\n"); };
State Sm_StateB(void) { printf("State B\n"); };
State Sm_StateC(void) { printf("State C\n"); };
State Sm_StateD(void) { printf("State D\n"); };

StateMachineType StateList[][4] = {
    {//First sTate
     {Sm_StateA, STATE_A, 10, 1},
     {Sm_StateB, STATE_B, 20, 2},
     {Sm_StateC, STATE_C, 30, 3},
     {Sm_StateD, STATE_D, 40, 4}},
    {//Second State
     {Sm_StateA, STATE_A, 50, 5},
     {Sm_StateB, STATE_B, 60, 6},
     {Sm_StateC, STATE_C, 70, 7},
     {Sm_StateD, STATE_D, 80, 8}}

};

void StateMachine()
{
    StateList[0][0].funk();
    printf("%d\n", StateList[0][0].StateInfo);
    printf("%d\n", StateList[0][0].TimeoutNumber);
    printf("%d\n", StateList[1][1].RerunsCount);
};

void CheckTimeOut() { printf("Timeout \n"); };

void One_Ms_Task()
{
    StateMachine();
    CheckTimeOut();
}
int main()
{
    One_Ms_Task();
    return 0;
}
