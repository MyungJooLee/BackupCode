/**
 ******************************************************************************
 *    @file    mon_init.h
 *    @author  mjlee@mopiens.com
 *    @version 0.01
 *    @date    2013/11/28
 *    @brief   LOC/GP MON's Chip initialize Header file.
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

#ifndef __INC_TCU_INIT_H__
#define __INC_TCU_INIT_H__

//////////////////////////////////////////////////////
// Include Section									//
//////////////////////////////////////////////////////

#include "types.h"
#include "define.h"
#include "global_variable.h"
#include "can_handler.h"

#include "stm32f4xx_exti.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_can.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_dac.h"

#include "stm32f407_init.h"
#include "scheduler.h"
#include "ioconf.h"
#include "mon_timer.h"
#include "mon_task.h"

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////
// Global Variable Pre-Define Section				//
//////////////////////////////////////////////////////




//////////////////////////////////////////////////////
// Struct Define Section							//
//////////////////////////////////////////////////////




//////////////////////////////////////////////////////
// Function	Pre-Define Section						//
//////////////////////////////////////////////////////
void initPeripheral(void);
void initAll(void);
void initRCC(void);
void initSPI(SPI_TypeDef* SPIx);
void initI2C(I2C_TypeDef* I2Cx, uint16_t nMaster_Address, uint32_t nI2C_Speed);
void initCAN(CAN_TypeDef* CANx);
void initADC(ADC_TypeDef* ADCx, uint8_t ADC_Channel, FunctionalState ADC_ContinuousConvMode);
void initADC_Sampling(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint32_t ADC_DR_ADDERSS, DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_Channel, uint8_t NVIC_IRQChannel, uint16_t* pBufferAddress0, uint16_t* pBufferAddress1, uint32_t uBufferSize);
void initEtc(void);

#ifdef __cplusplus
}
#endif

#endif	/* __INC_TCU_INIT_H__ */
