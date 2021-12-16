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
* @file xilisf_write.c
*
* This file contains the library functions to write to the Serial Flash
* devices. Refer xilisf.h for detailed description.
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
* 3.00a srt	 06/20/12 Updated to support interfaces SPI PS and QSPI PS.
*			  Added support to SST flash on SPI PS interface.
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
static int WriteData(XIsf *InstancePtr, u8 Command, u32 Address,
			const u8 *BufferPtr, u32 ByteCount);
static int AutoPageWrite(XIsf *InstancePtr, u32 Address);
static int BufferWrite(XIsf *InstancePtr, u8 BufferNum, const u8 *WritePtr,
			u32 ByteOffset, u32 NumBytes);
static int BufferToFlashWriteWithErase(XIsf *InstancePtr, u8 BufferNum,
					u32 Address);
static int BufferToFlashWriteWithoutErase(XIsf *InstancePtr, u8 BufferNum,
					  u32 Address);
static int WriteSR(XIsf *InstancePtr, u8 SRData);
static int WriteSR2(XIsf *InstancePtr, u8 *SRData);
static int WriteOTPData(XIsf *InstancePtr, u32 Address, const u8 *BufferPtr);

/************************** Variable Definitions *****************************/

/************************** Function Definitions ******************************/


/*****************************************************************************/
/**
*
* This API writes the data to the Serial Flash.
*
* @param	InstancePtr is a pointer to the XIsf instance.
* @param	Operation is the type of write operation to be performed on the
*		Serial Flash.
*		The different operations are
*		- XISF_WRITE: Normal Write
*		- XISF_DUAL_IP_PAGE_WRITE: Dual Input Fast Program
*		- XISF_DUAL_IP_EXT_PAGE_WRITE: Dual Input Extended Fast Program
*		- XISF_QUAD_IP_PAGE_WRITE: Quad Input Fast Program
*		- XISF_QUAD_IP_EXT_PAGE_WRITE: Quad Input Extended Fast Program
*		- XISF_AUTO_PAGE_WRITE: Auto Page Write
*		- XISF_BUFFER_WRITE: Buffer Write
*		- XISF_BUF_TO_PAGE_WRITE_WITH_ERASE: Buffer to Page Transfer
*			with Erase
*		- XISF_BUF_TO_PAGE_WRITE_WITHOUT_ERASE: Buffer to Page Transfer
*			without Erase
*		- XISF_WRITE_STATUS_REG: Status Register Write
*		- XISF_WRITE_STATUS_REG2: 2 byte Status Register Write
*		- XISF_OTP_WRITE: OTP Write.
*
* @param	OpParamPtr is the pointer to a structure variable which contains
*		operational parameters of the specified operation.
*		This parameter type is dependant on value of first argument
*		(Operation).
*
*		- Normal Write (XISF_WRITE), Dual Input Fast Program
*		(XISF_DUAL_IP_PAGE_WRITE), Dual Input Extended Fast Program
*		(XISF_DUAL_IP_EXT_PAGE_WRITE), Quad Input Fast Program
*		(XISF_QUAD_IP_PAGE_WRITE), Quad Input Extended Fast Program
*		(XISF_QUAD_IP_EXT_PAGE_WRITE):
*		The OpParamPtr must be of type struct XIsf_WriteParam.
* 		OpParamPtr->Address is the start address in the Serial Flash.
*		OpParamPtr->WritePtr is a pointer to the data to be written to
*		the Serial Flash.
*		OpParamPtr->NumBytes is the number of bytes to be written to the
*		Serial Flash.
*		This operation is supported for Atmel, Intel, STM, Winbond and
*		Spansion Serial Flash.
*
*		- Auto Page Write (XISF_AUTO_PAGE_WRITE):
*		The OpParamPtr must be of 32 bit unsigned integer variable. This
*		is the address of page number in the Serial Flash which is to be
*		refreshed.
*		This operation is only supported for Atmel Serial Flash.
*
*		- Buffer Write (XISF_BUFFER_WRITE):
*		The OpParamPtr must be of type struct
*		XIsf_BufferToFlashWriteParam.
*		OpParamPtr->BufferNum specifies the internal SRAM Buffer of the
*		Serial Flash. The valid values are XISF_PAGE_BUFFER1 or
*		XISF_PAGE_BUFFER2. XISF_PAGE_BUFFER2 is not valid in the case of
*		AT45DB011D Flash as it contains a single buffer.
*		OpParamPtr->WritePtr is a pointer to the data to be written to
*		the Serial Flash SRAM Buffer.
*		OpParamPtr->ByteOffset is byte offset in the buffer from where
*		the data is to be written.
*		OpParamPtr->NumBytes is the number of bytes to be written to the
*		Buffer.
*		This operation is supported only for Atmel Serial Flash.
*
*		- Buffer To Memory Write With Erase
*			(XISF_BUF_TO_PAGE_WRITE_WITH_ERASE)/
*		  Buffer To Memory Write Without Erase
*			(XISF_BUF_TO_PAGE_WRITE_WITHOUT_ERASE):
*		The OpParamPtr must be  of type struct
*		XIsf_BufferToFlashWriteParam.
*		OpParamPtr->BufferNum specifies the internal SRAM Buffer of the
*		Serial Flash. The valid values are XISF_PAGE_BUFFER1 or
*		XISF_PAGE_BUFFER2. XISF_PAGE_BUFFER2 is not valid in the case of
*		AT45DB011D Flash as it contains a single buffer.
*		OpParamPtr->Address is starting address in the Serial Flash
*		memory from where the data is to be written.
*		These operations are only supported for Atmel Serial Flash.
*
*		- Write Status Register (XISF_WRITE_STATUS_REG):
*		The OpParamPtr must be  of type of 8 bit unsigned integer
*		variable. This is the value to be written to the Status
*		Register.
*		This operation is only supported for Intel, STM Winbond and
*		Spansion Serial Flash.
*
*		- Write Status Register2 (XISF_WRITE_STATUS_REG2):
*		The OpParamPtr must be  of type (u8 *) and should point to two
*		8 bit unsigned integer values. This is the value to be written
*		to the 16 bit Status Register.
*		This operation is only supported in Winbond (W25Q) Serial Flash.
*
*		- One Time Programmable Area Write (XISF_OTP_WRITE):
*		The OpParamPtr must be of type struct XIsf_WriteParam.
*		OpParamPtr->Address is the address in the SRAM Buffer of the
*		Serial Flash to which the data is to be written.
*		OpParamPtr->WritePtr is a pointer to the data to be written to
*		the Serial Flash.
*		OpParamPtr->NumBytes should be set to 1 when performing OTPWrite
*		operation.
*		This operation is only supported for Intel Serial Flash.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note
*		- Application must fill the structure elements of the third
*		argument and pass its pointer by type casting it with void
*		pointer.
*		- For Intel, STM, Winbond and Spansion Serial Flash, the user
*		application must call the XIsf_WriteEnable() API by passing
*		XISF_WRITE_ENABLE as an argument, before calling the
*		XIsf_Write() API.
*
******************************************************************************/
int XIsf_Write(XIsf *InstancePtr, XIsf_WriteOperation Operation,
			void *OpParamPtr)
{
	int Status = XST_FAILURE;
	XIsf_WriteParam *WriteParamPtr;
	XIsf_BufferWriteParam *BufferWriteParamPtr;
	XIsf_BufferToFlashWriteParam *BufferToFlashWriteParamPtr;

	if (InstancePtr == NULL) {
		return XST_FAILURE;
	}

	if (InstancePtr->IsReady != TRUE) {
		return XST_FAILURE;
	}

	if (NULL == OpParamPtr) {
		return XST_FAILURE;
	}

	switch (Operation) {
		case XISF_WRITE:
			WriteParamPtr = (XIsf_WriteParam*) OpParamPtr;
			Status = WriteData(InstancePtr,
					XISF_CMD_PAGEPROG_WRITE,
					WriteParamPtr->Address,
					WriteParamPtr->WritePtr,
					WriteParamPtr->NumBytes);
			break;

		case XISF_AUTO_PAGE_WRITE:
			Status = AutoPageWrite(InstancePtr,
						*((u32*)OpParamPtr));
			break;

		case XISF_BUFFER_WRITE:
			BufferWriteParamPtr = (XIsf_BufferWriteParam*)
						OpParamPtr;
			Status = BufferWrite(InstancePtr,
					BufferWriteParamPtr->BufferNum,
					BufferWriteParamPtr->WritePtr,
					BufferWriteParamPtr->ByteOffset,
					BufferWriteParamPtr->NumBytes);
			break;

		case XISF_BUF_TO_PAGE_WRITE_WITH_ERASE:
			BufferToFlashWriteParamPtr =
				(XIsf_BufferToFlashWriteParam*) OpParamPtr;
			Status = BufferToFlashWriteWithErase(InstancePtr,
					BufferToFlashWriteParamPtr->BufferNum,
					BufferToFlashWriteParamPtr->Address);
			break;

		case XISF_BUF_TO_PAGE_WRITE_WITHOUT_ERASE:
			BufferToFlashWriteParamPtr =
				(XIsf_BufferToFlashWriteParam*) OpParamPtr;
			Status = BufferToFlashWriteWithoutErase(InstancePtr,
					BufferToFlashWriteParamPtr->BufferNum,
					BufferToFlashWriteParamPtr->Address);
			break;

		case XISF_WRITE_STATUS_REG:
			Status = WriteSR(InstancePtr, *((u8*)OpParamPtr));
			break;

		case XISF_OTP_WRITE:
			WriteParamPtr = (XIsf_WriteParam*) OpParamPtr;
			if (1 == WriteParamPtr->NumBytes) {
				Status = WriteOTPData(InstancePtr,
					WriteParamPtr->Address,
					WriteParamPtr->WritePtr);
			}
			break;

		case XISF_WRITE_STATUS_REG2:
			Status = WriteSR2(InstancePtr, (u8*)OpParamPtr);
			break;

#if ((XPAR_XISF_FLASH_FAMILY == WINBOND) || (XPAR_XISF_FLASH_FAMILY == STM) || \
     (XPAR_XISF_FLASH_FAMILY == SPANSION))
		case XISF_QUAD_IP_PAGE_WRITE:
			WriteParamPtr = (XIsf_WriteParam*) OpParamPtr;
			Status = WriteData(InstancePtr,
					XISF_CMD_QUAD_IP_PAGE_WRITE,
					WriteParamPtr->Address,
					WriteParamPtr->WritePtr,
					WriteParamPtr->NumBytes);
			break;

#endif /*((XPAR_XISF_FLASH_FAMILY == WINBOND) ||
	  (XPAR_XISF_FLASH_FAMILY == STM) ||
	  (XPAR_XISF_FLASH_FAMILY == SPANSION))*/

#if (XPAR_XISF_FLASH_FAMILY == STM)
		case XISF_DUAL_IP_PAGE_WRITE:
			WriteParamPtr = (XIsf_WriteParam*) OpParamPtr;
			Status = WriteData(InstancePtr,
					XISF_CMD_DUAL_IP_PAGE_WRITE,
					WriteParamPtr->Address,
					WriteParamPtr->WritePtr,
					WriteParamPtr->NumBytes);
			break;

		case XISF_DUAL_IP_EXT_PAGE_WRITE:
			WriteParamPtr = (XIsf_WriteParam*) OpParamPtr;
			Status = WriteData(InstancePtr,
					XISF_CMD_DUAL_IP_EXT_PAGE_WRITE,
					WriteParamPtr->Address,
					WriteParamPtr->WritePtr,
					WriteParamPtr->NumBytes);
			break;

		case XISF_QUAD_IP_EXT_PAGE_WRITE:
			WriteParamPtr = (XIsf_WriteParam*) OpParamPtr;
			Status = WriteData(InstancePtr,
					XISF_CMD_QUAD_IP_EXT_PAGE_WRITE,
					WriteParamPtr->Address,
					WriteParamPtr->WritePtr,
					WriteParamPtr->NumBytes);
			break;
#endif /* (XPAR_XISF_FLASH_FAMILY == STM) */

		default:
			break;
	}

	return Status;
}

/*****************************************************************************/
/**
*
* This function writes the data to the specified address locations in the Serial
* Flash.
*
* @param	InstancePtr is a pointer to the XIsf instance.
* @param	Address is the address in the Serial Flash memory, where the
*		data is to be written.
* @param	BufferPtr is a pointer to the data to be written to Serial
*		Flash.
* @param	ByteCount is the number of bytes to be written.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note
*		- A minimum of one byte and a maximum of one Page can be
*		written using this function.
*		- This operation is supported for Atmel, Intel, STM, Winbond
*		and Spansion Serial Flash.
*
******************************************************************************/
static int WriteData(XIsf *InstancePtr, u8 Command, u32 Address,
			const u8 *BufferPtr, u32 ByteCount)
{
	u32 Index;
	int Status;

	if ((ByteCount <= 0) || (ByteCount > InstancePtr->BytesPerPage)) {
		return XST_FAILURE;
	}

	if (BufferPtr == NULL) {
		return XST_FAILURE;
	}

	InstancePtr->WriteBufPtr[BYTE1] = Command;
	InstancePtr->WriteBufPtr[BYTE2] = (u8) (Address >> XISF_ADDR_SHIFT16);
	InstancePtr->WriteBufPtr[BYTE3] = (u8) (Address >> XISF_ADDR_SHIFT8);
	InstancePtr->WriteBufPtr[BYTE4] = (u8) (Address);

	for(Index = 4; Index < ByteCount + XISF_CMD_SEND_EXTRA_BYTES;
								Index++) {
		InstancePtr->WriteBufPtr[Index] = *BufferPtr++;
	}

	/*
	 * Initiate the Transfer.
	 */
	Status = XIsf_Transfer(InstancePtr, InstancePtr->WriteBufPtr, NULL,
				(ByteCount + XISF_CMD_SEND_EXTRA_BYTES));
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function Auto rewrites the contents of a Page in the Serial Flash.
*
* @param	InstancePtr is a pointer to the XIsf instance.
* @param	Address is the address of the page to be refreshed.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note		This operation is only supported for Atmel Serial Flash.
*
******************************************************************************/
static int AutoPageWrite(XIsf *InstancePtr, u32 Address)
{
	int Status = XST_FAILURE;

#if (XPAR_XISF_FLASH_FAMILY == ATMEL)
	InstancePtr->WriteBufPtr[BYTE1] = XISF_CMD_AUTOPAGE_WRITE;
	InstancePtr->WriteBufPtr[BYTE2] = (u8) (Address >> XISF_ADDR_SHIFT16);
	InstancePtr->WriteBufPtr[BYTE3] = (u8) (Address >> XISF_ADDR_SHIFT8);
	InstancePtr->WriteBufPtr[BYTE4] = (XISF_DUMMYBYTE);

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
* This function writes data to the specified SRAM buffer of the Serial Flash.
*
* @param	InstancePtr is a pointer to the XIsf instance.
* @param	BufferNum specifies the internal SRAM Buffer of the Serial
*		Flash. The valid values are XISF_PAGE_BUFFER1 or
*		XISF_PAGE_BUFFER2. XISF_PAGE_BUFFER2 is not valid in case of
*		Atmel AT45DB011D Serial Flash as it contains a single buffer.
* @param	WritePtr is the pointer to the data to be written to the
*		Serial Flash SRAM Buffer.
* @param	ByteOffset is the byte offset in the buffer from where the
*		data is to be written.
* @param	NumBytes is the number of bytes to be written to the Buffer.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note
*		- A minimum of one byte and a maximum of one SRAM buffer can be
*		written using this function.
*		- This operation is only supported for Atmel Serial Flash.
*
******************************************************************************/
static int BufferWrite(XIsf *InstancePtr, u8 BufferNum, const u8 *WritePtr,
			u32 ByteOffset, u32 NumBytes)
{
	int Status = XST_FAILURE;

#if (XPAR_XISF_FLASH_FAMILY == ATMEL)
	u16 Index;

	/*
	 * Check buffer number is valid or not.
	 */
	if ((BufferNum == XISF_PAGE_BUFFER1) ||
		(BufferNum == XISF_PAGE_BUFFER2)) {
		if ((InstancePtr->DeviceCode  == XISF_ATMEL_DEV_AT45DB011D) &&
			(BufferNum != XISF_PAGE_BUFFER1)) {
			return XST_FAILURE;
		}
	}
	else{
		return XST_FAILURE;
	}

	if (WritePtr == NULL) {
			return XST_FAILURE;
	}

	if (ByteOffset > InstancePtr->BytesPerPage) {
		return XST_FAILURE;
	}

	if ((NumBytes <= 0) || (NumBytes > InstancePtr->BytesPerPage)) {
		return XST_FAILURE;
	}


	if (BufferNum == XISF_PAGE_BUFFER1) {
		InstancePtr->WriteBufPtr[BYTE1] = XISF_CMD_BUFFER1_WRITE;
	}
	else{
		InstancePtr->WriteBufPtr[BYTE1] = XISF_CMD_BUFFER2_WRITE;
	}
	InstancePtr->WriteBufPtr[BYTE2] = (u8) (0x00);
	InstancePtr->WriteBufPtr[BYTE3] = (u8) (ByteOffset >> XISF_ADDR_SHIFT8);
	InstancePtr->WriteBufPtr[BYTE4] = (u8) ByteOffset;


	for(Index = 4; Index < NumBytes + XISF_CMD_SEND_EXTRA_BYTES; Index++) {
		InstancePtr->WriteBufPtr[Index] = *WritePtr++;
	}

	/*
	 * Initiate the Transfer.
	 */
	Status = XIsf_Transfer(InstancePtr, InstancePtr->WriteBufPtr, NULL,
				(NumBytes + XISF_CMD_SEND_EXTRA_BYTES));
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
#endif /* (XPAR_XISF_FLASH_FAMILY == ATMEL) */

	return Status;
}

/*****************************************************************************/
/**
*
* This function first erases a page and then writes data from the specified
* internal SRAM buffer to the specified locations in the Serial Flash.
*
* @param	InstancePtr is a pointer to the XIsf instance.
* @param	BufferNum specifies the internal SRAM Buffer, from which the
*		data needs to be written to the Serial Flash. The valid values
*		are XISF_PAGE_BUFFER1 or XISF_PAGE_BUFFER2. XISF_PAGE_BUFFER2 is
*		not valid in the case of Atmel AT45DB011D Serial Flash as it
*		contains a single buffer.
* @param	Address is the starting address in the Serial Flash where
*		the data has to be written. Byte address in this address is
*		ignored	as an entire Page is transferred using this API.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note
*		- A minimum of one Page and a maximum of one Page can be written
*		using this function.
*		- This operation is only supported for Atmel Serial Flash.
*
******************************************************************************/
static int BufferToFlashWriteWithErase(XIsf *InstancePtr, u8 BufferNum,
					u32 Address)
{
	int Status = XST_FAILURE;

#if (XPAR_XISF_FLASH_FAMILY == ATMEL)
	/*
	 * Check whether the buffer number is valid or not.
	 */
	if ((BufferNum == XISF_PAGE_BUFFER1) ||
		(BufferNum == XISF_PAGE_BUFFER2)) {
		if ((InstancePtr->DeviceCode  == XISF_ATMEL_DEV_AT45DB011D) &&
			(BufferNum != XISF_PAGE_BUFFER1)) {
			return XST_FAILURE;
		}
	}
	else {
		return XST_FAILURE;
	}

	if (BufferNum == XISF_PAGE_BUFFER1) {
		/*
		 * Buffer 1 to Page Program With Erase.
		 */
		InstancePtr->WriteBufPtr[BYTE1] =
				XISF_CMD_ERASE_BUF1TOPAGE_WRITE;
	} else {
		/*
		 * Buffer 2 to Page Program With Erase.
		 */
		InstancePtr->WriteBufPtr[BYTE1] =
			XISF_CMD_ERASE_BUF2TOPAGE_WRITE;
	}
	InstancePtr->WriteBufPtr[BYTE2] = (u8) (Address >> XISF_ADDR_SHIFT16);
	InstancePtr->WriteBufPtr[BYTE3] = (u8) (Address >> XISF_ADDR_SHIFT8);
	InstancePtr->WriteBufPtr[BYTE4] = (u8) (XISF_DUMMYBYTE);

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
* This function writes data from the specified internal SRAM buffer to the
* specified locations in the Serial Flash.
*
* @param	InstancePtr is a pointer to the XIsf instance.
* @param	BufferNum specifies the internal SRAM Buffer, from which the
*		data needs to be written to the Serial Flash. The valid values
*		are XISF_PAGE_BUFFER1 or XISF_PAGE_BUFFER2. XISF_PAGE_BUFFER2 is
*		not valid in the case of Atmel AT45DB011D Serial Flash as it
*		contains a single buffer.
* @param	Address is the starting address in the Serial Flash where
*		data has to be written. Byte address in this address will be
*		ignored as an entire page of data is transferred using this
*		operation.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
*		- A minimum of one Page and a maximum of one Page can be written
*		using this function.
*		- This operation is only supported for Atmel Serial Flash.
*
******************************************************************************/
static int BufferToFlashWriteWithoutErase(XIsf *InstancePtr, u8 BufferNum,
					u32 Address)
{
	int Status = XST_FAILURE;

#if (XPAR_XISF_FLASH_FAMILY == ATMEL)
	/*
	 * Check whether the buffer number is valid or not.
	 */
	if ((BufferNum == XISF_PAGE_BUFFER1) ||
		(BufferNum == XISF_PAGE_BUFFER2)) {
		if ((InstancePtr->DeviceCode == XISF_ATMEL_DEV_AT45DB011D) &&
			(XISF_PAGE_BUFFER1 != 1)) {
			return XST_FAILURE;
		}
	}
	else {
		return XST_FAILURE;
	}

	if (BufferNum == XISF_PAGE_BUFFER1) {
		/*
		 * Buffer 1 to Page Program Without Erase.
		 */
		InstancePtr->WriteBufPtr[BYTE1] = XISF_CMD_BUF1TOPAGE_WRITE;
	}
	else {
		/*
		 * Buffer 2 to Page Program Without Erase.
		 */
		InstancePtr->WriteBufPtr[BYTE1] = XISF_CMD_BUF2TOPAGE_WRITE;
	}

	InstancePtr->WriteBufPtr[BYTE2] = (u8) (Address >> XISF_ADDR_SHIFT16);
	InstancePtr->WriteBufPtr[BYTE3] = (u8) (Address >> XISF_ADDR_SHIFT8);
	InstancePtr->WriteBufPtr[BYTE4] = (u8) (XISF_DUMMYBYTE);

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
* This function writes data to the Status Register of the Serial Flash.
*
* @param	InstancePtr is a pointer to the XIsf instance.
* @param	SRData is the value to be written to the Status Register
*		of the Serial Flash.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note		This operation is only supported in Intel, STM, Winbond and
*		Spansion Serial Flash. This is the write of Status Register 1
*		for Winbond devices, write of Status Register 2 is handled by
*		WriteSR2.
*
******************************************************************************/
static int WriteSR(XIsf *InstancePtr, u8 SRData)
{
	int Status = XST_FAILURE;

#if ((XPAR_XISF_FLASH_FAMILY == INTEL) || (XPAR_XISF_FLASH_FAMILY == STM) || \
    (XPAR_XISF_FLASH_FAMILY == WINBOND) || (XPAR_XISF_FLASH_FAMILY == SPANSION) \
	|| (XPAR_XISF_FLASH_FAMILY == SST))
	/*
	 * Prepare the Write Buffer.
	 */
	InstancePtr->WriteBufPtr[BYTE1] = XISF_CMD_STATUSREG_WRITE;
	InstancePtr->WriteBufPtr[BYTE2] = SRData;

	/*
	 * Initiate the Transfer.
	 */
	Status = XIsf_Transfer(InstancePtr, InstancePtr->WriteBufPtr, NULL,
						XISF_STATUS_RDWR_BYTES);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
#endif /* ((XPAR_XISF_FLASH_FAMILY==INTEL) || (XPAR_XISF_FLASH_FAMILY==STM) \\
	   (XPAR_XISF_FLASH_FAMILY == WINBOND) ||
	   (XPAR_XISF_FLASH_FAMILY == SPANSION)) */

	return Status;
}

/*****************************************************************************/
/**
*
* This function writes data to the Status Register of the Serial Flash. This API
* should be used to write to the 16 bit status register in Winbond Quad Flash
* (W25QXX).
*
* @param	InstancePtr is a pointer to the XIsf instance.
* @param	SRData is of type (u8*) and points to the 16 bit value to be
*		written to the Status Register of the Serial Flash.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note		This operation is only supported in Winbond (W25QXX) Serial
*		Flash.
*
******************************************************************************/
static int WriteSR2(XIsf *InstancePtr, u8 *SRData)
{
	int Status = XST_FAILURE;

#if (XPAR_XISF_FLASH_FAMILY == WINBOND)
	/*
	 * Prepare the Write Buffer.
	 */
	InstancePtr->WriteBufPtr[BYTE1] = XISF_CMD_STATUSREG_WRITE;
	InstancePtr->WriteBufPtr[BYTE2] = *SRData++;
	InstancePtr->WriteBufPtr[BYTE3] = *SRData;

	/*
	 * Initiate the Transfer.
	 */
	Status = XIsf_Transfer(InstancePtr, InstancePtr->WriteBufPtr, NULL,
						XISF_STATUS_RDWR_BYTES + 1);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
#endif /* (XPAR_XISF_FLASH_FAMILY == WINBOND) */

	return Status;
}

/*****************************************************************************/
/**
*
* This function writes one byte of data to the OTP area in the Serial Flash.
*
* @param	InstancePtr is a pointer to the XIsf instance.
* @param	Address is the address in the OTP area, where to write the data.
* @param	BufferPtr is the pointer to the data to be written into OTP
*		region of Serial Flash.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note
*		- A minimum of one byte and a maximum of one byte can be
*		written using this function.
*		- This operation is supported only for Intel Serial Flash.
*
******************************************************************************/
static int WriteOTPData(XIsf *InstancePtr, u32 Address, const u8 *BufferPtr)
{
	int Status = XST_FAILURE;

#if (XPAR_XISF_FLASH_FAMILY == INTEL)
	if (BufferPtr == NULL) {
		return XST_FAILURE;
	}

	InstancePtr->WriteBufPtr[BYTE1] = XISF_CMD_OTP_WRITE;
	InstancePtr->WriteBufPtr[BYTE2] = (u8) (Address >> XISF_ADDR_SHIFT16);
	InstancePtr->WriteBufPtr[BYTE3] = (u8) (Address >> XISF_ADDR_SHIFT8);
	InstancePtr->WriteBufPtr[BYTE4] = (u8) Address;
	InstancePtr->WriteBufPtr[BYTE5] = *BufferPtr;

	/*
	 * Initiate the Transfer.
	 */
	Status = XIsf_Transfer(InstancePtr, InstancePtr->WriteBufPtr, NULL,
					XISF_OTP_RDWR_EXTRA_BYTES);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
#endif /* (XPAR_XISF_FLASH_FAMILY == INTEL) */

	return Status;
}
