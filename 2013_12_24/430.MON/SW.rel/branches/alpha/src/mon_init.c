/**
 ******************************************************************************
 *    @file    mon_init.c
 *    @author  mjlee@mopiens.com
 *    @version 0.01
 *    @date    2013/11/28
 *    @brief   LOC/GP MON's Chip initialize source file.
 ******************************************************************************/
/*    SVN $Id$  */
/******************************************************************************
 *                                                                            *
 *    MOPIENS, Inc. ("COMPANY") PROPRIETARY AND CONFIDENTIAL                  *
 *    ======================================================                  *
 *    COPYRIGHT (C) 2012-2013 MOPIENS, Inc.  All Rights Reserved.             *
 *                                                                            *
 *    NOTICE:  All information contained herein is, and remains the property  *
 *    of COMPANY.                                                             *
 *                                                                            *
 *    The intellectual and technical concepts contained herein are            *
 *    proprietary to COMPANY and may be covered by Korean and Foreign         *
 *    Patents, patents in process, and are protected by trade secret or       *
 *    copyright law.                                                          *
 *                                                                            *
 *    Access to the source code contained herein is hereby forbidden to       *
 *    anyone except current COMPANY employees, managers or contractors who    *
 *    have executed Confidentiality and Non-disclosure agreements explicitly  *
 *    covering such access.                                                   *
 *                                                                            *
 *    The copyright notice above does not evidence any actual or intended     *
 *    publication or disclosure of this source code, which includes           *
 *    information that is confidential and/or proprietary, and is a trade     *
 *    secret, of COMPANY.                                                     *
 *                                                                            *
 *    ANY REPRODUCTION, MODIFICATION, DISTRIBUTION, PUBLIC PERFORMANCE,       *
 *    OR PUBLIC DISPLAY OF OR THROUGH USE OF THIS SOURCE CODE WITHOUT THE     *
 *    EXPRESS WRITTEN CONSENT OF COMPANY IS STRICTLY PROHIBITED, AND IN       *
 *    VIOLATION OF APPLICABLE LAWS AND INTERNATIONAL TREATIES.                *
 *                                                                            *
 *    THE RECEIPT OR POSSESSION OF THIS SOURCE CODE AND/OR RELATED            *
 *    INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS TO REPRODUCE, DISCLOSE  *
 *    OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE, USE, OR SELL ANYTHING    *
 *    THAT IT MAY DESCRIBE, IN WHOLE OR IN PART.                              *
 *                                                                            *
 ******************************************************************************/

#include "mon_init.h"





//////////////////////////////////////////////////////
// Global Variable Define Section					//
//////////////////////////////////////////////////////





//////////////////////////////////////////////////////
// Function	Define Section							//
//////////////////////////////////////////////////////
inline void setFPU()
{
	// FPU Setting Code
	*((volatile unsigned long*)0xE000ED88) = 0xF << 20;

	/* In Assembly
	//enable fpu begin
	  __asm("  LDR.W R0, =0xE000ED88\n"
	        "  LDR R1, [R0]\n"
	        "  ORR R1, R1, #(0xF << 20)\n"
	        "  STR R1, [R0]");
	//enable fpu end
	*/
}
void initAll()
{
	//Chip Initialize
	initMCUClock();

	//RCC Setting
	initRCC();

	//NVIC Loacation Setting
	//NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00);
	//NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x00);

	//GPIO Setting
	initGPIO();
	setDefaultValueofGPIO();


	//Read BPU Position
	g_stMONLocalData.uMONMode = getConfigBit();
	g_stMONLocalData.uBPUPosition = getBPUPosition();
	setCANUnitID(g_stMONLocalData.uBPUPosition);

	//Peripheral Setting
	initPeripheral();
	__DEBUG("LOC/GP MON MCU Initialize Complete!\r\n\n");

	//First Watchdog IC Pulse Send
	sendPulsetoWatchdogIC(LIVEMODE_STARTUP);

	setFPU();
	initEtc();
}

void initEtc()
{


}
void initPeripheral()
{
	// UART init.
	initializeUART(DEBUG_PORT, DEBUG_BAUDRATE, DEBUG_IRQn, DEBUG_PRIORITY, DEBUG_SUBPRIORITY,
			DEBUG_WORDLENGTH, DEBUG_STOPBITS, DEBUG_PARITY, DEBUG_FLOWCONTROL, DEBUG_MODE);	// Debug UART(USART1)

	// ADC init.
		// Use Only 1 ADC
	//initADC();

	// DAC init.
	//initDAC();

	// CAN init.
	initCAN(CAN_PORT);

	// I2C init.
	//initI2C(TEMP_SENSOR_I2C_NO, I2C_MON_ADDRESS, TEMP_SENSOR_I2C_Speed);

	// SPI init.
	//initSPI(FPGA_SPI_NO);	// CPLD SPI

	// Timer init	
	//initTimer(TASK_SCHEDULING_TIMER_NO, TASK_SCHEDULING_TIMER_CYCLE_US, TRUE, TASK_SCHEDULING_TIMER_IRQn, TASK_SCHEDULING_TIMER_PRIORITY);
	//initTimer(DAC_TIMER_NO, DAC_TIMER_CYCLE_US, FALSE, DAC_TIMER_IRQn, DAC_TIMER_PRIORITY);
	//initTimer(IDENT_KEYING_TIMER_NO, IDENT_KEYING_TIMER_CYCLE_US, TRUE, IDENT_KEYING_TIMER_IRQn, IDENT_KEYING_TIMER_PRIORITY);

	// Timer Start
	//startTimer(DAC_TIMER_NO);
}
void initADC(ADC_TypeDef* ADCx, uint8_t ADC_Channel, FunctionalState ADC_ContinuousConvMode)
{

}
void initADC_Sampling(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint32_t ADC_DR_ADDERSS, DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_Channel, uint8_t NVIC_IRQChannel, uint16_t* pBufferAddress0, uint16_t* pBufferAddress1, uint32_t uBufferSize)
{
	ADC_InitTypeDef       ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	DMA_InitTypeDef       DMA_InitStructure;

	DMA_InitStructure.DMA_Channel = DMA_Channel;
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC_DR_ADDERSS;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)pBufferAddress0;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = uBufferSize;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMAy_Streamx, &DMA_InitStructure);
	DMA_DoubleBufferModeConfig(DMAy_Streamx, (uint32_t)pBufferAddress1, DMA_Memory_0);
	DMA_DoubleBufferModeCmd(DMAy_Streamx, ENABLE);
	DMA_Cmd(DMAy_Streamx, ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;
	  /* Configure and enable DMA interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = NVIC_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// ADC Common Init
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	//ADC Init
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADCx, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADCx, ADC_Channel, 1, ADC_SampleTime_3Cycles);
	ADC_DMARequestAfterLastTransferCmd(ADCx, ENABLE);
	ADC_DMACmd(ADCx, ENABLE);
	ADC_Cmd(ADCx, ENABLE);
}


void initI2C(I2C_TypeDef* I2Cx, uint16_t nMaster_Address, uint32_t nI2C_Speed)
{
	I2C_InitTypeDef  I2C_InitStructure;
	/* I2C configuration */
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = nMaster_Address;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = nI2C_Speed;

	/* Apply I2C configuration after enabling it */
	I2C_Init(I2Cx, &I2C_InitStructure);
	/* I2C Peripheral Enable */
	I2C_Cmd(I2Cx, ENABLE);
}
void initSPI(SPI_TypeDef* SPIx)
{
	SPI_InitTypeDef SPI_InitStructure;

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPIx, &SPI_InitStructure);
	SPI_SSOutputCmd(SPIx, ENABLE);
	SPI_Cmd(SPIx, ENABLE);
}
void initCAN(CAN_TypeDef* CANx)
{
	CAN_InitTypeDef CAN_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* CAN register init */
	CAN_DeInit(CANx);
	CAN_StructInit(&CAN_InitStructure);
	//printf("CAN Initialize Start!\r\n\n");
	/* CAN cell init */
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_ABOM = DISABLE;
	CAN_InitStructure.CAN_AWUM = DISABLE;
	CAN_InitStructure.CAN_NART = DISABLE;
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TXFP = DISABLE;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1 = CAN_BS1_7tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_1tq;
	CAN_InitStructure.CAN_Prescaler = 4;
	CAN_Init(CANx, &CAN_InitStructure);

	// CAN filter init.
	// SCU to ALL
	CAN_FilterInitStructure.CAN_FilterNumber = 1;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = CAN_ID_BASE_SCU_TO_ALL_ID_HIGH;		// 0x20000~0x21FFF ---Shift 3bit(For 32bit Mask)--> 0x100000~0x10FFF8
	CAN_FilterInitStructure.CAN_FilterIdLow = CAN_ID_BASE_SCU_TO_ALL_ID_LOW;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = CAN_ID_BASE_IDMASK_HIGH;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO_NO;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);

	// to MON ALL
	CAN_FilterInitStructure.CAN_FilterNumber = 2;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = CAN_ID_BASE_SCU_TO_MONALL_ID_HIGH;		// 0x28000~0x29FFF ---Shift 3bit(For 32bit Mask)--> 0x140000~0x14FFF8
	CAN_FilterInitStructure.CAN_FilterIdLow = CAN_ID_BASE_SCU_TO_MONALL_ID_LOW;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = CAN_ID_BASE_IDMASK_HIGH;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = CAN_ID_BASE_IDMASK_LOW;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO_NO;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);

	if(g_stMONLocalData.uBPUPosition == MON_SHELF_POS_MON1)
	{	// MON1
		CAN_FilterInitStructure.CAN_FilterNumber = 3;
		CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
		CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
		CAN_FilterInitStructure.CAN_FilterIdHigh = CAN_ID_BASE_SCU_TO_MON_1_ID_HIGH;	// 0x2A000~0x2BFFF ---Shift 3bit(For 32bit Mask)--> 0x150000~0x15FFF8
		CAN_FilterInitStructure.CAN_FilterIdLow = CAN_ID_BASE_SCU_TO_MON_1_ID_LOW;
		CAN_FilterInitStructure.CAN_FilterMaskIdHigh = CAN_ID_BASE_IDMASK_HIGH;
		CAN_FilterInitStructure.CAN_FilterMaskIdLow = CAN_ID_BASE_IDMASK_LOW;
		CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO_NO;
		CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
		CAN_FilterInit(&CAN_FilterInitStructure);
	}
	else if(g_stMONLocalData.uBPUPosition == MON_SHELF_POS_MON2)
	{	// MON2
		CAN_FilterInitStructure.CAN_FilterNumber = 3;
		CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
		CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
		CAN_FilterInitStructure.CAN_FilterIdHigh = CAN_ID_BASE_SCU_TO_MON_2_ID_HIGH;	// 0x2C000~0x2DFFF ---Shift 3bit(For 32bit Mask)--> 0x160000~0x16FFF8
		CAN_FilterInitStructure.CAN_FilterIdLow = CAN_ID_BASE_SCU_TO_MON_2_ID_LOW;
		CAN_FilterInitStructure.CAN_FilterMaskIdHigh = CAN_ID_BASE_IDMASK_HIGH;
		CAN_FilterInitStructure.CAN_FilterMaskIdLow = CAN_ID_BASE_IDMASK_LOW;
		CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO_NO;
		CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
		CAN_FilterInit(&CAN_FilterInitStructure);
	}
	else
	{	// MON - STB
		CAN_FilterInitStructure.CAN_FilterNumber = 3;
		CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
		CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
		CAN_FilterInitStructure.CAN_FilterIdHigh = CAN_ID_BASE_SCU_TO_MON_STB_ID_HIGH;	// 0x2C000~0x2DFFF ---Shift 3bit(For 32bit Mask)--> 0x160000~0x16FFF8
		CAN_FilterInitStructure.CAN_FilterIdLow = CAN_ID_BASE_SCU_TO_MON_STB_ID_LOW;
		CAN_FilterInitStructure.CAN_FilterMaskIdHigh = CAN_ID_BASE_IDMASK_HIGH;
		CAN_FilterInitStructure.CAN_FilterMaskIdLow = CAN_ID_BASE_IDMASK_LOW;
		CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO_NO;
		CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
		CAN_FilterInit(&CAN_FilterInitStructure);
	}

	/* Enable CAN RX0 interrupt IRQ channel */
	NVIC_InitStructure.NVIC_IRQChannel = CAN_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	/* CAN FIFO0 message pending interrupt enable */
	CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);
	//printf("CAN Initialize End!\r\n\n");
}
void initRCC(void)
{
	// must remove unused Peripheral
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF |
			RCC_AHB1Periph_GPIOG | RCC_AHB1Periph_GPIOH | RCC_AHB1Periph_GPIOI | RCC_AHB1Periph_DMA1 | RCC_AHB1Periph_DMA2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 | RCC_APB1Periph_TIM5 | RCC_APB1Periph_TIM6 | RCC_APB1Periph_TIM7 | RCC_APB1Periph_TIM12 | RCC_APB1Periph_TIM13| RCC_APB1Periph_TIM14 |
			RCC_APB1Periph_WWDG | RCC_APB1Periph_SPI2 | RCC_APB1Periph_SPI3 | RCC_APB1Periph_USART2 | RCC_APB1Periph_USART3 | RCC_APB1Periph_UART4 | RCC_APB1Periph_UART5 |
			RCC_APB1Periph_I2C1 | RCC_APB1Periph_I2C2 | RCC_APB1Periph_I2C3 | RCC_APB1Periph_CAN1 | RCC_APB1Periph_PWR | RCC_APB1Periph_DAC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_TIM8 | RCC_APB2Periph_USART1 | RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2 | RCC_APB2Periph_ADC3 |
			RCC_APB2Periph_SPI1 | RCC_APB2Periph_TIM9 | RCC_APB2Periph_TIM10 | RCC_APB2Periph_TIM11, ENABLE);
			// ADC is Changeable!

}


