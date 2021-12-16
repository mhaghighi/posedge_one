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
* @file xilisf_read.c
*
* This file contains the library functions to read data from the Serial Flash
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
*
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "include/xilisf.h"

/************************** Constant Definitions *****************************/

#define FAST_READ_NUM_DUMMY_BYTES	1

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

extern int XIsf_Transfer(XIsf *InstancePtr, u8 *WritePtr, u8* ReadPtr,
			 u32 ByteCount);
static int ReadData(XIsf *InstancePtr, u32 Address, u8 *ReadPtr, u32 ByteCount);
static int FastReadData(XIsf *InstancePtr, u8 Command, u32 Address, u8 *ReadPtr,
			u32 ByteCount, int NumDummyBytes);
static int FlashToBufTransfer(XIsf *InstancePtr, u8 BufferNum, u32 Address);
static int BufferRead(XIsf *InstancePtr, u8 BufferNum, u8 *ReadPtr,
			u32 ByteOffset, u32 NumBytes);
static int FastBufferRead(XIsf *InstancePtr, u8 BufferNum, u8 *ReadPtr,
			  u32 ByteOffset, u32 NumBytes);
static int ReadOTPData(XIsf *InstancePtr, u32 Address, u8 *ReadPtr,
			u32 ByteCount);

/************************** Variable Definitions *****************************/

/************************** Function Definitions ******************************/

/*****************************************************************************/
/**
*
* This API reads the data from the Serial Flash.
*
* @param	InstancePtr is a pointer to the XIsf instance.
* @param	Operation is the type of the read operation to be performed on
*		the Serial Flash.
*		The different operations are
		- XISF_READ: Normal Read
*		- XISF_FAST_READ: Fast Read
*		- XISF_PAGE_TO_BUF_TRANS: Page to Buffer Transfer
*		- XISF_BUFFER_READ: Buffer Read
*		- XISF_FAST_BUFFER_READ: Fast Buffer Read
*		- XISF_OTP_READ: One Time Programmable Area (OTP) Read
*		- XISF_DUAL_OP_FAST_READ: Dual Output Fast Read
*		- XISF_DUAL_IO_FAST_READ: Dual Input/Output Fast Read
*		- XISF_QUAD_OP_FAST_READ: Quad Output Fast Read
*		- XISF_QUAD_IO_FAST_READ: Quad Input/Output Fast Read
* @param	OpParamPtr is the pointer to structure variable which contains
*		operational parameter of specified Operation. This parameter
*		type is dependant on the type of Operation to be performed.
*
*		- Normal Read (XISF_READ), Fast Read (XISF_FAST_READ),
*		One Time Programmable Area Read(XISF_OTP_READ), Dual Output Fast
*		Read (XISF_CMD_DUAL_OP_FAST_READ), Dual Input/Output Fast Read
*		(XISF_CMD_DUAL_IO_FAST_READ), Quad Output Fast Read
*		(XISF_CMD_QUAD_OP_FAST_READ) and Quad Input/Output Fast Read
*		(XISF_CMD_QUAD_IO_FAST_READ):
*		The OpParamPtr must be of type struct XIsf_ReadParam.
*		OpParamPtr->Address is start address in the Serial Flash.
*		OpParamPtr->ReadPtr is a pointer to the memory where the data
*		read from the Serial Flash is stored.
*		OpParamPtr->NumBytes is number of bytes to read.
*		OpParamPtr->NumDummyBytes is the number of dummy bytes to be
*		transmitted for the Read command. This parameter is only used
*		in case of Dual and Quad reads.
*		Normal Read and Fast Read operations are supported for Atmel,
*		Intel, STM, Winbond and Spansion Serial Flash.
*		Dual and quad reads are supported for Winbond (W25QXX), Numonyx
*		(N25QXX) and Spansion (S25FL129) quad flash.
*		OTP Read operation is only supported in Intel Serial Flash.
*
*		- Page To Buffer Transfer (XISF_PAGE_TO_BUF_TRANS):
*		The OpParamPtr must be of type struct
*		XIsf_FlashToBufTransferParam .
*		OpParamPtr->BufferNum specifies the internal SRAM Buffer of
*		the Serial Flash. The valid values are XISF_PAGE_BUFFER1
*		or XISF_PAGE_BUFFER2. XISF_PAGE_BUFFER2 is not valid in the case
*		of AT45DB011D Flash as it contains a single buffer.
*		OpParamPtr->Address is start address in the Serial Flash.
*		This operation is only supported in Atmel Serial Flash.
*
*		- Buffer Read (XISF_BUFFER_READ) and Fast Buffer Read
*		(XISF_FAST_BUFFER_READ):
*		The OpParamPtr must be of type struct XIsf_BufferReadParam.
*		OpParamPtr->BufferNum specifies the internal SRAM Buffer of
*		the Serial Flash. The valid values are XISF_PAGE_BUFFER1
*		or XISF_PAGE_BUFFER2. XISF_PAGE_BUFFER2 is not valid in case of
*		AT45DB011D Flash as it contains a single buffer.
*		OpParamPtr->ReadPtr is pointer to the memory where the data read
*		from the SRAM buffer is to be stored.
*		OpParamPtr->ByteOffset is byte offset in the SRAM buffer from
*		where the first byte is read.
*		OpParamPtr->NumBytes is the number of bytes to be read from the
*		Buffer.
*		These operations are supported only in Atmel Serial Flash.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note
*		- Application must fill the structure elements of the third
*		argument and pass its pointer by type casting it with void
*		pointer.
*		- The valid data is available from the fourth location pointed
*		to by the ReadPtr for Normal Read and Buffer Read operations.
*		- The valid data is available from the fifth location pointed to
*		by the ReadPtr for Fast Read, Fast Buffer Read and OTP Read
*		operations.
*		- The valid data is available from the (4 + NumDummyBytes)th
*		location pointed to by ReadPtr for Dual/Quad Read operations.
*
******************************************************************************/
int XIsf_Read(XIsf *InstancePtr, XIsf_ReadOperation Operation, void *OpParamPtr)
{
	int Status = XST_FAILURE;
	XIsf_ReadParam *ReadParamPtr;
	XIsf_FlashToBufTransferParam *FlashToBufTransferParamPtr;
	XIsf_BufferReadParam *BufferReadParamPtr;

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
		case XISF_READ:
			ReadParamPtr = (XIsf_ReadParam*) OpParamPtr;
			Status = ReadData(InstancePtr,
					ReadParamPtr->Address,
					ReadParamPtr->ReadPtr,
					ReadParamPtr->NumBytes);
			break;

		case XISF_FAST_READ:
			ReadParamPtr = (XIsf_ReadParam*) OpParamPtr;
			Status = FastReadData(InstancePtr,
					XISF_CMD_FAST_READ,
					ReadParamPtr->Address,
					ReadParamPtr->ReadPtr,
					ReadParamPtr->NumBytes,
					FAST_READ_NUM_DUMMY_BYTES);
			break;

		case XISF_PAGE_TO_BUF_TRANS:
			FlashToBufTransferParamPtr =
				(XIsf_FlashToBufTransferParam*) OpParamPtr;
			Status = FlashToBufTransfer(InstancePtr,
					FlashToBufTransferParamPtr->BufferNum,
					FlashToBufTransferParamPtr->Address);
			break;

		case XISF_BUFFER_READ:
			BufferReadParamPtr = (XIsf_BufferReadParam*) OpParamPtr;
			Status = BufferRead(InstancePtr,
					BufferReadParamPtr->BufferNum,
					BufferReadParamPtr->ReadPtr,
					BufferReadParamPtr->ByteOffset,
					BufferReadParamPtr->NumBytes);
			break;

		case XISF_FAST_BUFFER_READ:
			BufferReadParamPtr = (XIsf_BufferReadParam*) OpParamPtr;
			Status = FastBufferRead(InstancePtr,
					BufferReadParamPtr->BufferNum,
					BufferReadParamPtr->ReadPtr,
					BufferReadParamPtr->ByteOffset,
					BufferReadParamPtr->NumBytes);
			break;

		case XISF_OTP_READ:
			ReadParamPtr = (XIsf_ReadParam*) OpParamPtr;
			Status = ReadOTPData(InstancePtr,
					ReadParamPtr->Address,
					ReadParamPtr->ReadPtr,
					ReadParamPtr->NumBytes);
			break;

#if ((XPAR_XISF_FLASH_FAMILY == WINBOND) || (XPAR_XISF_FLASH_FAMILY == STM) || \
     (XPAR_XISF_FLASH_FAMILY == SPANSION))
		case XISF_DUAL_OP_FAST_READ:
			ReadParamPtr = (XIsf_ReadParam*) OpParamPtr;
			Status = FastReadData(InstancePtr,
					XISF_CMD_DUAL_OP_FAST_READ,
					ReadParamPtr->Address,
					ReadParamPtr->ReadPtr,
					ReadParamPtr->NumBytes,
					ReadParamPtr->NumDummyBytes);
			break;

		case XISF_DUAL_IO_FAST_READ:
			ReadParamPtr = (XIsf_ReadParam*) OpParamPtr;
			Status = FastReadData(InstancePtr,
					XISF_CMD_DUAL_IO_FAST_READ,
					ReadParamPtr->Address,
					ReadParamPtr->ReadPtr,
					ReadParamPtr->NumBytes,
					ReadParamPtr->NumDummyBytes);
			break;

		case XISF_QUAD_OP_FAST_READ:
			ReadParamPtr = (XIsf_ReadParam*) OpParamPtr;
			Status = FastReadData(InstancePtr,
					XISF_CMD_QUAD_OP_FAST_READ,
					ReadParamPtr->Address,
					ReadParamPtr->ReadPtr,
					ReadParamPtr->NumBytes,
					ReadParamPtr->NumDummyBytes);
			break;

		case XISF_QUAD_IO_FAST_READ:
			ReadParamPtr = (XIsf_ReadParam*) OpParamPtr;
			Status = FastReadData(InstancePtr,
					XISF_CMD_QUAD_IO_FAST_READ,
					ReadParamPtr->Address,
					ReadParamPtr->ReadPtr,
					ReadParamPtr->NumBytes,
					ReadParamPtr->NumDummyBytes);
			break;
#endif /*((XPAR_XISF_FLASH_FAMILY == WINBOND) ||
	  (XPAR_XISF_FLASH_FAMILY == STM) ||
	  (XPAR_XISF_FLASH_FAMILY == SPANSION))*/

		default:
			break;
	}

	return Status;
}

/*****************************************************************************/
/**
*
* This function reads data from the Serial Flash.
*
* @param	InstancePtr is a pointer to the XIsf instance.
* @param	Address is the starting address in the Serial Flash from where
*		the data is to be read.
* @param	ReadPtr is a pointer to the memory where the data read from
*		the Serial Flash is stored.
* @param	ByteCount is the number of bytes to be read from the Serial
*		Flash.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note
*		- This operation is supported for Atmel, Intel, STM, Winbond
*		  and Spansion Serial Flash.
*		- Minimum of one byte and a maximum of an entire Serial Flash
*		Array can be read.
*		- The valid data is available from the fourth location pointed
*		to by the ReadPtr.
*
******************************************************************************/
static int ReadData(XIsf *InstancePtr, u32 Address, u8 *ReadPtr, u32 ByteCount)
{
	int Status;

	if (ByteCount <= 0 ) {
		return XST_FAILURE;
	}

	if (ReadPtr == NULL) {
		return XST_FAILURE;
	}

	ReadPtr[BYTE1] = XISF_CMD_RANDOM_READ;
	ReadPtr[BYTE2] = (u8) (Address >> XISF_ADDR_SHIFT16);
	ReadPtr[BYTE3] = (u8) (Address >> XISF_ADDR_SHIFT8);
	ReadPtr[BYTE4] = (u8) Address;

	/*
	 * Initiate the Transfer.
	 */
	Status = XIsf_Transfer(InstancePtr, ReadPtr, ReadPtr,
				ByteCount + XISF_CMD_SEND_EXTRA_BYTES);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function reads data from the Serial Flash at a higher speed than normal
* Read operation.
*
* @param	InstancePtr is a pointer to the XIsf instance.
* @param	Command is the fast read command used to read data from the
*		flash. It could be one of XISF_CMD_DUAL/QUAD_*_FAST_READ or
*		XISF_CMD_FAST_READ.
* @param	Address is the starting address in the Serial Flash from where
*		the data is to be read.
* @param	ReadPtr is a pointer to the memory where the data read from
*		the Serial Flash is stored.
* @param	ByteCount is the number of bytes to be read from the Serial
*		Flash.
* @param	NumDummyBytes is the number of dummy bytes associated with the
*		fast read commands.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note
*		- XISF_CMD_FAST_READ operation is supported for Atmel, Intel,
*		  STM, Winbond and Spansion Serial Flash.
*		- XISF_CMD_DUAL/QUAD_*_FAST_READ operations are supported on
*		  Winbond (W25QXX), Numonyx (N25QXX) and Spansion (S25FL129)
*		  quad flash devices.
*		- Minimum of one byte and a maximum of an entire Serial Flash
*		  Array can be read.
*		- The valid data is available from the (4 + NumDummyBytes)th
*		  location pointed to by the ReadPtr.
*
******************************************************************************/
static int FastReadData(XIsf *InstancePtr, u8 Command, u32 Address, u8 *ReadPtr,
			u32 ByteCount, int NumDummyBytes)
{
	int Status;
	int Index;

	if (ByteCount <= 0 ) {
		return XST_FAILURE;
	}

	if (ReadPtr == NULL) {
		return XST_FAILURE;
	}

	if (NumDummyBytes <= 0) {
		return XST_FAILURE;
	}

	ReadPtr[BYTE1] = Command;
	ReadPtr[BYTE2] = (u8) (Address >> XISF_ADDR_SHIFT16);
	ReadPtr[BYTE3] = (u8) (Address >> XISF_ADDR_SHIFT8);
	ReadPtr[BYTE4] = (u8) Address;

	for (Index = 0; Index < NumDummyBytes; Index++) {
		ReadPtr[Index + BYTE5] = (u8) (XISF_DUMMYBYTE);
	}

	/*
	 * Initiate the Transfer.
	 */
	Status = XIsf_Transfer(InstancePtr, ReadPtr, ReadPtr,
				ByteCount + NumDummyBytes +
				XISF_CMD_SEND_EXTRA_BYTES);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function copies the data from the Serial Flash to the specified SRAM
* buffer.
*
* @param	InstancePtr is a pointer to the XIsf instance.
* @param	BufferNum specifies the internal SRAM Buffer to which the data
*		from the Serial Flash is to be transferred. The valid values are
*		XISF_PAGE_BUFFER1 or XISF_PAGE_BUFFER2. XISF_PAGE_BUFFER2 is not
*		valid in the case of AT45DB011D Flash as it contains a single
*		buffer.
* @param	Address specifies any address within the Page of the Serial
*		Flash from where the Page of data is to be copied.
*		Byte address in this Address is ignored as an entire Page of
*		data is transferred/copied.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note
*		- This operation is only supported in Atmel Serial Flash.
*		- This function reads one complete Page from the Serial Flash.
*		- Read the Spartan-3AN In-system Flash User Guide/Atmel
*		  AT45XXXD Data sheets for more information.
*
******************************************************************************/
static int FlashToBufTransfer(XIsf *InstancePtr, u8 BufferNum, u32 Address)
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
	} else {
		return XST_FAILURE;
	}

	if (BufferNum == XISF_PAGE_BUFFER1) {
		/*
		 * Page to Buffer 1 Transfer.
		 */
		InstancePtr->WriteBufPtr[BYTE1] =
			XISF_CMD_PAGETOBUF1_TRANS;
	} else {
		/*
		 * Page to Buffer 2 Transfer.
		 */
		InstancePtr->WriteBufPtr[BYTE1] =
			XISF_CMD_PAGETOBUF2_TRANS;
	}

	InstancePtr->WriteBufPtr[BYTE2] = (u8)(Address >> XISF_ADDR_SHIFT16);
	InstancePtr->WriteBufPtr[BYTE3] = (u8)(Address >> XISF_ADDR_SHIFT8);
	InstancePtr->WriteBufPtr[BYTE4] = (u8)(XISF_DUMMYBYTE);

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
* This function reads the data available in the SRAM buffer of the Serial Flash.
*
* @param	InstancePtr is a pointer to the XIsf instance.
* @param	BufferNum specifies the internal SRAM Buffer from which the data
*		is to be read. The valid values are XISF_PAGE_BUFFER1 or
*		XISF_PAGE_BUFFER2. XISF_PAGE_BUFFER2 is not valid in the case of
*		AT45DB011D Flash as it contains a single buffer.
* @param	ReadPtr is a pointer to the memory where the data read from the
*		SRAM buffer is stored.
* @param	ByteOffset is the byte offset in the buffer from where the
*		first byte is read.
* @param	NumBytes is the number of bytes to be read from the Buffer.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note
*		- This operation is only supported in Atmel Serial Flash.
*		- This function reads a Minimum of one Byte and a Maximum of an
*		entire SRAM buffer (1 Page) from the Serial Flash.
*		- The valid data is available from the fourth location pointed
*		to by the ReadPtr.
*		- Read the Spartan-3AN In-system Flash User Guide/Atmel
*		AT45XXXD Data sheets for more information.
*
******************************************************************************/
static int BufferRead(XIsf *InstancePtr, u8 BufferNum, u8 *ReadPtr,
			u32 ByteOffset, u32 NumBytes)
{
	int Status = XST_FAILURE;

#if (XPAR_XISF_FLASH_FAMILY == ATMEL)

	/*
	 * Check if the buffer number is valid or not.
	 */
	if ((BufferNum == XISF_PAGE_BUFFER1) ||
			(BufferNum == XISF_PAGE_BUFFER2)) {
		if ((InstancePtr->DeviceCode  == XISF_ATMEL_DEV_AT45DB011D) &&
			(BufferNum != XISF_PAGE_BUFFER1)) {
			return XST_FAILURE;
		}
	} else {
		return XST_FAILURE;
	}

	if (ReadPtr == NULL) {
		return XST_FAILURE;
	}

	if (ByteOffset > InstancePtr->BytesPerPage){
		return XST_FAILURE;
	}

	if ((NumBytes <= 0) || (NumBytes > InstancePtr->BytesPerPage)) {
		return XST_FAILURE;
	}

	if (BufferNum == XISF_PAGE_BUFFER1) {
		ReadPtr[BYTE1] = XISF_CMD_BUF1_READ; /* Buffer 1 Read. */
	} else {
		ReadPtr[BYTE1] = XISF_CMD_BUF2_READ; /* Buffer 2 Read.*/
	}
	ReadPtr[BYTE2] = (u8) (0x00);
	ReadPtr[BYTE3] = (u8) (ByteOffset >> XISF_ADDR_SHIFT8);
	ReadPtr[BYTE4] = (u8) ByteOffset;

	/*
	 * Initiate the Transfer.
	 */
	Status = XIsf_Transfer(InstancePtr, ReadPtr, ReadPtr,
				NumBytes + XISF_CMD_SEND_EXTRA_BYTES);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
#endif /* (XPAR_XISF_FLASH_FAMILY == ATMEL) */

	return Status;

}
/*****************************************************************************/
/**
*
* This function reads the data from the internal SRAM page buffer of the Serial
* Flash memory at higher speed than normal Buffer Read operation.
*
* @param	InstancePtr is a pointer to the XIsf instance.
* @param	BufferNum specifies the internal SRAM Buffer from which the data
*		is to be read. The valid values are XISF_PAGE_BUFFER1 or
*		XISF_PAGE_BUFFER2. XISF_PAGE_BUFFER2 is not valid in the case of
*		AT45DB011D Flash as it contains a single buffer.
* @param	ReadPtr is a pointer to the memory where the data read from the
*		SRAM buffer is stored.
* @param	ByteOffset is the byte offset in the buffer from where the
*		first byte is read.
* @param	NumBytes is the number of bytes to be read from the Buffer.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note
*		- This operation is only supported in Atmel Serial Flash.
*		- This function reads a Minimum of one Byte and a Maximum of an
*		entire SRAM buffer (1 Page) from the Serial Flash.
*		- The valid data is available from the fifth location pointed
*		to by the ReadPtr.
*		- Read the Spartan-3AN In-system Flash User Guide/Atmel
*		AT45XXXD Data sheets for more information.
*
******************************************************************************/
static int FastBufferRead(XIsf *InstancePtr, u8 BufferNum, u8 *ReadPtr,
				u32 ByteOffset, u32 NumBytes)
{
	int Status = XST_FAILURE;

#if (XPAR_XISF_FLASH_FAMILY == ATMEL)
	/*
	 * Check if the buffer number is valid or not.
	 */
	if ((BufferNum == XISF_PAGE_BUFFER1) ||
			(BufferNum == XISF_PAGE_BUFFER2)) {
		if ((InstancePtr->DeviceCode  == XISF_ATMEL_DEV_AT45DB011D) &&
			(BufferNum != XISF_PAGE_BUFFER1)) {
			return XST_FAILURE;
		}
	} else {
		return XST_FAILURE;
	}

	if (ReadPtr == NULL) {
		return XST_FAILURE;
	}

	if (ByteOffset > InstancePtr->BytesPerPage){
		return XST_FAILURE;
	}

	if ((NumBytes <= 0) || (NumBytes > InstancePtr->BytesPerPage)) {
		return XST_FAILURE;
	}

	if (BufferNum == XISF_PAGE_BUFFER1) {
		/*
		 * Buffer 1 Fast Read.
		 */
		ReadPtr[BYTE1] = XISF_CMD_FAST_BUF1_READ;
	} else {
		/*
		 * Buffer 2 Fast Read.
		 */
		ReadPtr[BYTE1] = XISF_CMD_FAST_BUF2_READ;
	}

	ReadPtr[BYTE2] = (u8) (0x00);
	ReadPtr[BYTE3] = (u8) (ByteOffset >> XISF_ADDR_SHIFT8);
	ReadPtr[BYTE4] = (u8) ByteOffset;
	ReadPtr[BYTE5] = (u8) (XISF_DUMMYBYTE);

	/*
	 * Initiate the Transfer.
	 */
	Status = XIsf_Transfer(InstancePtr, ReadPtr, ReadPtr,
			NumBytes + XISF_CMD_FAST_READ_EXTRA_BYTES);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
#endif /* (XPAR_XISF_FLASH_FAMILY == ATMEL) */

	return Status;
}

/*****************************************************************************/
/**
*
* This function reads the data from OTP area of the Serial Flash.
*
* @param	InstancePtr is a pointer to the XIsf instance.
* @param	Address is the starting address in OTP area of the Serial Flash
*		from which the data is to be read.
* @param	ReadPtr is a pointer to the memory where the data read from the
*		Serial Flash is stored.
* @param	ByteCount is the number of bytes to be read from the Serial
*		Flash.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note
*		- This operation is only supported for Intel Serial Flash.
*		- Minimum of one byte and a maximum of an entire Serial Flash
*		  array can be read.
******************************************************************************/
static int ReadOTPData(XIsf *InstancePtr, u32 Address, u8 *ReadPtr,
			u32 ByteCount)
{
	int Status = XST_FAILURE;

#if (XPAR_XISF_FLASH_FAMILY == INTEL)
	if (ByteCount <= 0 ) {
		return XST_FAILURE;
	}

	if (ReadPtr == NULL) {
		return XST_FAILURE;
	}

	ReadPtr[BYTE1] = XISF_CMD_OTP_READ;
	ReadPtr[BYTE2] = (u8) (Address >> XISF_ADDR_SHIFT16);
	ReadPtr[BYTE3] = (u8) (Address >> XISF_ADDR_SHIFT8);
	ReadPtr[BYTE4] = (u8) Address;
	ReadPtr[BYTE5] = (u8) (XISF_DUMMYBYTE);


	/*
	 * Initiate the Transfer.
	 */
	Status = XIsf_Transfer(InstancePtr, ReadPtr, ReadPtr,
				ByteCount + XISF_OTP_RDWR_EXTRA_BYTES);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
#endif /* (XPAR_XISF_FLASH_FAMILY == INTEL) */

	return Status;
}
