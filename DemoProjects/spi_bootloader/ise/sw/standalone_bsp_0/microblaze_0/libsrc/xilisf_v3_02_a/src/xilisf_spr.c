/******************************************************************************
*
* (c) Copyright 2012-2013 Xilinx, Inc. All rights reserved.
*
* This file contains confidential and proprietary information of Xilinx, Inc.
* and is protected under U.S. and international copyright and other
* intellectual property laws.
*
* DISCLAIMER
* This disclaimer is not a license and does not grant any rights to the
* materials distributed herewith. Except as otherwise provided in a valid
* license issued to you by Xilinx, and to the maximum extent permitted by
* applicable law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL
* FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS,
* IMPLIED, OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
* MERCHANTABILITY, NON-INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE;
* and (2) Xilinx shall not be liable (whether in contract or tort, including
* negligence, or under any other theory of liability) for any loss or damage
* of any kind or nature related to, arising under or in connection with these
* materials, including for any direct, or any indirect, special, incidental,
* or consequential loss or damage (including loss of data, profits, goodwill,
* or any type of loss or damage suffered as a result of any action brought by
* a third party) even if such damage or loss was reasonably foreseeable or
* Xilinx had been advised of the possibility of the same.
*
* CRITICAL APPLICATIONS
* Xilinx products are not designed or intended to be fail-safe, or for use in
* any application requiring fail-safe performance, such as life-support or
* safety devices or systems, Class III medical devices, nuclear facilities,
* applications related to the deployment of airbags, or any other applications
* that could lead to death, personal injury, or severe property or
* environmental damage (individually and collectively, "Critical
* Applications"). Customer assumes the sole risk and liability of any use of
* Xilinx products in Critical Applications, subject only to applicable laws
* and regulations governing limitations on product liability.
*
* THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE
* AT ALL TIMES.
*
******************************************************************************/
/*****************************************************************************/
/**
*
* @file xilisf_spr.c
*
* This file contains the library functions to operate on Sector Protection
* feature of the Serial Flash. Refer xilisf.h for a detailed description.
*
* <pre>
*
* MODIFICATION HISTORY:
*
* Ver   Who      Date     Changes
* ----- -------  -------- -----------------------------------------------
* 1.00a ksu/sdm  03/03/08 First release
* 2.01a sdm      01/04/10 Added Support for Winbond W25QXX/W25XX devices
* 2.04a sdm      08/17/10 Updated to support Numonyx (N25QXX) and Spansion
*			  flash memories
*
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "include/xilisf.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

extern int XIsf_Transfer(XIsf *InstancePtr, u8 *WritePtr, u8* ReadPtr,
				u32 ByteCount);
extern int XIsf_GetStatus(XIsf *InstancePtr, u8 *ReadPtr);
static int SprRead(XIsf *InstancePtr, u8 *ReadPtr);
static int SprProgram(XIsf *InstancePtr, u8 *BufferPtr);

static int SprErase(XIsf *InstancePtr);
static int SpEnable(XIsf *InstancePtr);
static int SpDisable(XIsf *InstancePtr);

/************************** Variable Definitions *****************************/

/************************** Function Definitions ******************************/


/*****************************************************************************/
/**
*
* This API is used for performing Sector Protect related operations.
*
* @param	InstancePtr is a pointer to the XIsf instance.
* @param	Operation is the type of Sector Protect operation to be
*		performed on the Serial Flash.
*		The different operations are
*		- XISF_SPR_READ: Read Sector Protection Register
*		- XISF_SPR_WRITE: Write Sector Protection Register
*		- XISF_SPR_ERASE: Erase Sector Protection Register
*		- XISF_SP_ENABLE: Enable Sector Protection
*		- XISF_SP_DISABLE: Disable Sector Protection
* @param	BufferPtr is a pointer to the memory where the SPR content is
*		read to/written from. This argument can be NULL if the
*		Operation is SprErase, SpEnable and SpDisable.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note
*		- The SPR content is stored at the fourth location pointed
*		by the BufferPtr when performing XISF_SPR_READ operation.
*		- For Intel, STM, Winbond and Spansion Serial Flash, the user
*		application must call the XIsf_WriteEnable() API by passing
*		XISF_WRITE_ENABLE as an argument, before calling the
*		XIsf_SectorProtect() API, for Sector Protect Register Write
*		(XISF_SPR_WRITE) operation.
*		- Atmel Flash supports all these Sector Protect operations.
*		- Intel, STM, Winbond and Spansion Flash support only Sector
*		Protect Read and Sector Protect Write operations.
*
******************************************************************************/
int XIsf_SectorProtect(XIsf *InstancePtr, XIsf_SpOperation Operation,
				u8 *BufferPtr)
{
	int Status = XST_FAILURE;

	switch (Operation) {
		case XISF_SPR_READ:
			Status = SprRead(InstancePtr, BufferPtr);
			break;

		case XISF_SPR_WRITE:
			Status = SprProgram(InstancePtr, BufferPtr);
			break;

		case XISF_SPR_ERASE:
			Status = SprErase(InstancePtr);
			break;

		case XISF_SP_ENABLE:
			Status = SpEnable(InstancePtr);
			break;

		case XISF_SP_DISABLE:
			Status = SpDisable(InstancePtr);
			break;

		default:
			break;
	}

	return Status;
}

/*****************************************************************************/
/**
*
* This function reads the content of the Sector Protection Register(SPR).
*
* @param	InstancePtr is a pointer to the XIsf instance.
* @param	ReadPtr is a pointer to the memory where the SPR content is
*		copied.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note
*		- This operation is supported for Atmel, Intel, STM, Winbond
*		and Spansion Serial Flash.
*		- The SPR content is stored at the fourth location pointed
*		by the ReadPtr for Atmel Serial Flash and at the second location
*		for STM/Intel/Winbond/Spansion Serial Flash.
*
******************************************************************************/
static int SprRead(XIsf *InstancePtr, u8 *ReadPtr)
{
	int Status;

	if (ReadPtr == NULL) {
		return XST_FAILURE;
	}

#if (XPAR_XISF_FLASH_FAMILY == ATMEL)
	u32 Index;

	/*
	 * Prepare the Write Buffer.
	 */
	InstancePtr->WriteBufPtr[BYTE1] = XISF_CMD_SPR_READ;

	for(Index = 1; Index < (InstancePtr->NumOfSectors +
				XISF_CMD_SEND_EXTRA_BYTES); Index++) {
		InstancePtr->WriteBufPtr[Index] = XISF_DUMMYBYTE;
	}

	/*
	 * Initiate the Transfer.
	 */
	Status = XIsf_Transfer(InstancePtr, InstancePtr->WriteBufPtr, ReadPtr,
				InstancePtr->NumOfSectors +
				XISF_CMD_SEND_EXTRA_BYTES);

#else

	Status = XIsf_GetStatus(InstancePtr, ReadPtr);

#endif /* (XPAR_XISF_FLASH_FAMILY == ATMEL) */

	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function writes to the Sector Protection Register(SPR).
*
* @param	InstancePtr is a pointer to the XIsf instance.
* @param	BufferPtr is the pointer to the data to be written to SPR.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note		This operation is supported for Atmel, Intel, STM, Winbond and
*		Spansion Serial Flash.
*
******************************************************************************/
static int SprProgram(XIsf *InstancePtr, u8 *BufferPtr)
{
	int Status;

	if (BufferPtr == NULL) {
		return XST_FAILURE;
	}

#if (XPAR_XISF_FLASH_FAMILY == ATMEL)
	u32 Index;

	/*
	 * Prepare the Write Buffer.
	 */
	InstancePtr->WriteBufPtr[BYTE1] = XISF_CMD_SPR_BYTE1;
	InstancePtr->WriteBufPtr[BYTE2] = XISF_CMD_SPR_BYTE2;
	InstancePtr->WriteBufPtr[BYTE3] = XISF_CMD_SPR_BYTE3;
	InstancePtr->WriteBufPtr[BYTE4] = XISF_CMD_SPR_BYTE4_PROGRAM;

	for(Index = 4; Index < (InstancePtr->NumOfSectors +
			XISF_CMD_SEND_EXTRA_BYTES); Index++) {
		InstancePtr->WriteBufPtr[Index] = *BufferPtr++;
	}

	/*
	 * Initiate the Transfer.
	 */
	Status = XIsf_Transfer(InstancePtr, InstancePtr->WriteBufPtr, NULL,
				InstancePtr->NumOfSectors +
				XISF_CMD_SEND_EXTRA_BYTES);
#else

	Status = XIsf_Write(InstancePtr, XISF_WRITE_STATUS_REG,
				(void*) BufferPtr);

#endif /* (XPAR_XISF_FLASH_FAMILY == ATMEL) */

	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function erases the content of the Sector Protection Register(SPR).
*
* @param	InstancePtr is a pointer to the XIsf instance.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note		This operation is only supported for Atmel Serial Flash.
*
******************************************************************************/
static int SprErase(XIsf *InstancePtr)
{
	int Status = XST_FAILURE;

#if (XPAR_XISF_FLASH_FAMILY == ATMEL)
	/*
	 * Prepare the Write Buffer.
	 */
	InstancePtr->WriteBufPtr[BYTE1] = XISF_CMD_SPR_BYTE1;
	InstancePtr->WriteBufPtr[BYTE2] = XISF_CMD_SPR_BYTE2;
	InstancePtr->WriteBufPtr[BYTE3] = XISF_CMD_SPR_BYTE3;
	InstancePtr->WriteBufPtr[BYTE4] = XISF_CMD_SPR_BYTE4_ERASE;

	/*
	 * Initiate the Transfer.
	 */
	Status = XIsf_Transfer(InstancePtr, InstancePtr->WriteBufPtr, NULL,
					XISF_CMD_SEND_EXTRA_BYTES);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
#endif /* (XPAR_XISF_FLASH_FAMILY == ATMEL) */

	return Status;
}

/*****************************************************************************/
/**
*
* This function enables Sector Protection. Sectors specified for protection in
* the Sector Protection Register are protected by using this operation.
*
* @param	InstancePtr is a pointer to the XIsf instance.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note		This operation is only supported for Atmel Serial Flash.
*
******************************************************************************/
static int SpEnable(XIsf *InstancePtr)
{
	int Status = XST_FAILURE;

#if (XPAR_XISF_FLASH_FAMILY == ATMEL)
	/*
	 * Prepare the Write Buffer.
	 */
	InstancePtr->WriteBufPtr[BYTE1] = XISF_CMD_SPR_BYTE1;
	InstancePtr->WriteBufPtr[BYTE2] = XISF_CMD_SPR_BYTE2;
	InstancePtr->WriteBufPtr[BYTE3] = XISF_CMD_SPR_BYTE3;
	InstancePtr->WriteBufPtr[BYTE4] = XISF_CMD_SPR_BYTE4_ENABLE;

	/*
	 * Initiate the Transfer.
	 */
	Status = XIsf_Transfer(InstancePtr, InstancePtr->WriteBufPtr, NULL,
				XISF_CMD_SEND_EXTRA_BYTES);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
#endif /* (XPAR_XISF_FLASH_FAMILY == ATMEL) */

	return Status;
}

/*****************************************************************************/
/**
*
* This function Disables Sector Protection.
*
* @param	InstancePtr is a pointer to the XIsf instance.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note		This operation is only supported for Atmel Serial Flash.
*
******************************************************************************/
static int SpDisable(XIsf *InstancePtr)
{
	int Status = XST_FAILURE;

#if (XPAR_XISF_FLASH_FAMILY == ATMEL)
	/*
	 * Prepare the Write Buffer.
	 */
	InstancePtr->WriteBufPtr[BYTE1] = XISF_CMD_SPR_BYTE1;
	InstancePtr->WriteBufPtr[BYTE2] = XISF_CMD_SPR_BYTE2;
	InstancePtr->WriteBufPtr[BYTE3] = XISF_CMD_SPR_BYTE3;
	InstancePtr->WriteBufPtr[BYTE4] = XISF_CMD_SPR_BYTE4_DISABLE;

	/*
	 * Initiate the Transfer.
	 */
	Status = XIsf_Transfer(InstancePtr, InstancePtr->WriteBufPtr, NULL,
				XISF_CMD_SEND_EXTRA_BYTES);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
#endif /* (XPAR_XISF_FLASH_FAMILY == ATMEL) */

	return Status;
}
