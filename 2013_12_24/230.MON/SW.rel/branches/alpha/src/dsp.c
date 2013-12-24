/**
 ******************************************************************************
 *    @file    dsp.c
 *    @author  mjlee@mopiens.com
 *    @version 0.01
 *    @date    2013/12/03
 *    @brief   LOC/GP MON's Digital Signal Processing source file.
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
#include "dsp.h"





//////////////////////////////////////////////////////
// Global Variable Define Section					//
//////////////////////////////////////////////////////





//////////////////////////////////////////////////////
// Function	Define Section							//
//////////////////////////////////////////////////////
#define ADC_HALF					2048
#define IF_FREQ						8000
#define	IF_FREQ_MUL_2PI				50265.48245743664f
#define	IF_FREQ_MUL_2PI_DIV_ADC_FS	0.52359877559829833f	// 8000 * pi * 2 / 96000
//#define PI						3.14159265358979f
#define DPI							6.28318530717958f

#define ADC_FS					96000
#define ADC_SAMPLE_COUNT		3200

#define ADC_DIVIDE_DAC_SAMPLE	25
#define DAC_FS					3840				// ADC_FS / ADC_DIVIDE_DAC_SAMPLE
#define DAC_SAMPLE_COUNT		128					// ADC_SAMPLE_COUNT / ADC_DIVIDE_DAC_SAMPLE

#define ADC_DIVIDE_FFT_SAMPLE	25
#define FFT_FS					3840				// ADC_FS / ADC_DIVIDE_FFT_SAMPLE
#define FFT_SAMPLE_COUNT		128					// ADC_SAMPLE_COUNT / ADC_DIVIDE_FFT_SAMPLE
#define FFT_DATA_COUNT			257					//	FFT_SAMPLE_COUNT*2 + 1
#define	FFT_SIGN_FFT			1
#define	FFT_SIGN_IFFT			-1
#define	FFT_DC_INDEX			1					// (0/30)*2 + 1
#define	FFT_90_INDEX			7					// (90/30)*2 + 1
#define	FFT_150_INDEX			11					// (150/30)*2 + 1
#define	FFT_1020_INDEX			69					// (1020/30)*2 + 1


void processSignal_CL(uint16_t* pSampleBaseAddress)
{
	//Process Signal
	processSignal(pSampleBaseAddress, &g_stMONLocalData.stCL_Result, TRUE);
	//Alarm Check
	//Send to CAN
	return;
}
void processSignal_DS(uint16_t* pSampleBaseAddress)
{
	//Process Signal
	processSignal(pSampleBaseAddress, &g_stMONLocalData.stDS_Result, FALSE);
	//Alarm Check
	//Send to CAN
	return;
}
void processSignal_CLR(uint16_t* pSampleBaseAddress)
{
	//Process Signal
	processSignal(pSampleBaseAddress, &g_stMONLocalData.stCLR_Result, FALSE);
	//Alarm Check
	//Send to CAN
	return;
}
void processSignal_NF(uint16_t* pSampleBaseAddress)
{
	//Process Signal
	processSignal(pSampleBaseAddress, &g_stMONLocalData.stNF_Result, FALSE);
	//Alarm Check
	//Send to CAN
	return;
}
void processSignal_INTA(uint16_t* pSampleBaseAddress)
{
	//Process Signal
	processSignal(pSampleBaseAddress, &g_stMONLocalData.stINT_Result, FALSE);
	//Alarm Check
	//Send to CAN
	return;
}
void processSignal_INTB(uint16_t* pSampleBaseAddress)
{
	//Process Signal
	processSignal(pSampleBaseAddress, &g_stMONLocalData.stINT_Result, FALSE);
	//Alarm Check
	//Send to CAN
	return;
}
inline void setFFTPoint(float* data, fComplex_t* result)
{
	result->r = data[0];
	result->i = data[1];
	result->a = getAmplitude(data[0], data[1]);
	result->p = getPhase(data[0], data[1]);
}
inline void normalizeInputSignal(uint16_t* uaInput, float* faOutput, int nSize)
{
	int i=0;

	// Nomalize Signal 0~2*ADC_HALF to -1.0~+1.0
	for(i=0; i<nSize; i++)
	{
		faOutput[i] = (uaInput[i]-ADC_HALF)/(float)ADC_HALF;
	}
}
inline void downConversionIFtoBase(float* faSamples_f32, float fPhaseDiff)
{
	// Degree/360 * 2PI
	int i=0;

	// 8K to Baseband Down-Conversion
	for(i=0; i<ADC_SAMPLE_COUNT; i++)
	{
		faSamples_f32[i] = faSamples_f32[i] * arm_cos_f32(IF_FREQ_MUL_2PI_DIV_ADC_FS*i + fPhaseDiff);
	}
}
inline void copyIDENTDACData(float* faSamples_f32)
{
	int i=0;

	for(i=0; i<ADC_SAMPLE_COUNT; i += ADC_DIVIDE_DAC_SAMPLE)
	{
		// COPY to IDENT signal DAC Data Table
	}
}
inline void checkSignal(float* faSamples_f32, LOC_GP_RESULT_t* stResult)
{
	int i, iFFT;
	float faFFTData_f32		[FFT_DATA_COUNT];

	// re-Sampling
	for(i=0, iFFT=0; i<ADC_SAMPLE_COUNT; iFFT+=2, i+=ADC_DIVIDE_FFT_SAMPLE)
	{
		faFFTData_f32[iFFT+1] =	faSamples_f32[i];
		faFFTData_f32[iFFT+2] = 0.;
	}
	// FFT
	fft_f32(faFFTData_f32, FFT_SAMPLE_COUNT, FFT_SIGN_FFT);

	// Set Result
	setFFTPoint(&faFFTData_f32[FFT_DC_INDEX] , &stResult->stDC);
	setFFTPoint(&faFFTData_f32[FFT_90_INDEX] , &stResult->st90Hz);
	setFFTPoint(&faFFTData_f32[FFT_150_INDEX] , &stResult->st150Hz);
	setFFTPoint(&faFFTData_f32[FFT_1020_INDEX] , &stResult->st1020Hz);

	stResult->fPower = stResult->stDC.a;
	stResult->f90AM = stResult->st90Hz.a / stResult->fPower;
	stResult->f150AM = stResult->st150Hz.a / stResult->fPower;
	stResult->f1020AM = stResult->st1020Hz.a / stResult->fPower;
	stResult->fSDM = stResult->f150AM + stResult->f90AM;
	stResult->fDDM = stResult->f150AM - stResult->f90AM;

	// Check IDENT Information

	// Check IDENT Code
}
void processSignal(uint16_t* uaSamples, LOC_GP_RESULT_t* stResult, bool bCopyIDENTDATA)
{
	float faSamples_f32		[ADC_SAMPLE_COUNT];

	// Normailize
	normalizeInputSignal(uaSamples, faSamples_f32, ADC_SAMPLE_COUNT);
	// Check Phase
		// How?
	// Down-Conversion
	downConversionIFtoBase(faSamples_f32, 0.);
	// apply IIR-Filter? - LPF 1.5KHz or 2KHz
		// How?
	// COPY to IDENT signal DAC Data Table
	if(bCopyIDENTDATA == TRUE)
	{
		copyIDENTDACData(faSamples_f32);
	}
	checkSignal(faSamples_f32, stResult);
}

inline float getAmplitude(float real, float image)
{
	float result = 0;
	arm_sqrt_f32(real*real + image*image , &result);
	return result;
}
inline float getPhase(float real, float image)
{
	return atan2(image, real);
}
void firfil_f32(float* sample, float* coef, float* output, int n, int Filt_lenth)
{
	int i, j, maxcount;
	for (i=0; i<n; i++)
	{
		maxcount = (i>Filt_lenth-2)? Filt_lenth-1 : i;
		output[i] = sample[i] * coef[0];
		for(j=1; j<=maxcount; j++)
		{
				output[i] += sample[i-j] * coef[j];
		}
	}
}
fComplex_t goertzel_f32(float Fs, float freq, int n, float* samp)
{
	fComplex_t sample;
	int     k,i;
    float   omega,sine,cosine,coeff,q0,q1,q2;

    k = (int) (0.5 + ((n * freq) / Fs));
    omega = (2.0 * PI * k) / (float)n;
    sine = arm_sin_f32(omega);
    cosine = arm_cos_f32(omega);
    coeff = 2.0 * cosine;
    q0=0;
    q1=0;
    q2=0;
    for(i=0; i<n; i++)
    {
        q0 = coeff * q1 - q2 + samp[i];
        q2 = q1;
        q1 = q0;
    }
	sample.r= (q1 - q2 * cosine);
	sample.i= (q2 * sine);
	arm_sqrt_f32(sample.r*sample.r + sample.i*sample.i, &sample.a);
    return sample;
}

void fft_f32(float data[], int nn, int isign)
{
	int n = 0, mmax = 0, m =0, j= 0 , istep = 0, i = 0;
	float wtemp = 0, wr = 0 , wpr = 0, wpi = 0, wi =0, theta = 0;
	float tempr = 0, tempi = 0;

	n = nn << 1;
	j = 1;
	for (i = 1; i < n; i += 2)
	{
		if (j > i)
		{
			tempr = data[j];     data[j] = data[i];     data[i] = tempr;
			tempr = data[j+1]; data[j+1] = data[i+1]; data[i+1] = tempr;
		}

		m = n >> 1;
		while (m >= 2 && j > m) {
			j -= m;
			m >>= 1;
		}
		j += m;
	}
	mmax = 2;

	while (n > mmax) {
		istep = 2*mmax;
		theta = isign*(DPI/mmax);
		wtemp = arm_sin_f32(0.5*theta);
		wpr = -2.0*wtemp*wtemp;
		wpi = arm_sin_f32(theta);
		wr = 1.0;
		wi = 0.0;
		for (m = 1; m < mmax; m += 2) {
			for (i = m; i <= n; i += istep) {
				j =i + mmax;
				tempr = wr*data[j]   - wi*data[j+1];
				tempi = wr*data[j+1] + wi*data[j];
				data[j]   = data[i]   - tempr;
				data[j+1] = data[i+1] - tempi;
				data[i] += tempr;
				data[i+1] += tempi;
			}
			wr = (wtemp = wr)*wpr - wi*wpi + wr;
			wi = wi*wpr + wtemp*wpi + wi;
		}
		mmax = istep;
	}
}


