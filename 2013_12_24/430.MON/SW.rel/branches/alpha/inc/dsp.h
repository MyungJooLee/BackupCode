/**
 ******************************************************************************
 *    @file    dsp.h
 *    @author  mjlee@mopiens.com
 *    @version 0.01
 *    @date    2013/12/03
 *    @brief   LOC/GP MON's Digital Signal Processing Header file.
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
#ifndef __INC_DSP_H__
#define __INC_DSP_H__

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////
// Include Section									//
//////////////////////////////////////////////////////

#include "structure.h"
#include "global_variable.h"

#include "math.h"
#include "arm_math.h"



//////////////////////////////////////////////////////
// Global Variable Pre-Define Section				//
//////////////////////////////////////////////////////




//////////////////////////////////////////////////////
// Struct Define Section							//
//////////////////////////////////////////////////////



//////////////////////////////////////////////////////
// Function	Pre-Define Section						//
//////////////////////////////////////////////////////
void processSignal_CL(uint16_t* pSampleBaseAddress);
void processSignal_DS(uint16_t* pSampleBaseAddress);
void processSignal_CLR(uint16_t* pSampleBaseAddress);
void processSignal_NF(uint16_t* pSampleBaseAddress);
void processSignal_INTA(uint16_t* pSampleBaseAddress);
void processSignal_INTB(uint16_t* pSampleBaseAddress);
void processSignal(uint16_t* uaSamples, LOC_GP_RESULT_t* stResult, bool bCopyIDENTDATA);
inline void normalizeInputSignal(uint16_t* uaInput, float* faOutput, int nSize);
inline void setFFTPoint(float* data, fComplex_t* result);
inline float getAmplitude(float real, float image);
inline float getPhase(float real, float image);

void firfil_f32(float* sample, float* coef, float* output, int n, int Filt_lenth);
void fft_f32(float data[], int nn, int isign);
fComplex_t goertzel_f32(float Fs, float freq, int n, float* samp);

#ifdef __cplusplus
}
#endif

#endif	/* __INC_DSP_H__ */
