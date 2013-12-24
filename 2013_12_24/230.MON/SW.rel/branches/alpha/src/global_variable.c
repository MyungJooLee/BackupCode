#include "global_variable.h"

// For Use Global Setting Information
const MON_FLASH_DATA_TYPE 	g_stMONCalData;
MON_DATA_TYPE 				g_stMONData;
MON_LOCAL_DATA_TYPE			g_stMONLocalData;



// For Other Unit's FU.
BOOL	g_bOtherUnitFU = FALSE;

// For MON's FU.
 void (*const fpFirmwareUpgrade)() = (void (*const)())FLASH_ADDRESS_FU_START;



// For Debug Data
uint8_t g_sDebugReceiveDataNode[UART_RECEIVE_BUFFERSIZE];

Queue_Structure g_stDebugRecieveQueue = 	 { 	g_sDebugReceiveDataNode,
												sizeof(uint8_t),
												0,
												0,
												UART_RECEIVE_BUFFERSIZE,
												copyUARTQueueNode
											 };


const PCB_REVISION_TABLE_DATA_TYPE g_PCBRevisionTable[PCB_REVISION_TABLE_SIZE] =
{
		{0, 1023, PCB_REVISION_FAULT_VALUE},		// PD
		{1024, 2048, PCB_REVISION_0_VALUE},			// REV 0
		{2049, 4096, PCB_REVISION_A_VALUE},			// REV A
};

