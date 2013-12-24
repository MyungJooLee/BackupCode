/**
 ******************************************************************************
 *    @file    scheduler.c
 *    @author  mjlee@mopiens.com
 *    @version 0.01
 *    @date    2013/11/28
 *    @brief   LOC/GP MON's scheduling source file.
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
#include "../inc/scheduler.h"



//////////////////////////////////////////////////////
// Global Variable Define Section					//
//////////////////////////////////////////////////////
void NoJob(uint16_t* pSampleBaseAddress)
{
	return;
}
void (* const fpDSPHandler[DSP_SCHEDULING_SLOT_COUNT])(uint16_t* pSampleBaseAddress) = {
		NULL,	// Must set NULL
		processSignal_CL,
		processSignal_DS,
		processSignal_CLR,
		processSignal_NF,
		processSignal_INTA,
		processSignal_INTB
};
void (* const fpSJHandler[SJ_SCHEDULING_SLOT_COUNT])(void) = {
		processCANMessage,
		checkDCDC,
		processDebugMessage,
		sendCANMessage,
		processCANMessage,
		checkFPGA,
		sendCANMessage,
};

//////////////////////////////////////////////////////
// Function	Define Section							//
//////////////////////////////////////////////////////
inline void selectSideJobs()
{
	static int iSideJobCount = 0;
	const int nSideJobMaxCount = 10;
	fpSJHandler[iSideJobCount]();
	iSideJobCount = (iSideJobCount + 1) % nSideJobMaxCount;
}
inline void startScheduling()
{
	startTimer(TASK_SCHEDULING_TIMER_NO);
	__DEBUG("Scheduler Start! \r\n\n");

	// infinity loop for scheduling
	while(1)
	{
		//Flag Check
		if(g_stMONLocalData.eCurrentBuffer_SampeType != LG_SAMPLE_NONE)
		{
			// include DSP Processing & ADC Control!
			// Must!!! finished in 33ms
			fpDSPHandler[g_stMONLocalData.eCurrentBuffer_SampeType](g_stMONLocalData.pSampleBaseAddress);
			continue;
		}
		//Other Job
			// DC/DC Check - 5, 8, 15, -15, 28, 50, 28_IN
			// CPLD Communicatoin - CRS, CLR, Differ Freq.
			// CAN
			// Debug Message
		selectSideJobs();
	}

	// Do not reach this statement!
	__DEBUG("Scheduler End! \r\n");
}

