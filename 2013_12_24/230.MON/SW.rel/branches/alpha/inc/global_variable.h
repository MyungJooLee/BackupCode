#ifndef __INC_GLOBAL_VARIABLE_H__
#define __INC_GLOBAL_VARIABLE_H__

//////////////////////////////////////////////////////
// Include Section									//
//////////////////////////////////////////////////////
#include "types.h"
#include "define.h"
#include "structure.h"
#include "scheduler.h"
#include "uart_quintet.h"


#ifdef __cplusplus
extern "C" {
#endif


//////////////////////////////////////////////////////
// Struct Define Section							//
//////////////////////////////////////////////////////


//////////////////////////////////////////////////////
// Function	Pre-Define Section						//
//////////////////////////////////////////////////////


//////////////////////////////////////////////////////
// Global Variable	Pre-Define Section				//
//////////////////////////////////////////////////////

// For Use Global Setting Information
extern const MON_FLASH_DATA_TYPE 			g_stMONCalData;
extern MON_DATA_TYPE 						g_stMONData;
extern MON_LOCAL_DATA_TYPE					g_stMONLocalData;
extern const PCB_REVISION_TABLE_DATA_TYPE	g_PCBRevisionTable[PCB_REVISION_TABLE_SIZE];

// For Use Scheduler Timer
extern volatile int32_t						g_iSchedulerTimerCount;

// For Other Unit's FU.
extern BOOL									g_bOtherUnitFU;

// For MON's FU.
extern void (*const fpFirmwareUpgrade)();


// For Debug Data
extern uint8_t g_sDebugReceiveDataNode[UART_RECEIVE_BUFFERSIZE];
extern Queue_Structure g_stDebugRecieveQueue;


#ifdef __cplusplus
}
#endif

#endif	/* __INC_GLOBAL_VARIABLE_H__ */
