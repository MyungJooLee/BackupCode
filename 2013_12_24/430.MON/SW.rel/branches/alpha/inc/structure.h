#ifndef __INC_STRUCTURE_H__
#define __INC_STRUCTURE_H__

//////////////////////////////////////////////////////
// Include Section									//
//////////////////////////////////////////////////////
#include "types.h"
#include "define.h"


#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////
// Global Variable Pre-Define Section				//
//////////////////////////////////////////////////////


//////////////////////////////////////////////////////
// Struct Define Section							//
//////////////////////////////////////////////////////
typedef struct __fComplex_t
{
	float r;
	float i;
	float a;
	float p;
}fComplex_t;

typedef struct __LOC_GP_RESULT_t
{
	fComplex_t stDC;
	fComplex_t st90Hz;
	fComplex_t st150Hz;
	fComplex_t st1020Hz;

	float	fPower;
	float	f90AM;
	float	f150AM;
	float	f1020AM;

	float	fSDM;
	float	fDDM;
}LOC_GP_RESULT_t;

typedef struct __MON_LOCAL_DATA_TYPE{
	uint8_t			uMONMode;

	uint32_t 		uCANSendID;
	uint8_t 		uBPUPosition;

	// For Sampling
	LOCGP_MON_SAMPLE_t	eCurrentBuffer_SampeType;
	uint16_t*		pSampleBaseAddress;

	// For Other Unit's Status
	uint16_t 		uOtherUnitPDStatus;
	uint8_t 		uOtherUnitFaultStatus;

	LOC_GP_RESULT_t	stCL_Result;
	LOC_GP_RESULT_t	stDS_Result;
	LOC_GP_RESULT_t	stCLR_Result;
	LOC_GP_RESULT_t	stNF_Result;
	LOC_GP_RESULT_t	stINT_Result;

}MON_LOCAL_DATA_TYPE;

typedef struct __MON_FLASH_DATA_TYPE{
	// Do Not Change-able
	SW_Version_t 	stSW_Version;

	// Calibration
	uint16_t	sCarrierPower;
	uint16_t	sAM1020_MOD;





}MON_FLASH_DATA_TYPE;

typedef struct __MON_DATA_TYPE{
	uint8_t			uMONMode;


}MON_DATA_TYPE;




//////////////////////////////////////////////////////
// Function	Pre-Define Section						//
//////////////////////////////////////////////////////


//////////////////////////////////////////////////////
// Global Variable	Pre-Define Section				//
//////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif

#endif	/* __INC_STRUCTURE_H__ */
