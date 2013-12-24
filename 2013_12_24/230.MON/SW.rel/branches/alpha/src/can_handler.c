#include "can_handler.h"


//////////////////////////////////////////////////////
// Global Variable Define Section					//
//////////////////////////////////////////////////////
CAN_DataNode g_staCANSendDataNodes[CAN_SEND_BUFFERSIZE];
CAN_DataNode g_staCANRecieveDataNodes[CAN_RECEIVE_BUFFERSIZE];

Queue_Structure g_stCANSendQueue = 		 { 	g_staCANSendDataNodes,
												sizeof(CAN_DataNode),
												0,
												0,
												CAN_SEND_BUFFERSIZE,
												copyCANQueueNode
										 };
Queue_Structure g_stCANRecieveQueue = 	 { 	g_staCANRecieveDataNodes,
												sizeof(CAN_DataNode),
												0,
												0,
												CAN_RECEIVE_BUFFERSIZE,
												copyCANQueueNode
										 };



int (*const fpCAN_ALL_RECIEVE_TABLE[CAN_ALL_OPCODE_COUNT])(CAN_DataNode stCANMessage)
	= {
			NULL,								// OPCODE 0x000;
			handleCAN_ALL_BootComplete,			// OPCODE 0x001;
			handleCAN_ALL_FWUStart,				// OPCODE 0x002;
			handleCAN_ALL_FWUEnd,				// OPCODE 0x003;
			handleCAN_ALL_UnitStatus,			// OPCODE 0x004;
			handleCAN_ALL_UnitStatus_NoAck,		// OPCODE 0x005;
			handleCAN_ALL_getSWVersion,			// OPCODE 0x006;
	};
int (*const fpCAN_COMMON_RECIEVE_TABLE[CAN_COMMON_OPCODE_COUNT])(CAN_DataNode stCANMessage)
	= {
			NULL,								// OPCODE 0x000;
			handleCAN_COM_RequestFWUReady,		// OPCODE 0x001;
			handleCAN_COM_getSWVersion,			// OPCODE 0x002;
			NULL,								// OPCODE 0x003;
			handleCAN_COM_goMCUReset,			// OPCODE 0x004;
			handleCAN_COM_getHWVersion,			// OPCODE 0x005;
			handleCAN_COM_getMCUUniqueID,		// OPCODE 0x006;
	};
int (*const fpCAN_NORMAL_RECIEVE_TABLE[CAN_NORMAL_OPCODE_COUNT])(CAN_DataNode stCANMessage)
	= {
			NULL,								// OPCODE 0x400;
			NULL,								// OPCODE 0x401;
			NULL,								// OPCODE 0x402;
			NULL,								// OPCODE 0x403;
			NULL,								// OPCODE 0x404;
			NULL,								// OPCODE 0x405;
			NULL,								// OPCODE 0x406;
			NULL,								// OPCODE 0x407;
			NULL,								// OPCODE 0x408;
			NULL,								// OPCODE 0x409;
			NULL,								// OPCODE 0x40A;
			NULL,								// OPCODE 0x40B;
			NULL,								// OPCODE 0x40C;
			NULL,								// OPCODE 0x40D;
			NULL,								// OPCODE 0x40E;
			NULL,								// OPCODE 0x40F;
			NULL,								// OPCODE 0x410;
			NULL,								// OPCODE 0x411;
			NULL,								// OPCODE 0x412;
			NULL,								// OPCODE 0x413;
			NULL,								// OPCODE 0x414;
			NULL,								// OPCODE 0x415;
			NULL,								// OPCODE 0x416;
			NULL,								// OPCODE 0x417;
			NULL,								// OPCODE 0x418;
			NULL,								// OPCODE 0x419;
			NULL,								// OPCODE 0x41A;
			NULL,								// OPCODE 0x41B;
			NULL,								// OPCODE 0x41C;
			NULL,								// OPCODE 0x41D;
			NULL,								// OPCODE 0x41E;
			NULL,								// OPCODE 0x41F;
			NULL,								// OPCODE 0x420;
			NULL,								// OPCODE 0x421;
			NULL,								// OPCODE 0x422;
			NULL,								// OPCODE 0x423;
			NULL,								// OPCODE 0x424;
			NULL,								// OPCODE 0x425;
			NULL								// OPCODE 0x426;
	};

//////////////////////////////////////////////////////
// Can Receive Handler Function	Define Section		//
//////////////////////////////////////////////////////
int handleCAN_ALL_BootComplete(CAN_DataNode stCANMessage)
{
	__DEBUG("Receive Boot Complete - But No Job\r\n\n");
	// Currently No Job
	// or
	// Send All Setting Value Send Message
		// TBD
	return 0;
}
int handleCAN_ALL_FWUStart(CAN_DataNode stCANMessage)
{
	__DEBUG("Receive FU Start\r\n\n");
	g_bOtherUnitFU = TRUE;
	return 0;
}
int handleCAN_ALL_FWUEnd(CAN_DataNode stCANMessage)
{
	__DEBUG("Receive FU End\r\n\n");
	g_bOtherUnitFU = FALSE;
	return 0;
}
int handleCAN_ALL_UnitStatus(CAN_DataNode stCANMessage)
{
	__DEBUG("Receive ALL Unit Status\r\n\n");
	// CAN Message Process
	if(stCANMessage.uLength < 3)
	{
		// Must Exception Handling
		__DEBUG("Unit Status RECEIVE ERROR\r\n\n");
		return -1;
	}
	g_stMONLocalData.uOtherUnitPDStatus = *((uint16_t*)&stCANMessage.uData[0]);
	g_stMONLocalData.uOtherUnitFaultStatus = stCANMessage.uData[2];

	sendLiveMessagetoSCU(LIVEMODE_NORMAL);
	return 0;
}
int handleCAN_ALL_UnitStatus_NoAck(CAN_DataNode stCANMessage)
{
	__DEBUG("Receive ALL Unit Status(No ACK)\r\n\n");
	// CAN Message Process
	if(stCANMessage.uLength < 3)
	{
		// Must Exception Handling
		__DEBUG("Unit Status(No ACK) RECEIVE ERROR\r\n\n");
		return -1;
	}
	g_stMONLocalData.uOtherUnitPDStatus = *((uint16_t*)&stCANMessage.uData[0]);
	g_stMONLocalData.uOtherUnitFaultStatus = stCANMessage.uData[2];

	return 0;
}
int handleCAN_ALL_getSWVersion(CAN_DataNode stCANMessage)
{
	__DEBUG("Receive Get SW Version(ALL)\r\n\n");
	sendSWVersion();
	return 0;
}

int handleCAN_COM_RequestFWUReady(CAN_DataNode stCANMessage)
{
	__DEBUG("Receive request FU ready\r\n\n");
	fpFirmwareUpgrade();
	return 0;
}
int handleCAN_COM_getSWVersion(CAN_DataNode stCANMessage)
{
	__DEBUG("Receive Get SW version(COM)\r\n\n");
	sendSWVersion();
	return 0;
}
int handleCAN_COM_goMCUReset(CAN_DataNode stCANMessage)
{
	__DEBUG("Now MCU Reset!\r\n\n");

	//Keep priority group unchanged
	SCB->AIRCR  = ((0x5FA << SCB_AIRCR_VECTKEY_Pos) | (SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) | SCB_AIRCR_SYSRESETREQ_Msk);
	//Ensure completion of memory access
	__DSB();
	//Waiting for reset
	while(1);

	return 0;
}
int handleCAN_COM_getHWVersion(CAN_DataNode stCANMessage)
{
	__DEBUG("Receive get H/W Version - But No Job \r\n\n");
	// Currently No Job
	return 0;
}
int handleCAN_COM_getMCUUniqueID(CAN_DataNode stCANMessage)
{
	CAN_DataNode stMessage = {{0}, g_stMONLocalData.uCANSendID, 0, 0};

	__DEBUG("Receive get MCU Unique ID\r\n\n");
	uint8_t *uID = (uint8_t *)0x1FFFF7E8;

	// CAN Message Send - Low ID
	stMessage.uOpcode = CAN_S_COM_OP_MCU_UNIQUE_ID;
	stMessage.uLength = 7;
	stMessage.uData[0] = LOW;
	stMessage.uData[1] = uID[0];
	stMessage.uData[2] = uID[1];
	stMessage.uData[3] = uID[2];
	stMessage.uData[4] = uID[3];
	stMessage.uData[5] = uID[4];
	stMessage.uData[6] = uID[5];
	addRear_Queue(&g_stCANSendQueue, (void *)&stMessage);

	// CAN Message Send - High ID
	stMessage.uOpcode = CAN_S_COM_OP_MCU_UNIQUE_ID;
	stMessage.uLength = 5;
	stMessage.uData[0] = LOW;
	stMessage.uData[1] = uID[6];
	stMessage.uData[2] = uID[7];
	stMessage.uData[3] = uID[8];
	stMessage.uData[4] = uID[9];
	stMessage.uData[5] = uID[10];
	stMessage.uData[6] = uID[11];
	addRear_Queue(&g_stCANSendQueue, (void *)&stMessage);

	return 0;
}




