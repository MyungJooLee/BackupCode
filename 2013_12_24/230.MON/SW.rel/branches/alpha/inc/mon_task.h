#ifndef __INC_MON_TASK_H__
#define __INC_MON_TASK_H__

//////////////////////////////////////////////////////
// Include Section									//
//////////////////////////////////////////////////////
#include "types.h"
#include "define.h"

#include "global_variable.h"
#include "common_queue.h"
#include "can_quintet.h"
#include "mon_init.h"

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_exti.h"

#include "misc.h"

#include "scheduler.h"
#include "dle.h"
#include "can_handler.h"

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////
// Struct Define Section							//
//////////////////////////////////////////////////////



//////////////////////////////////////////////////////
// Global Variable Pre-Define Section				//
//////////////////////////////////////////////////////









//////////////////////////////////////////////////////
// Function	Pre-Define Section						//
//////////////////////////////////////////////////////
void checkDCDC(void);
void checkFPGA(void);
void processCANMessage(void);
void processDebugMessage(void);
void sendCANMessage(void);

inline void writeBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
inline void setBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
inline void resetBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
inline void writeFPGA(SPI_TypeDef* SPIx, uint16_t uData, uint16_t uAddress);
inline uint16_t readFPGA(SPI_TypeDef* SPIx, uint16_t uSendData);
void readFPGAnSendCAN(SPI_TypeDef* SPIx, uint16_t uSendData, uint16_t* uDestData, uint16_t uFPGA_CAN_SEND_OP);
uint16_t commSPI(SPI_TypeDef* SPIx, uint16_t uData);
inline void sendLiveMessagetoSCU(LIVE_MODE_t eMode);
inline void sendPulsetoWatchdogIC(LIVE_MODE_t eMode);
inline void delay_us(uint32_t nDelayTime);
inline uint8_t getBPUPosition(void);
inline uint8_t getConfigBit(void);
inline uint8_t getCANUnitID(void);
inline void setCANUnitID(uint8_t uBPUPosition);
inline void sendSWVersion();




#ifdef __cplusplus
}
#endif

#endif	/* __INC_MON_TASK_H__ */
