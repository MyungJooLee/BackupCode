#ifndef __INC_CANDEFINE_H__
#define __INC_CANDEFINE_H__

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
#define CAN_FIFO_NO									CAN_FIFO0
#define CAN_ID_BASE_SCU_TO_ALL_ID_HIGH				0x0010
#define CAN_ID_BASE_SCU_TO_ALL_ID_LOW				0xFFF8
#define CAN_ID_BASE_SCU_TO_MONALL_ID_HIGH			0x0014
#define CAN_ID_BASE_SCU_TO_MONALL_ID_LOW			0xFFF8
#define CAN_ID_BASE_SCU_TO_MON_1_ID_HIGH			0x0015
#define CAN_ID_BASE_SCU_TO_MON_1_ID_LOW				0xFFF8
#define CAN_ID_BASE_SCU_TO_MON_2_ID_HIGH			0x0016
#define CAN_ID_BASE_SCU_TO_MON_2_ID_LOW				0xFFF8
#define CAN_ID_BASE_SCU_TO_MON_STB_ID_HIGH			0x0016
#define CAN_ID_BASE_SCU_TO_MON_STB_ID_LOW			0xFFF8
#define CAN_ID_BASE_IDMASK_HIGH						0xFFFF
#define CAN_ID_BASE_IDMASK_LOW						0x0000

#define	CAN_PORT									CAN1
#define	CAN_FIFO									CAN_FIFO0
#define	CAN_IRQn									CAN1_RX0_IRQn
#define CAN_SEND_BUFFERSIZE							Size512
#define CAN_RECEIVE_BUFFERSIZE						Size512

#define	CAN_MON_1_SEND_UNITID						0x064000
#define	CAN_MON_2_SEND_UNITID						0x066000
#define	CAN_MON_STB_SEND_UNITID						0x068000

#define	CAN_UNITID_MASK								0x07E000
#define	CAN_ALL_OPCODE_UNITID_MASK_RESULT			0x020000

#define	CAN_NORMAL_OPCODE_START_INDEX				0x0400

#define	CAN_ALL_OPCODE_COUNT						7		// Using Handler Table index. Must set Max OPCode No. + 1
#define	CAN_COMMON_OPCODE_COUNT						7
#define	CAN_NORMAL_OPCODE_COUNT						39



//////////////////////////////////////////////////////
// CAN SCU to ALL OPCODE Define Section				//
//////////////////////////////////////////////////////
#define	CAN_R_ALL_OP_BOOT_COMPLETE					0x0001
#define	CAN_R_ALL_OP_FWU_START						0x0002
#define	CAN_R_ALL_OP_FWU_END						0x0003
#define	CAN_R_ALL_OP_UNIT_STATUS					0x0004
#define	CAN_R_ALL_OP_UNIT_STATUS_NOACK				0x0005
#define	CAN_R_ALL_OP_GET_SW_VERSION					0x0006
//////////////////////////////////////////////////////
// CAN SCU to MON COMMON OPCODE Define Section		//
//////////////////////////////////////////////////////
#define	CAN_R_COM_OP_REQUEST_FWU_READY				0x0001
#define	CAN_R_COM_OP_GET_SW_VERSION					0x0002
#define	CAN_R_COM_OP_GO_MCU_RESET					0x0004
#define	CAN_R_COM_OP_GET_HW_VERSION					0x0005
#define	CAN_R_COM_OP_GET_MCU_UNIQUE_ID				0x0006
//////////////////////////////////////////////////////
// CAN SCU to MON NORMAL OPCODE Define Section		//
//////////////////////////////////////////////////////
#define	CAN_R_NOR_OP_MON_MODE						0x0401

//////////////////////////////////////////////////////
// CAN MON to SCU COMMON OPCODE Define Section		//
//////////////////////////////////////////////////////
#define	CAN_S_COM_OP_NORMAL_STATUS					0x0001
#define	CAN_S_COM_OP_NORMAL_STATUS_DATA_REQUEST		0x0002
#define	CAN_S_COM_OP_SW_VERSION						0x0003
#define	CAN_S_COM_OP_FWU_READY						0x0004
#define	CAN_S_COM_OP_HW_VERSION						0x0005
#define	CAN_S_COM_OP_MCU_UNIQUE_ID					0x0006
#define	CAN_S_COM_OP_TRANSACTION_START				0x0009
#define	CAN_S_COM_OP_TRANSACTION_END				0x000A
//////////////////////////////////////////////////////
// CAN MON to SCU NORMAL OPCODE Define Section		//
//////////////////////////////////////////////////////
#define	CAN_S_NOR_OP_MON_STATUS						0x0401


////// DATA BIT MASK //////////////////////



#ifdef __cplusplus
}
#endif

#endif	/* __INC_CANDEFINE_H__ */
