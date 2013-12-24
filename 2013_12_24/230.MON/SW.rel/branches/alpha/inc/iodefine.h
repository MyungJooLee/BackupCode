#ifndef __INC_IODEFINE_H__
#define __INC_IODEFINE_H__

//////////////////////////////////////////////////////
// Include Section									//
//////////////////////////////////////////////////////


#ifdef __cplusplus
extern "C" {
#endif



//////////////////////////////////////////////////////
// Define Section									//
//////////////////////////////////////////////////////


////// Timer Define ///////////////////
#define TASK_SCHEDULING_TIMER_NO			TIM3
#define TASK_SCHEDULING_TIMER_CYCLE_US		50000
#define TASK_SCHEDULING_TIMER_PRIORITY		20
#define TASK_SCHEDULING_TIMER_IRQn			TIM3_IRQn


////// USART Define ///////////////////
#define	DEBUG_PORT							USART1
#define	DEBUG_BAUDRATE						115200
#define	DEBUG_IRQn							USART1_IRQn
#define	DEBUG_PRIORITY						10
#define	DEBUG_SUBPRIORITY					10
#define	DEBUG_WORDLENGTH					USART_WordLength_8b
#define	DEBUG_STOPBITS						USART_StopBits_1
#define	DEBUG_PARITY						USART_Parity_No
#define	DEBUG_FLOWCONTROL					USART_HardwareFlowControl_None
#define	DEBUG_MODE							(USART_Mode_Rx | USART_Mode_Tx)


////// I2C Define ///////////////////


////// SPI Define ///////////////////


////// ADC Define ///////////////////



////// DAC Define ///////////////////


////// GPIO Define ///////////////////
#define MON_SHELF_POS_PORT				GPIOD
#define MON_SHELF_POS_PIN				(GPIO_Pin_0 | GPIO_Pin_1)

#define MON_SHELF_POS_MON1				0x00
#define MON_SHELF_POS_MON2				0x01
#define MON_SHELF_POS_MON_STB			0x02

#define MON_CONFIG_PORT					GPIOC
#define MON_CONFIG_PIN					(GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12)

#define FPGA_NSS_PORT					GPIOB
#define FPGA_NSS_PIN					GPIO_Pin_12



#ifdef __cplusplus
}
#endif

#endif	/* __INC_IODEFINE_H__ */
