/////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009 Xilinx, Inc. All Rights Reserved.
//
// You may copy and modify these files for your own internal use solely with
// Xilinx programmable logic devices and  Xilinx EDK system or create IP
// modules solely for Xilinx programmable logic devices and Xilinx EDK system.
// No rights are granted to distribute any files unless they are distributed in
// Xilinx programmable logic devices.
//
/////////////////////////////////////////////////////////////////////////////////

/*
 *      Simple SREC Bootloader
 *      This simple bootloader is provided with Xilinx EDK for you to easily re-use in your
 *      own software project. It is capable of booting an SREC format image file 
 *      (Mototorola S-record format), given the location of the image in memory.
 *      In particular, this bootloader is designed for images stored in non-volatile flash
 *      memory that is addressable from the processor. 
 *
 *      Please modify the define "FLASH_IMAGE_BASEADDR" in the blconfig.h header file 
 *      to point to the memory location from which the bootloader has to pick up the 
 *      flash image from.
 *
 *      You can include these sources in your software application project in XPS and 
 *      build the project for the processor for which you want the bootload to happen.
 *      You can also subsequently modify these sources to adapt the bootloader for any
 *      specific scenario that you might require it for.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blconfig.h"
#include "portab.h"
#include "errors.h"
#include "srec.h"
#include "xparameters.h"
#include <xilisf.h>		/* Serial Flash Library header file */

/* Defines */
#define CR       13

/* Comment the following line, if you want a smaller and faster bootloader which will be silent */
#define VERBOSE

/* Declarations */
static void display_progress (uint32_t lines);
static uint8_t load_exec ();
static uint8_t flash_get_srec_line (uint8_t *buf);
extern void init_stdout();

/* Declarations for ISF/SPI */
#define SPI_DEVICE_ID			XPAR_AXI_SPI_0_DEVICE_ID
#define ISF_SPI_SELECT		0x01
#define ISF_PAGE_SIZE		256

static XIsf Isf;
static XSpi Spi;
XIsf_ReadParam ReadParam;
volatile static int TransferInProgress; /* State of Spi Transfer */
u8 IsfWriteBuffer[ISF_PAGE_SIZE + XISF_CMD_SEND_EXTRA_BYTES];
u8 ReadBuffer[ISF_PAGE_SIZE + XISF_CMD_SEND_EXTRA_BYTES]; /* Read Buffer */

extern int srec_line;

#ifdef __cplusplus
extern "C" {
#endif

extern void outbyte(char c); 

#ifdef __cplusplus
}
#endif

/* Data structures */
static srec_info_t srinfo;
static uint8_t sr_buf[SREC_MAX_BYTES];
static uint8_t sr_data_buf[SREC_DATA_MAX_BYTES];

static uint8_t *flbuf;

#ifdef VERBOSE
static int8_t *errors[] = { 
    "",
    "Error while copying executable image into RAM",
    "Error while reading an SREC line from flash",
    "SREC line is corrupted",
    "SREC has invalid checksum."
};
#endif

/* We don't use interrupts/exceptions. 
   Dummy definitions to reduce code size on MicroBlaze */
#ifdef __MICROBLAZE__
void _interrupt_handler () {}
void _exception_handler () {}
void _hw_exception_handler () {}
#endif


int main()
{
    uint8_t ret;

	/*
	 * Initialize the SPI driver so that it's ready to use,
	 * specify the device ID that is generated in xparameters.h.
	 */
	XSpi_Initialize(&Spi, SPI_DEVICE_ID);
	
	/*
	 * Start the SPI driver so that interrupts and the device are enabled.
	 */
	XSpi_Start(&Spi);

	/*
	* Disable Global interrupt to use polled mode operation
	*/
	XSpi_IntrGlobalDisable(&Spi);

	/*
	 * Initialize the Serial Flash Library.
	 */
	XIsf_Initialize(&Isf, &Spi, ISF_SPI_SELECT, IsfWriteBuffer);
	

    init_stdout();

#ifdef VERBOSE    
    print ("\r\nSREC Bootloader\r\n");
    print ("Loading SREC image from flash @ address: ");    
    putnum (FLASH_IMAGE_BASEADDR);
    print ("\r\n");        
#endif

    flbuf = (uint8_t*)FLASH_IMAGE_BASEADDR;
    ret = load_exec ();

    /* If we reach here, we are in error */
    
#ifdef VERBOSE
    if (ret > LD_SREC_LINE_ERROR) {
        print ("ERROR in SREC line: ");
        putnum (srec_line);
        print (errors[ret]);    
    } else {
        print ("ERROR: ");
        print (errors[ret]);
    }
#endif

    return ret;
}

#ifdef VERBOSE
static void display_progress (uint32_t count)
{
    /* Send carriage return */
    outbyte (CR);  
    print  ("Bootloader: Processed (0x)");
    putnum (count);
    print (" S-records");
}
#endif

static uint8_t load_exec ()
{
    uint8_t ret;
    void (*laddr)();
    int8_t done = 0;
    
    srinfo.sr_data = sr_data_buf;
    
    while (!done) {
        if ((ret = flash_get_srec_line (sr_buf)) != 0) 
            return ret;

        if ((ret = decode_srec_line (sr_buf, &srinfo)) != 0)
            return ret;
        
#ifdef VERBOSE
        display_progress (srec_line);
#endif
        switch (srinfo.type) {
            case SREC_TYPE_0:
                break;
            case SREC_TYPE_1:
            case SREC_TYPE_2:
            case SREC_TYPE_3:
                memcpy ((void*)srinfo.addr, (void*)srinfo.sr_data, srinfo.dlen);
                break;
            case SREC_TYPE_5:
                break;
            case SREC_TYPE_7:
            case SREC_TYPE_8:
            case SREC_TYPE_9:
                laddr = (void (*)())srinfo.addr;
                done = 1;
                ret = 0;
                break;
        }
    }

#ifdef VERBOSE
    print ("\r\nExecuting program starting at address: ");
    putnum ((uint32_t)laddr);
    print ("\r\n");
#endif

    (*laddr)();                 
  
    /* We will be dead at this point */
    return 0;
}


static uint8_t flash_get_srec_line (uint8_t *buf)
{
    uint8_t c;
    int count = 0;

    while (1) {
    	/*
    	 * Set the
    	 * - Address in the Serial Flash where the data is to be read from.
    	 * - Number of bytes to be read from the Serial Flash.
    	 * - Read Buffer to which the data is to be read.
    	 */
    	TransferInProgress = TRUE;
    	ReadParam.Address = flbuf++;
    	ReadParam.NumBytes = 1;
    	ReadParam.ReadPtr = ReadBuffer;

    	XIsf_Read(&Isf, XISF_READ, (void*) &ReadParam);
    	IsfWaitForFlashNotBusy();
        c  = ReadBuffer[XISF_CMD_SEND_EXTRA_BYTES];

        if (c == 0xD) {   
            /* Eat up the 0xA too */
        	TransferInProgress = TRUE;
        	ReadParam.Address = flbuf++;
        	ReadParam.NumBytes = 1;
        	ReadParam.ReadPtr = ReadBuffer;

        	XIsf_Read(&Isf, XISF_READ, (void*) &ReadParam);
        	IsfWaitForFlashNotBusy();
        	c  = ReadBuffer[XISF_CMD_SEND_EXTRA_BYTES];

            return 0;
        }
        
        *buf++ = c;
        count++;
        if (count > SREC_MAX_BYTES) 
            return LD_SREC_LINE_ERROR;
    }
}

int IsfWaitForFlashNotBusy(void)
{
	int Status;
	u8 StatusReg;

	while(1) {

		/*
		 * Get the Status Register.
		 */
		TransferInProgress = TRUE;
		Status = XIsf_GetStatus(&Isf, ReadBuffer);
		if(Status != XST_SUCCESS) {
			return XST_FAILURE;
		}

		/*
		 * Check if the Serial Flash is ready to accept the next
		 * command. If so break.
		 */
		StatusReg = ReadBuffer[BYTE2];
		if((StatusReg & XISF_SR_IS_READY_MASK) == 0) {
			break;
		}
	}

	return XST_SUCCESS;
}


#ifdef __PPC__

#include <unistd.h>

/* Save some code and data space on PowerPC 
   by defining a minimal exit */
void exit (int ret)
{
    _exit (ret);
}
#endif
