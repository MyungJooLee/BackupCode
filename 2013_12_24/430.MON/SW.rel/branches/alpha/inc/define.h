#ifndef __INC_DEFINE_H__
#define __INC_DEFINE_H__

//////////////////////////////////////////////////////
// Include Section									//
//////////////////////////////////////////////////////
#define DEBUG

#include "common_define.h"
#include "iodefine.h"
#include "candefine.h"
#include "fpgadefine.h"

#ifdef __cplusplus
extern "C" {
#endif


//////////////////////////////////////////////////////
// Define Section									//
//////////////////////////////////////////////////////

#define MON_1_SHELF_POS_BIT					0
#define MON_2_SHELF_POS_BIT					1
#define MON_STB_SHELF_POS_BIT				2

#define FLASH_ADDRESS_READONLY_START		0x8074000
#define FLASH_ADDRESS_FU_START				0x8078000

#define DEBUG_TO_CAN_ALL_OPCODE_UNITID		1
#define DEBUG_TO_CAN_COM_OPCODE_UNITID		2
#define DEBUG_TO_CAN_NOR_OPCODE_UNITID		3

#define PROCESS_CAN_MAX_COUNT				3
#define PROCESS_DEBUG_MAX_COUNT				3
#define SEND_CAN_MAX_COUNT					3



typedef enum {LG_SAMPLE_NONE = 0, LG_SAMPLE_CL, LG_SAMPLE_DS, LG_SAMPLE_CLR, LG_SAMPLE_NF, LG_SAMPLE_INT_A, LG_SAMPLE_INT_B} LOCGP_MON_SAMPLE_t;

signed int printf(const char *pFormat, ...);

#ifdef __cplusplus
}
#endif

#endif	/* __INC_DEFINE_H__ */
