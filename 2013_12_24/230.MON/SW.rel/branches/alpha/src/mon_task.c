#include "mon_task.h"


//////////////////////////////////////////////////////
// Global Variable Define Section					//
//////////////////////////////////////////////////////




//////////////////////////////////////////////////////
// Function	Define Section							//
//////////////////////////////////////////////////////


///////////// TASK Start /////////////////////////////
void checkDCDC(void)
{

}
void checkFPGA(void)
{

}

void processCANMessage(void)
{
	int i=0;
	CAN_DataNode stRecievedData;
	QueueErrorType eQueueError;
	int (* fpCAN_RECIEVE)(CAN_DataNode tCANMessage);
	//__DEBUG("Receive CAN Called\r\n\n");

	for(i=0; i<PROCESS_CAN_MAX_COUNT; i++)
	{
		eQueueError = getFront_Queue(&g_stCANRecieveQueue, (void*)&stRecievedData);
		if(eQueueError == QueueNormal)
		{
			if((stRecievedData.uUnitID & CAN_UNITID_MASK) == CAN_ALL_OPCODE_UNITID_MASK_RESULT && stRecievedData.uOpcode < CAN_ALL_OPCODE_COUNT)
				fpCAN_RECIEVE = fpCAN_ALL_RECIEVE_TABLE[stRecievedData.uOpcode];
			else if(stRecievedData.uOpcode < CAN_NORMAL_OPCODE_START_INDEX && stRecievedData.uOpcode < CAN_COMMON_OPCODE_COUNT)
				fpCAN_RECIEVE = fpCAN_COMMON_RECIEVE_TABLE[stRecievedData.uOpcode];
			else if((stRecievedData.uOpcode- CAN_NORMAL_OPCODE_START_INDEX) < CAN_NORMAL_OPCODE_COUNT)
				fpCAN_RECIEVE = fpCAN_NORMAL_RECIEVE_TABLE[stRecievedData.uOpcode - CAN_NORMAL_OPCODE_START_INDEX];
			else
			{
				__DEBUG("unKnown CAN OP - %d/%5d \r\n\n", stRecievedData.uUnitID, stRecievedData.uOpcode);
				return;
			}

			if(fpCAN_RECIEVE != NULL)
				fpCAN_RECIEVE(stRecievedData);
		}
		else if(eQueueError == QueueError)
		{
			__DEBUG("CAN Receive Queue Error Code : %03d\r\n", eQueueError);
		}
	}
}
void processDebugMessage(void)
{

}
void sendCANMessage(void)
{
	int i=0;
	CanErrorType eCANError = CANNormal;

	//__DEBUG("Send Can Called\r\n\n");
	for(i=0; i<SEND_CAN_MAX_COUNT; i++)
	{
		eCANError = CANNormal;
		if(g_bOtherUnitFU == TRUE)
			continue;	// Waiting For Other Unit's FU.

		eCANError = sendCANData_fromQueue(CAN_PORT, &g_stCANSendQueue);
		if(eCANError != CANNormal)
		{

			if(eCANError != CANSendFail_QueueEmpty && eCANError != CANSendFail_MailBoxFull)
				__DEBUG("CAN Send Error Code : %03d\r\n", eCANError);
		}
	}
}


///////////// Function Start /////////////////////////
inline void writeBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
	if (BitVal != Bit_RESET)
		GPIOx->BSRRL = GPIO_Pin;
	else
		GPIOx->BSRRH = GPIO_Pin;
}
inline void setBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIOx->BSRRL = GPIO_Pin;
}
inline void resetBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIOx->BSRRH = GPIO_Pin;
}
inline void writeFPGA(SPI_TypeDef* SPIx, uint16_t uData, uint16_t uAddress)
{
	commSPI(SPIx, FPGA_ADDRESS_FRAME | FPGA_ADDRESS_WRTIE | uAddress);
	commSPI(SPIx, FPGA_DATA_FRAME | FPGA_ADDRESS_WRTIE | uData);
}
inline uint16_t readFPGA(SPI_TypeDef* SPIx, uint16_t uSendData)
{
	uint16_t uReceiveData = 0;
	uReceiveData = commSPI(SPIx, FPGA_ADDRESS_FRAME | FPGA_ADDRESS_READ | uSendData);
	uReceiveData = commSPI(SPIx, FPGA_DATA_FRAME | FPGA_ADDRESS_READ | 0);
	return uReceiveData;
}
void readFPGAnSendCAN(SPI_TypeDef* SPIx, uint16_t uSendData, uint16_t* uDestData, uint16_t uFPGA_CAN_SEND_OP)
{
	CAN_DataNode stMessage = {{0}, g_stMONLocalData.uCANSendID, 0, 0};
	uint16_t uReceiveData = 0;

	uReceiveData = readFPGA(SPIx, uSendData);
	if(uReceiveData != *uDestData)
	{
		*uDestData = uReceiveData;
		stMessage.uOpcode = uFPGA_CAN_SEND_OP;
		stMessage.uLength = 2;
		*((uint16_t*)(&stMessage.uData[0])) = uReceiveData;
		addRear_Queue(&g_stCANSendQueue, (void *)&stMessage);
		__DEBUG("Send to CAN OP(%u)/Data(%u)\r\n\n", stMessage.uOpcode, uReceiveData);
	}
}
// Non-Public Function
static inline uint16_t sendnrecieveDataSPI(SPI_TypeDef* SPIx, uint16_t uData)
{
	SPI_I2S_SendData(SPIx, uData);
	// Receive Data
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPIx);
}
uint16_t commSPI(SPI_TypeDef* SPIx, uint16_t uData)
{
	uint16_t uRecieveData = 0;

	// Send Data
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);

	resetBit(FPGA_NSS_PORT, FPGA_NSS_PIN);
	uRecieveData = sendnrecieveDataSPI(SPIx, uData);
	setBit(FPGA_NSS_PORT, FPGA_NSS_PIN);

	return uRecieveData;
}
inline void sendLiveMessagetoSCU(LIVE_MODE_t eMode)
{
	CAN_DataNode stMessage = {{0}, g_stMONLocalData.uCANSendID, 0, 0};

	// Send To CAN
	if(eMode == LIVEMODE_NORMAL)
	{	// Running State
		stMessage.uOpcode = CAN_S_COM_OP_NORMAL_STATUS;
		stMessage.uLength = 0;
		stMessage.uData[0] = 0;
	}
	else if(eMode == LIVEMODE_STARTUP)
	{	// Stratup
		stMessage.uOpcode = CAN_S_COM_OP_NORMAL_STATUS_DATA_REQUEST;
		stMessage.uLength = 4;
		stMessage.uData[0] = g_stMONCalData.stSW_Version.uMajor;
		stMessage.uData[1] = g_stMONCalData.stSW_Version.uMinor;
		*((uint16_t*)(&stMessage.uData[2])) = g_stMONCalData.stSW_Version.uRelease;
	}
	addRear_Queue(&g_stCANSendQueue, (void *)&stMessage);
}
inline void sendPulsetoWatchdogIC(LIVE_MODE_t eMode)
{
	IWDG_ReloadCounter();
	//delay_us(1);											// 1us Delay (at least 20ns)
	sendLiveMessagetoSCU(eMode);							// Send CAN Message of Unit Live Information.
}
inline void sendSWVersion()
{
	CAN_DataNode stMessage = {{0}, g_stMONLocalData.uCANSendID, 0, 0};
	stMessage.uOpcode = CAN_S_COM_OP_SW_VERSION;
	stMessage.uLength = 4;
	stMessage.uData[0] = g_stMONCalData.stSW_Version.uMajor;
	stMessage.uData[1] = g_stMONCalData.stSW_Version.uMinor;
	*((uint16_t*)(&stMessage.uData[2])) = g_stMONCalData.stSW_Version.uRelease;
	addRear_Queue(&g_stCANSendQueue, (void *)&stMessage);
}
inline uint8_t getBPUPosition(void)
{
	return (MON_SHELF_POS_PORT->ODR & MON_SHELF_POS_PIN); // ??? Real-Pin Check
}
inline uint8_t getConfigBit(void)
{
	return (MON_CONFIG_PORT->ODR & MON_CONFIG_PIN) >> 6;	// ??? Real-Pin Check
}
inline uint8_t getCANUnitID(void)
{
	return g_stMONLocalData.uCANSendID;
}
inline void setCANUnitID(uint8_t uBPUPosition)
{
	if(uBPUPosition == MON_1_SHELF_POS_BIT)
	{
		g_stMONLocalData.uCANSendID = CAN_MON_1_SEND_UNITID;
	}
	else if(uBPUPosition == MON_2_SHELF_POS_BIT)
	{
		g_stMONLocalData.uCANSendID = CAN_MON_2_SEND_UNITID;
	}
	else
	{
		g_stMONLocalData.uCANSendID = CAN_MON_STB_SEND_UNITID;
	}
}


