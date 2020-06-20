#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "Timeout.h"

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
    JUMP,
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
//state jump eklemek gerekiyor buraya
typedef struct
{
    StateFunction_type funk;
    StateType StateInfo;
    int TimeoutNumber;
    //uint8_t JumpUpState;
    uint8_t JumpDownState;
} StateMachineType;

typedef struct
{
    uint32_t nextStateAvaible : 1;
    uint32_t timeout;
    ALL_SCENARIO_STATE upState;
    uint8_t downState;
} StateControl_t;

/**
 * @brief 
 * 
 */
static void StateMachine(void);

/**
 * @brief 
 * 
 */
void One_Ms_Task(void);

