#ifndef __INC_FPGADEFINE_H__
#define __INC_FPGADEFINE_H__

//////////////////////////////////////////////////////
// Include Section									//
//////////////////////////////////////////////////////


#ifdef __cplusplus
extern "C" {
#endif



//////////////////////////////////////////////////////
// Define Section									//
//////////////////////////////////////////////////////


////// ID Define ///////////////////



////// COMMON OPCODE Define ///////////////
#define FPGA_ADDRESS_WRTIE								0x4000
#define FPGA_ADDRESS_READ								0x0000
#define FPGA_DATA_FRAME									0x8000
#define FPGA_ADDRESS_FRAME								0x0000

#define FPGA1_ADDRESS_RX_CONTROL_BIT					0x0000


#ifdef __cplusplus
}
#endif

#endif	/* __INC_FPGADEFINE_H__ */
