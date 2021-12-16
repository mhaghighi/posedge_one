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
* @file xilisf.h
*
* The Xilinx In-system and Serial Flash (XilIsf) Library supports the Xilinx
* In-system Flash and, external Serial Flash Memories from Atmel (AT45XXXD),
* Intel (S33), ST Microelectronics (STM) (M25PXX), Winbond (W25QXX/W25XX),
* Numonyx (N25QXX) devices. Intel (S33) and STM (M25PXX) Serial Flash devices
* are now a part of Serial Flash devices provided by Numonyx.
*
* <b>This library also supports the Spansion (S25FLXX) devices, but this family
* hasn't been tested. The support for this family of devices is limited to the
* common commands supported by the other flash families</b>
*
* The following instructions are not supported in WinBond (W25QXX/W25XX) -
* Block Erase 32KB, Erase Suspend/Resume, Mode Bit Reset, Read Unique ID,
* and Read Manufacturer/Device ID.
*
* The following instructions are not supported in Numonyx (N25QXX)- Erase
* Suspend/Resume, Read/Write Volatile/Non-volatile configuration register.
*
* <b>Library Description</b>
*
* The library enables higher layer software (e.g. an application) to communicate
* with the Serial Flash.
*
* The library allows the user to Write, Read and Erase the Serial Flash.
* The user can also protect the data stored in the Serial Flash from unwarranted
* modification by enabling the Sector Protection feature. User can also perform
* different Control operations on Intel, STM (Numonyx), Winbond and Spansion
* Serial Flash devices.
*
* The library supports interrupt driven mode and polled mode based on the
* mode in which the Spi driver is configured by the user.
*
* - Polled Mode of operation: All the APIs are blocking in this mode.
* - Interrupt mode of operation: It is the application's responsibility to
* acknowledge the associated Interrupt Controller's interrupts.
* The transfer is initiated and the control is given back to the user
* application. The user application has to keep track of whether the initiated
* operation is completed successfully.
*
* This library can support multiple instances of Serial Flash at a time,
* provided they are of the same device family (either Atmel, Intel, STM or
* Spansion) as the device family is selected at compile time.
*
* <b>Device Operation</b>
*
* The Serial Flash operates as a slave device on the SPI bus, with Xilinx SPI
* core operating as the Master. The library uses XSpi driver for communicating
* with the Serial Flash.
*
* <b>Device Geometry</b>
*
* - Atmel (AT45XXXD)/Xilinx ISF:
* The Atmel Serial Flash is divided into Sectors. Each Sector consists of
* multiple Blocks. Each Block contains multiple Pages. Each Page contains
* multiple Bytes. The Number of Sectors, Blocks Per Sector, Pages Per Block and
* Bytes Per Page vary for different devices within this family.
* There are two addressing modes supported by the Atmel Serial Flash:
*	- Default-Addressing Mode.
*	- Power-Of-2 Addressing mode.
*
* In Default Addressing mode the Atmel Serial Flash contains approximately 3%
* more Addressing memory than the Power-Of-2 addressing mode. The addressing
* mode of the Atmel Serial Flash can be known by reading the Device Status
* Register The ISF in the Xilinx devices is in Default-Addressing mode by
* default.
*
* The following Atmel flash memories are supported by this library.
* AT45DB011D		AT45DB021D		AT45DB041D
* AT45DB081D		AT45DB161D		AT45DB321D
* AT45DB642D
*
* - Intel (Numonyx) (S33) and STM (Numonyx)(M25PXX):
* The Intel and STM Serial Flash is divided into Sectors. Each Sector consists
* of multiple pages. Each Page contains 256 Bytes. The Number of Sectors
* and Pages Per Sectors vary for different devices within this family.
*
* The following Intel and STM flash memories are supported by this library.
* S3316MBIT		S3332MBIT		S3364MBIT
*
* M25P05_A		M25P10_A		M25P20
* M25P40		M25P80			M25P16
* M25P32		M25P64			M25P128
*
* - Winbond W25QXX/W25XX:
* The Winbond W25QXX/W25XX Serial Flash is divided into Blocks of 64 KB and
* the blocks are divided into sectors. Each Sector consists of multiple pages.
* Each Page contains 256 Bytes. The Number of Blocks and Sectors vary for
* different devices within this family.
* The following instructions are not supported - Block Erase 32KB, Erase
* Suspend/Resume, Mode Bit Reset, Read Unique ID, and Read Manufacturer/Device
* ID.
*
* The following Winbond flash memories are supported by this library.
* W25Q80		W25Q16			W25Q32
* W25Q64		W25Q128			W25X10
* W25X20		W25X40			W25X80
* W25X16		W25X32			W25X64
*
* - Numonyx N25QXX
* The Numonyx N25QXX Serial Flash is divided into sectors of 64 KB and
* the sectors are divided into sub-sectors. Each Sector consists of multiple
* pages. Each Page contains 256 Bytes. The Number of Blocks vary for different
* devices within this family.
* The following instructions are not supported - Erase Suspend/Resume,
* Read/Write Volatile/Non-volatile configuration register.
*
* The following Numonyx flash memories are supported by this library.
* N25Q32		N25Q64			N25Q128
*
* - Spansion S25FL
* The Spansion S25FL Serial Flash is divided into sectors of 64 KB and
* in devices like S25FL128/129, the sectors are divided into sub-sectors.
* Each Sector consists of multiple pages. Each Page contains 256 Bytes. The
* Number of Blocks vary for different devices within this family.
*
* The following Spansion flash memories are supported by this library.
* S25FL004		S25FL008		S25FL016
* S25FL032		S25FL064		S25FL128/129
*
* - Silicon Storage Technology (SST) SST25WF080
* The SST25WF080 Serial Flash is divided into sectors of 4KB. This flash
* doesn't support Page Write commands. Supports only Byte-Write Command.
*
* Support for new parts can be easily added, when they are available from
* vendors.
*
* <b>Library Initialization</b>
*
* The function call XIsf_Initialize() should be called by the application
* before using  any other function in the library. This function will fetch the
* Manufacturer code and Device code and determine the geometry of the Serial
* Flash used.
*
* <b>Write Operations</b>
*
* The XIsf_Write() API is used to write data to the Serial Flash. A maximum
* of a Page of data can be written using this API. Once the user initiates a
* write operation, the Serial Flash takes time to complete the write operation
* internally. The user has to read the Status Register (XIsf_GetStatus) to
* know if the Serial Flash is still busy with a previously initiated operation
* before initiating a new one.
*
* Using the XIsf_Write() API the user can perform several different types of
* write operations as mentioned below:
*
* - Normal Write:
*	Write data to the specified locations in the Serial Flash.
*	This operation is supported in Atmel, Intel, STM, Winbond and Spansion
*	Serial Flash.
*
* - Dual Input Fast Program:
*	This operation is similar to the Normal Write operation, except that
*	the data is transmitted on two lines (DQ0 and DQ1) instead of one.
*	This operation is supported in Numonyx (N25QXX) Quad Serial Flash.
*
* - Dual Input Extended Fast Program:
*	This operation is similar to the Dual Input Fast Program, except that
*	the address is transmitted on two lines (DQ0 and DQ1) instead of one.
*	This operation is supported in Numonyx (N25QXX) Quad Serial Flash.
*
* - Quad Input Fast Program:
*	This operation is similar to the Dual Input Fast Program, except that
*	the data is transmitted on four lines (DQ0 - DQ3) instead of two.
*	This operation is supported in Numonyx (N25QXX), Winbond (W25QXX) and
*	Spansion (S25FL129) Quad Serial Flash.
*
* - Quad Input Extended Fast Program:
*	This operation is similar to the Quad Input Fast Program, except that
*	the address is transmitted on four lines (DQ0 - DQ3) instead of one.
*	This operation is supported in Numonyx (N25QXX) Quad Serial Flash.
*
* - Auto Page Write:
*	Auto rewrite the contents of the page.
*	This operation is supported only for Atmel Serial Flash.
*
* - Buffer Write:
* 	Write data to the internal SRAM buffer of the Serial Flash.
*	This operation is supported only for Atmel Serial Flash.
*
* - Buffer To Memory Write With Erase:
*	Write data from the specified SRAM buffer to a page in the Serial Flash
*	after erasing the page.
*	This operation is supported only for Atmel Serial Flash.
*
* - Buffer To Memory Write Without Erase:
*	Write data from the specified SRAM buffer to a Page in the Serial Flash
*	without erasing the page.
*	This operation is supported only for Atmel Serial Flash.
*
* - Write Status Register:
*	Write to the Status Register of the Serial Flash.
*	This operation is supported only for Intel, STM, Winbond and Spansion
*	Serial Flash.
*
* - Write 2 byte Status Register:
*	Write to the 16-bit Status Register of the Serial Flash.
*	This operation is supported only for Winbond Serial Flash.
*
* - One Time Programmable Area Write:
*	Write one byte of data in to One Time Programmable area.
*	This operation is supported only for Intel Serial Flash.
*
* For Intel, STM (Numonyx), Winbond and Spansion Serial Flash devices, the user
* application must call the XIsf_WriteEnable() API by passing XISF_WRITE_ENABLE
* as an argument before calling the Isf_Write() API.
*
*
* <b>Read Operations</b>
*
* The XIsf_Read() API can be used to read a minimum of one byte and a maximum of
* an entire array of the Serial Flash depending on the type of read operation.
*
* Using the XIsf_Read() API the user can perform several different types of read
* operations as mentioned below:
*
* - Normal Read:
*	Read data from the specified locations in the Serial Flash .
*	This operation is supported for Atmel, Intel, STM, Winbond and Spansion
*	Serial Flash.
*
* - Fast Read:
*	Read a large block of contiguous data from the specified locations of
*	the Serial Flash at a higher speed than the Normal Read.
*	This operation is supported for Atmel, Intel, STM, Winbond and Spansion
*	Serial Flash.
*
* - Dual Output Fast Read:
*	This operation is similar to the Fast Read, except that the data is
*	transmitted on two lines (DQ0 and DQ1) instead of one.
*	This operation is supported in Numonyx (N25QXX), Winbond (W25QXX) and
*	Spansion (S25FL129) Quad Serial Flash.
*
* - Dual Input/Output Fast Read:
*	This operation is similar to the Dual Output Fast Read, except that
*	the address is transmitted on two lines (DQ0 and DQ1) instead of one.
*	This operation is supported in Numonyx (N25QXX), Winbond (W25QXX) and
*	Spansion (S25FL129) Quad Serial Flash.
*
* - Quad Output Fast Read:
*	This operation is similar to the Dual Output Fast Read, except that
*	the data is transmitted on four lines (DQ0 - DQ3) instead of two.
*	This operation is supported in Numonyx (N25QXX), Winbond (W25QXX) and
*	Spansion (S25FL129) Quad Serial Flash.
*
* - Quad Input/Output Fast Read:
*	This operation is similar to the Quad Output Fast Program, except that
*	the address is transmitted on four lines (DQ0 - DQ3) instead of one.
*	This operation is supported in Numonyx (N25QXX), Winbond (W25QXX) and
*	Spansion (S25FL129) Quad Serial Flash.
*
* - Memory To Buffer Transfer:
*	Transfer a page of data from the Serial Flash to the specified
*	internal SRAM buffer of the Serial Flash.
*	This operation is supported only in Atmel Serial Flash.
*
* - Buffer Read:
*	Read data from the specified SRAM internal buffer of the Serial Flash.
*	This operation is supported only in Atmel Serial Flash.
*
* - Fast Buffer Read:
*	Read multiple contiguous bytes from the internal SRAM page buffer of the
*	Serial Flash at a higher speed than normal Buffer Read.
*	This operation is supported only for Atmel Serial Flash.
*
* - One Time Programmable Area Read:
*	Read One Time Programmable area.
* 	This operation is supported only for Intel Serial Flash.
*
* <b>Erase Operations</b>
*
* The XIsf_Erase() API can be used to Erase the contents of the Serial Flash.
* Once the user initiates an Erase operation, the Serial Flash takes time to
* complete the Erase operation internally. The user has to read the Status
* Register to know if the Serial Flash is still busy with a previously initiated
* operation before initiating a new one.
*
* Using the XIsf_Erase() API the user can perform four different types of Erase
* operations as mentioned below :
*
* - Page Erase:
*	Erase one Page of the Serial Flash.
*	This operation is supported only for Atmel Serial Flash.
*
* - Block Erase:
*	Erase one Block of the Serial Flash.
*	This operation is supported for Atmel, Intel, Winbond Serial Flash.
*
* - Sector Erase:
*	Erase one Sector of the Serial Flash.
*	This operation is supported for Atmel, Intel, STM, Spansion and Winbond
*	Serial Flash.
*
* - Bulk Erase:
*	Erase an entire Serial Flash.
*	This operation is supported for Intel, STM, Winbond and Spansion Serial
*	Flash.
*
* For Intel, STM, Winbond and Spansion Serial Flash the user application must
* call the XIsf_WriteEnable() API by passing XISF_WRITE_ENABLE as an argument
* before calling the XIsf_Erase() API.
*
* <b>Sector Protection Operations</b>
*
* The XIsf_SectorProtect() API can be  used to perform Sector Protection related
* operations. The Serial Flash is divided into Sectors. Each Sector or number of
* Sectors can be protected from unwarranted writing/erasing.
*
* Using the XIsf_SectorProtect() API the user can perform five different type of
* operations as given below:
*
* - Sector Protect Register Read:
*	Read Sector Protect Register/Bits in to the buffer provided by user.
*	This operation is supported for Atmel, Intel, STM, Winbond and Spansion
*	Serial Flash.
*
* - Sector Protect Register Write:
*	Write data to the Sector Protect Register/Bits.
*	This operation is supported for Atmel, Intel, STM, Winbond and Spansion
*	Serial Flash.
*
* - Sector Protect Register Erase:
*	Erase the Sector Protect Register.
*	This operation is supported only for Atmel Serial Flash.
*
* - Sector Protect Enable:
*	Enable Sector Protect mode of Serial Flash.
*	This operation is supported only for Atmel Serial Flash.
*
* - Sector Protect Disable:
*	Disable Sector Protect mode of Serial Flash.
*	This operation is supported only for Atmel Serial Flash.
*
* For Intel, STM, Winbond and Spansion Serial Flash the user application must
* call the XIsf_WriteEnable() API by passing XISF_WRITE_ENABLE as an argument
* before calling the XIsf_SectorProtect() API for Sector Protect Register
* Write operation.
*
* <b>Device Control Operations</b>
*
* The XIsf_Ioctl() API can be used to perform control operations on the
* Intel, STM, Winbond and Spansion Serial Flash.
*
* Using the XIsf_Ioctl() API the user can perform several different types of
* operations as given below:
*
* - Release From Deep Power-Down Mode:
*	This operation releases the Serial Flash from Deep Power-Down Mode.
*	This operation is supported for Intel, STM, Winbond and Spansion Serial
*	Flash.
*
* - Enter to Deep Power-Down Mode:
*	This operation puts the Serial Flash in to Deep Power-Down Mode.
*	In this mode all commands except the release from Deep Power-Down Mode
*	command will be ignored.
*	This operation is supported for Intel, STM, Winbond and Spansion Serial
*	Flash.
*
* - Clear Status Register Fail Flag:
*	This operation clears all the fail flags in the Status Register
*	of the Serial Flash.
*	This operation is only supported for Intel Serial Flash.
*
* - High Performance Mode:
*	This instruction must be executed before the dual/quad I/O instructions
*	in Winbond Flash. This instruction is supported only in Winbond (W25QXX)
*	Serial Flash.
*
* <b>Serial Flash Information Read</b>
*
* XIsf_GetDeviceInfo() API is used to read the Joint Electron Device
* Engineering Council (JEDEC) compatible device information.
* This JEDEC information consists of Manufacturer ID, Vendor-Specific Device
* family identifier, Vendor-Specific device identifier for the specified family,
* number of bits stored per memory cell, product version and number of
* additional Extended Device Information bytes.
*
* Read the Spartan-3AN In-system Flash User Guide and the data sheets of
* Atmel-AT45XXXD/STM-M25PXX/Intel-S33/Winbond-W25QXX/W25XX/Spansion-S25FLXX for
* more information.
*
* XIsf_GetStatus() API is used to read the Status Register of the Serial Flash.
* Winbond devices have a Status Register 2 which can be read using the
* XIsf_GetStatusReg2() API.
*
* <b>Write Enable/Disable Operations</b>
*
* For Intel, STM, Winbond and Spansion Serial Flash the user application must
* enable the Write to the Serial Flash by calling XIsf_WriteEnable
* (XISF_WRITE_ENABLE) API before doing any Write operations to the Serial Flash.
* Writing to the Serial Flash is disabled by calling XIsf_WriteEnable
* (XISF_WRITE_DISABLE) API.
*
* @note
*
* This library is intended to be RTOS and processor independent. It works with
* physical addresses only. Any needs for dynamic memory management, threads,
* mutual exclusion, virtual memory or cache control must be satisfied by the
* layer above this driver.
*
* This library supports the Spansion (S25FLXX) devices, but this family hasn't
* been tested. The support for this family of devices is limited to the common
* commands supported by the other flash families.
*
* <pre>
*
* MODIFICATION HISTORY:
*
* Ver   Who      Date     Changes
* ----- -------  -------- -----------------------------------------------
* 1.00a ksu/sdm  03/03/08 First release
* 2.00a ktn      11/27/09 Updated to use HAL processor APIs/definitions
* 2.01a sdm      01/04/10 Added Support for Winbond W25Q80/16/32 devices
* 2.01a sdm      06/17/10 Updated the Tcl to support axi_spi
* 2.03a sdm      04/17/10 Updated to support Winbond memory W25Q128 and added
*			  a list of supported flash memories
*			  Updated the Tcl to support axi_quad_spi
* 2.04a sdm      08/17/10 Updated to support Numonyx (N25QXX) and Spansion
*			  flash memories
* 3.00a srt	 06/20/12 Updated to support interfaces SPI PS and QSPI PS.
*			  New API:
*			  	XIsf_RegisterInterface()
*				XIsf_SetSpiConfiguration()
*				XIsf_SetOperatingMode()
*			  Changed API:
*			 	XIsf_Initialize()
*				XIsf_Transfer()
*			  Added support to SST flash.
* 3.01a srt	 02/06/13 Updated for changes made in QSPIPS driver (CR 698107).
*				      APIs changed:
*					  XQspiPs_PolledTransfer()
*					  XQspiPs_Transfer()
*					  XQspiPs_SetSlaveSelect().
*			  Modified the examples xilisf_spips_sst_intr_example.c
*			  and xilisf_spips_sst_polled_example.c to correct
*			  the flash write, erase and read logic. (CR 703816)
* 3.02a srt	 04/25/13 - Added Bulk Erase command support for SST and 
*			    Spansion flashes (CR 703816 & 711003).
* 			  - Modified SECTOR and BLOCK Erase commands for 
*			    SST flash and updated spips examples.
*			    (CR 703816)
*			  - Updated spips and qspips examples to perform 
*			    Write enable operation in each sector
*   		  	  - Removed compiler errors when not selecting proper
*		      	    interface for Zynq. (CR 716451)
*
* </pre>
*
******************************************************************************/
#ifndef XILISF_H /* prevent circular inclusions */
#define XILISF_H /* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/

#include "xparameters.h"

#ifdef XPAR_XISF_INTERFACE_AXISPI
#include "xspi.h"
#elif XPAR_XISF_INTERFACE_PSSPI
#include "xspips.h"
#elif XPAR_XISF_INTERFACE_PSQSPI
#include "xqspips.h"
#endif

/**
 * The following definitions specify the type of Serial Flash family.
 * Based on the Serial Flash family selected, some part of the code is included
 * or excluded in the In-system and Serial Flash Library.
 */
#define ATMEL		1 /**< Atmel family device */
#define INTEL		2 /**< Intel family device */
#define STM		3 /**< STM family device */
#define WINBOND		4 /**< Winbond family device */
#define SPANSION	5 /**< Spansion family device */
#define SST		6 /**< SST family device */

#if (XPAR_XISF_FLASH_FAMILY == ATMEL)
#include "xilisf_atmel.h"
#endif

#if ((XPAR_XISF_FLASH_FAMILY == INTEL) || (XPAR_XISF_FLASH_FAMILY == STM) || \
    (XPAR_XISF_FLASH_FAMILY == WINBOND) || (XPAR_XISF_FLASH_FAMILY == SPANSION) \
	|| (XPAR_XISF_FLASH_FAMILY == SST))
#include "xilisf_intelstm.h"
#endif

/************************** Constant Definitions *****************************/

/**
 * The following definitions specify the Manufacturer Code for the different
 * families of Serial Flash supported by this library.
 */
#define XISF_MANUFACTURER_ID_ATMEL	0x1F	/**< Atmel device */
#define XISF_MANUFACTURER_ID_INTEL	0x89	/**< Intel device */
#define XISF_MANUFACTURER_ID_STM	0x20	/**< STM device */
#define XISF_MANUFACTURER_ID_WINBOND	0xEF	/**< Winbond device */
#define XISF_MANUFACTURER_ID_SPANSION	0x01	/**< Spansion device */
#define XISF_MANUFACTURER_ID_SST	0xBF	/**< SST device */

/*
 * Interrupt or Polling mode of Operation Flags
 */
#define XISF_POLLING_MODE	0
#define XISF_INTERRUPT_MODE 	1

/*
 * SPI Options flags
 */
#ifdef XPAR_XISF_INTERFACE_AXISPI
#define XISF_SPI_OPTIONS	(XSP_MASTER_OPTION | \
					XSP_MANUAL_SSELECT_OPTION | \
					XSP_CLK_PHASE_1_OPTION | \
					XSP_CLK_ACTIVE_LOW_OPTION)
#elif XPAR_XISF_INTERFACE_PSQSPI
#define XISF_SPI_OPTIONS	(XQSPIPS_MANUAL_START_OPTION | \
					XQSPIPS_FORCE_SSELECT_OPTION)
#elif XPAR_XISF_INTERFACE_PSSPI
#define XISF_SPI_OPTIONS	(XSPIPS_MASTER_OPTION | \
					XSPIPS_FORCE_SSELECT_OPTION)
#endif

/*
 * PS SPI/QSPI PreScaler Settings
 */
#ifdef XPAR_XISF_INTERFACE_PSQSPI
#define XISF_SPI_PRESCALER	XQSPIPS_CLK_PRESCALE_4
#elif XPAR_XISF_INTERFACE_PSSPI
#define XISF_SPI_PRESCALER  	XSPIPS_CLK_PRESCALE_8
#elif XPAR_XISF_INTERFACE_AXISPI
#define XISF_SPI_PRESCALER	0
#endif

/**
 * The following definitions determines the type of Write operation to be
 * performed on the Serial Flash.
 */
typedef enum {
	XISF_WRITE,				/**< Normal write operation */
	XISF_AUTO_PAGE_WRITE,			/**< Auto rewrite the contents
						  *  of the page */
	XISF_BUFFER_WRITE,			/**< Write data to the internal
						  *  SRAM buffer of the Flash */
	XISF_BUF_TO_PAGE_WRITE_WITH_ERASE,	/**< Erase the specified Page
						  *  then Write data to Flash
						  *  from the internal SRAM
						  *  buffer */
	XISF_BUF_TO_PAGE_WRITE_WITHOUT_ERASE,	/**< Write data to the Flash
						  *  from the internal SRAM
						  *  buffer */
	XISF_WRITE_STATUS_REG,			/**< Write to the Status
						  *  Register */
	XISF_OTP_WRITE,				/**< Write one byte of data in
						  *  to the One Time
						  *  Programmable area */
	XISF_WRITE_STATUS_REG2,			/**< Write to the 2 byte Status
						  *  Register in W25QXX flash */

#if ((XPAR_XISF_FLASH_FAMILY == WINBOND) || (XPAR_XISF_FLASH_FAMILY == STM) || \
     (XPAR_XISF_FLASH_FAMILY == SPANSION))
	XISF_QUAD_IP_PAGE_WRITE,		/**< Quad input fast page write
						  */
#endif /*((XPAR_XISF_FLASH_FAMILY == WINBOND) ||
	  (XPAR_XISF_FLASH_FAMILY == STM) ||
	  (XPAR_XISF_FLASH_FAMILY == SPANSION))*/

#if (XPAR_XISF_FLASH_FAMILY == STM)
	XISF_DUAL_IP_PAGE_WRITE,		/**< Dual input fast page write
						  */
	XISF_DUAL_IP_EXT_PAGE_WRITE,		/**< Dual input extended fast
						  *  page write */
	XISF_QUAD_IP_EXT_PAGE_WRITE,		/**< Dual input extended fast
						  *  page write */
#endif /* (XPAR_XISF_FLASH_FAMILY == STM) */
} XIsf_WriteOperation;

/**
 * The following definitions determines the type of Read operations to be
 * performed on the Serial Flash.
 */
typedef enum {
	XISF_READ,		/**< Normal Read operation */
	XISF_FAST_READ,		/**< Fast Read operation */
	XISF_PAGE_TO_BUF_TRANS,	/**< Transfer data from Flash memory to
				  *  internal SRAM buffer of Flash */
	XISF_BUFFER_READ,	/**< Read data from SRAM internal buffer of
				  *  the Flash */
	XISF_FAST_BUFFER_READ,	/**< Fast SRAM buffer read operation on Flash */
	XISF_OTP_READ,		/**< Read One Time Programmable area */

#if ((XPAR_XISF_FLASH_FAMILY == WINBOND) || (XPAR_XISF_FLASH_FAMILY == STM) || \
     (XPAR_XISF_FLASH_FAMILY == SPANSION))
	XISF_DUAL_OP_FAST_READ,	/**< Dual output fast read */
	XISF_DUAL_IO_FAST_READ,	/**< Dual input/output fast read */
	XISF_QUAD_OP_FAST_READ,	/**< Quad output fast read */
	XISF_QUAD_IO_FAST_READ,	/**< Quad input/output fast read */
#endif /*((XPAR_XISF_FLASH_FAMILY == WINBOND) ||
	  (XPAR_XISF_FLASH_FAMILY == STM)) ||
	  (XPAR_XISF_FLASH_FAMILY == SPANSION)*/
} XIsf_ReadOperation;

/**
 * The following definitions determines the type of Erase operation to be
 * performed on the Serial Flash.
 */
typedef enum {
	XISF_PAGE_ERASE,	/**< Page Erase operation */
	XISF_BLOCK_ERASE,	/**< Block Erase operation */
	XISF_SECTOR_ERASE,	/**< Sector Erase operation */
	XISF_BULK_ERASE		/**< Erase an entire Flash */
} XIsf_EraseOperation;

/**
 * The following definitions determines the type of Sector protection operations
 * to be performed on the Serial Flash.
 */
typedef enum {
	XISF_SPR_READ,		/**< Sector protect register read */
	XISF_SPR_WRITE,		/**< Sector protect register write */
	XISF_SPR_ERASE,		/**< Sector protect register erase */
	XISF_SP_ENABLE,		/**< Sector protect enable */
	XISF_SP_DISABLE		/**< Sector protect disable */
} XIsf_SpOperation;

/**
 * The following definitions determines the type of control operations to be
 * performed on the Serial Flash.
 */
typedef enum  {
	XISF_IOCTL_RELEASE_DPD,		/**< Release from Deep Power-down */
	XISF_IOCTL_ENTER_DPD,		/**< Enter in to Deep Power-down mode */
	XISF_IOCTL_CLEAR_SR_FAIL_FLAGS,	/**< Clear Status Register Fail Flags */
	XISF_IOCTL_ENABLE_HI_PERF_MODE	/**< Enable high performance mode
					  *  (availabe in Winbond quad flash
					  *  (W25Q)) */
} XIsf_IoctlOperation;

/**************************** Type Definitions *******************************/

#ifdef XPAR_XISF_INTERFACE_AXISPI
typedef XSpi XIsf_Iface;
#elif XPAR_XISF_INTERFACE_PSSPI
typedef XSpiPs XIsf_Iface;
#elif XPAR_XISF_INTERFACE_PSQSPI
typedef XQspiPs XIsf_Iface;
#endif

/**
 * The following definition specifies the instance structure of the Serial
 * Flash.
 */
typedef struct {
	u8 IsReady;		/**< Is Device is ready for operation */

	u16 BytesPerPage;	/**< Number of Bytes per Page */
	u16 PagesPerBlock;	/**< This is Number of Pages per block,
				     for Atmel and it is Number of
				     Pages per sector for
				     Intel/STM/Winbond/Spansion */
	u16 BlocksPerSector; 	/**< Number of Blocks per Sector, this is valid
				  *  for ATMEL devices */
	u16 NumOfSectors; 	/**< Number of Sectors in Serial Flash */
	u8 AddrMode; 		/**< Type of addressing in Atmel Serial Flash
				  *  0 - Default/Normal Addressing Mode
				  *  1 - Power-Of-2 Addressing Mode */
	u16 DeviceCode;		/**< The Serial Flash Device Code */
	XIsf_Iface *SpiInstPtr;	/**< SPI Device Instance pointer */
	u32 SpiSlaveSelect;	/**< SPI Slave select for the Serial Flash */
	u8 *WriteBufPtr; 	/**< Pointer to Write Buffer */

	u16 ByteMask;		/**< Mask used for Address translation in Atmel
				  *  devices */
	u8 RegDone;		/**< Registration Done flag */
	u8 IntrMode;		/**< Operating Mode flag Interrupt/Polling */
	int (*XIsf_Iface_SetOptions)
		(XIsf_Iface *InstancePtr, u32 Options);
#ifndef XPAR_XISF_INTERFACE_PSQSPI
	int (*XIsf_Iface_SetSlaveSelect)
		(XIsf_Iface *InstancePtr, u8 SlaveMask);
#else
	int (*XIsf_Iface_SetSlaveSelect)
		(XIsf_Iface *InstancePtr);
#endif
	int (*XIsf_Iface_Start)
		(XIsf_Iface *InstancePtr);
	int (*XIsf_Iface_Transfer)
		(XIsf_Iface *InstancePtr, u8 *SendBufPtr,
                  u8 *RecvBufPtr, unsigned int ByteCount);
	int (*XIsf_Iface_PolledTransfer)
		(XIsf_Iface *InstancePtr, u8 *SendBufPtr,
                  u8 *RecvBufPtr, unsigned ByteCount);
	int (*XIsf_Iface_SetClkPrescaler)
		(XIsf_Iface *InstancePtr, u8 PreScaler);

} XIsf;

/**
 * The following structure definition specifies the operational parameters to be
 * passed to the XIsf_Write API while performing Normal write (XISF_WRITE) and
 * OTP write (XISF_OTP_WRITE) operations.
 */
typedef struct {
	u32 Address;		/**< Address in the Serial Flash */
	u8 *WritePtr;		/**< Pointer to the data to be written to the
				  *  Serial Flash */
	u32 NumBytes;		/**< Number of bytes to be written to the Serial
				  *  Flash */
} XIsf_WriteParam;


/**
 * The following structure definition specifies the operational parameters to be
 * passed to the XIsf_Read API while performing Normal Read (XISF_READ),
 * Fast Read (XISF_FAST_READ) and OTP Read (XISF_OTP_READ) operations .
 */
typedef struct {
	u32 Address;		/**< Start address in the Serial Flash */
	u8 *ReadPtr;		/**< Read buffer pointer where data needs to be
				  *  stored */
	u32 NumBytes;		/**< Number of bytes to read */
	int NumDummyBytes;	/**< Number of dummy bytes associated with the
				  *  fast read command. Valid only for dual o/p
				  *  fast read, dual i/o fast read, quad o/p
				  *  fast read and quad i/o fast read */
} XIsf_ReadParam;



/**
 * The following structure definition specifies the operational parameters to be
 * passed to the XIsf_Write API while writing data to the internal SRAM buffer
 * of the Atmel Serial Flash (XISF_BUFFER_WRITE).
 */
typedef struct {
	u8 BufferNum;		/**< SRAM buffer number of Serial Flash */
	u8 *WritePtr;		/**< Pointer to the data to be written into the
				  *  Serial Flash SRAM Buffer */
	u32 ByteOffset;		/**< Byte offset in the buffer from which the
				  *  data is written */
	u32 NumBytes;		/**< Number of bytes to be written into the
				  *  buffer */
} XIsf_BufferWriteParam;


/**
 * The following structure definition specifies the operational parameters to be
 * passed to the XIsf_Write API while writing data from the internal SRAM buffer
 * to a Page in the Atmel Serial Flash using XISF_BUF_TO_PAGE_WRITE_WITH_ERASE /
 * XISF_BUF_TO_PAGE_WRITE_WITHOUT_ERASE commands in Atmel Serial Flash.
 */
typedef struct {
	u8 BufferNum;		/**< SRAM buffer number of Serial Flash */
	u32 Address;		/**< Starting address in the Serial Flash */
} XIsf_BufferToFlashWriteParam;

/**
 * The following structure definition specifies the operational parameters to be
 * passed to the XIsf_Read API while performing Page to Buffer Transfer
 * operation (XISF_PAGE_TO_BUF_TRANS) in Atmel Serial Flash.
 */
typedef struct {
	u8 BufferNum;		/**< SRAM buffer number of Serial Flash */
	u32 Address;		/**< Start address in the Serial Flash */
} XIsf_FlashToBufTransferParam;

/**
 * The following structure definition specifies the operational parameters to be
 * passed to the XIsf_Read API while reading data from the Internal SRAM buffer
 * of Flash using XISF_BUFFER_READ or XISF_FAST_BUFFER_READ commands in Atmel
 * Serial Flash.
 */
typedef struct {
	u8 BufferNum;		/**< SRAM buffer number of Serial Flash */
	u8 *ReadPtr;		/**< Read buffer pointer where data read from
				  *  the SRAM buffer is stored */
	u32 ByteOffset;		/**< Byte offset in the SRAM buffer from where
				  *  the first byte is read */
	u32 NumBytes;		/**< Number of bytes to be read from the
				  *  buffer */
} XIsf_BufferReadParam;


/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/*****************************************************************************/
/**
*
* This API sets the interrupt/polling mode of transfer.
*
* @param	InstancePtr is a pointer to the XIsf instance.
* @param	Mode is the value to be set.
*
* @note		By default, the xilisf library is designed to operate in
*		polling mode.  User needs to call this API to set in interrupt
*		mode, if operating in Interrupt Mode.
******************************************************************************/
static inline void XIsf_SetTransferMode(XIsf *InstancePtr, u8 Mode)
{
	InstancePtr->IntrMode = Mode;
}

/************************** Function Prototypes ******************************/

/*
 * Initialization Function.
 */
int XIsf_Initialize(XIsf *InstancePtr, XIsf_Iface *SpiInstPtr, u8 SlaveSelect,
				u8 *WritePtr);

/*
 * Function to read the Status Registers.
 */
int XIsf_GetStatus(XIsf *InstancePtr, u8 *ReadPtr);

#if (XPAR_XISF_FLASH_FAMILY == WINBOND)
int XIsf_GetStatusReg2(XIsf *InstancePtr, u8 *ReadPtr);
#endif

/*
 * Function to read the Serial Flash information.
 */
int XIsf_GetDeviceInfo(XIsf *InstancePtr, u8 *ReadPtr);

/*
 * Function for Writing to the Serial Flash.
 */
int XIsf_Write(XIsf *InstancePtr, XIsf_WriteOperation Operation,
		void *OpParamPtr);

/*
 * Function for Reading from the Serial Flash.
 */
int XIsf_Read(XIsf *InstancePtr, XIsf_ReadOperation Operation,
		void *OpParamPtr);

/*
 * Function for Erasing the Serial Flash.
 */
int XIsf_Erase(XIsf *InstancePtr, XIsf_EraseOperation Operation, u32 Address);

/*
 * Function related to Sector protection.
 */
int XIsf_SectorProtect(XIsf *InstancePtr, XIsf_SpOperation Operation,
			u8 *BufferPtr);

/*
 * Function to perform different control operations.
 */
int XIsf_Ioctl(XIsf *InstancePtr, XIsf_IoctlOperation Operation);

/*
 * Function for Enabling/Disabling Write to the Intel, STM, Winbond and Spansion
 * Serial Flash.
 */
int XIsf_WriteEnable(XIsf *InstancePtr, u8 WriteEnable);

/*
 * Function for Registering Interfaces SPI, PSQSPI, PSSPI
 */
void XIsf_RegisterInterface(XIsf *InstancePtr);

/*
 * Function for setting SPI/PSQSPI/PSSPI Configuration
 */
int XIsf_SetSpiConfiguration(XIsf *InstancePtr, XIsf_Iface *SpiInstPtr,
				u32 Options, u8 PreScaler);

#ifdef __cplusplus
}
#endif

#endif  /* end of protection macro */
