#ifndef __INC_CAN_HANDLER_H__
#define __INC_CAN_HANDLER_H__

//////////////////////////////////////////////////////
// Include Section									//
//////////////////////////////////////////////////////
#include "types.h"
#include "define.h"

#include "structure.h"
#include "can_quintet.h"
#include "global_variable.h"

#include "mon_task.h"


#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////
// Define Section									//
//////////////////////////////////////////////////////

//////////////////////////////////////////////////////
// Global Variable Pre-Define Section				//
//////////////////////////////////////////////////////
extern CAN_DataNode g_staCANSendDataNodes[CAN_SEND_BUFFERSIZE];
extern CAN_DataNode g_staCANRecieveDataNodes[CAN_RECEIVE_BUFFERSIZE];

extern int (*const fpCAN_ALL_RECIEVE_TABLE[CAN_ALL_OPCODE_COUNT])(CAN_DataNode stCANMessage);
extern int (*const fpCAN_COMMON_RECIEVE_TABLE[CAN_COMMON_OPCODE_COUNT])(CAN_DataNode stCANMessage);
extern int (*const fpCAN_NORMAL_RECIEVE_TABLE[CAN_NORMAL_OPCODE_COUNT])(CAN_DataNode stCANMessage);

//////////////////////////////////////////////////////
// Struct Define Section							//
//////////////////////////////////////////////////////




//////////////////////////////////////////////////////
// Function	Pre-Define Section						//
//////////////////////////////////////////////////////
int handleCAN_ALL_BootComplete(CAN_DataNode stCANMessage);
int handleCAN_ALL_FWUStart(CAN_DataNode stCANMessage);
int handleCAN_ALL_FWUEnd(CAN_DataNode stCANMessage);
int handleCAN_ALL_UnitStatus(CAN_DataNode stCANMessage);
int handleCAN_ALL_UnitStatus_NoAck(CAN_DataNode stCANMessage);
int handleCAN_ALL_getSWVersion(CAN_DataNode stCANMessage);

int handleCAN_COM_RequestFWUReady(CAN_DataNode stCANMessage);
int handleCAN_COM_getSWVersion(CAN_DataNode stCANMessage);
int handleCAN_COM_goMCUReset(CAN_DataNode stCANMessage);
int handleCAN_COM_getHWVersion(CAN_DataNode stCANMessage);
int handleCAN_COM_getMCUUniqueID(CAN_DataNode stCANMessage);






#ifdef __cplusplus
}
#endif

#endif	/* __INC_CAN_HANDLER_H__ */
