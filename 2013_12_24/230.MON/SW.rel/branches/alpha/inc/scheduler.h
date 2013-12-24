/**
 ******************************************************************************
 *    @file    scheduler.h
 *    @author  mjlee@mopiens.com
 *    @version 0.01
 *    @date    2013/11/28
 *    @brief   LOC/GP MON's scheduler header file.
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
#ifndef __INC_SCHEDULER_H__
#define __INC_SCHEDULER_H__

//////////////////////////////////////////////////////
// Include Section									//
//////////////////////////////////////////////////////
#include "stm32f4xx_tim.h"
#include "stm32f4xx_iwdg.h"

#include "types.h"
#include "define.h"
#include "mon_task.h"
#include "mon_timer.h"
#include "dsp.h"

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////
// define Section									//
//////////////////////////////////////////////////////
#define DSP_SCHEDULING_SLOT_COUNT					7

#define	SJ_SCHEDULING_SLOT_COUNT					8


#define	SCHEDULING_SLOT_NO_R_CAN_1					0
#define	SCHEDULING_SLOT_NO_R_CAN_2					1
#define	SCHEDULING_SLOT_NO_DEBUG					2
#define	SCHEDULING_SLOT_NO_ALARM					3
#define	SCHEDULING_SLOT_NO_FPGA1					4
#define	SCHEDULING_SLOT_NO_S_CAN_1					5
#define	SCHEDULING_SLOT_NO_S_CAN_2					6

//////////////////////////////////////////////////////
// Global Variable Pre-Define Section				//
//////////////////////////////////////////////////////
extern void (* const fpDSPHandler[DSP_SCHEDULING_SLOT_COUNT])(uint16_t* pSampleBaseAddress);
extern void (* const fpSJHandler[SJ_SCHEDULING_SLOT_COUNT])(void);

//////////////////////////////////////////////////////
// Struct Define Section							//
//////////////////////////////////////////////////////
extern uint32_t g_uSchedulerTimerCount;				// Defined in global_variable.c



//////////////////////////////////////////////////////
// Function	Pre-Define Section						//
//////////////////////////////////////////////////////
inline void initScheduler();
inline void startScheduling();






#ifdef __cplusplus
}
#endif

#endif	/* __INC_SCHEDULER_H__ */
