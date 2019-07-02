//#if 0
#include <stdio.h>
#include "ff.h"
#include "xstatus.h"
#include "ma_ff_timer.h"

void print(char *str);

extern void ma_test_timer(void);

static FIL fil; /* File object */
static FATFS fatfs;
static char FileName[32] = "Test.bin";
static char *SD_File;

u8 DestinationAddress[20 * 1024] __attribute__ ((aligned(32)));
u8 SourceAddress[20 * 1024] __attribute__ ((aligned(32)));

#define TEST 7

int main() {
	int status;

	FRESULT Res;
	TCHAR *Path = "0:/";
	u32 FileSize = (20 * 1024);
	UINT NumBytesWritten;
	UINT NumBytesRead;
	u32 BuffCnt;

	print("Hello World\n\r");

	status = ma_timer_init();
	if (status != XST_SUCCESS) {
		print("ma_timer_init failed\n\r");
		return XST_FAILURE;
	}
	//ma_test_timer();

	for (BuffCnt = 0; BuffCnt < FileSize; BuffCnt++) {
		SourceAddress[BuffCnt] = TEST + BuffCnt;
	}

	/* Register volume work area, initialize device */
	Res = f_mount(&fatfs, Path, 1);
	if (Res != FR_OK) {
		print("! f_mount failed.\n\r");
		return XST_FAILURE;
	}
	print("f_mount OK.\n\r");

	DWORD sz_disk;

	if (disk_ioctl(0, 1, &sz_disk))
		print("! disk_ioctl GET_SECTOR_COUNT failed \n\r");

	printf("disk total sector is : %d\n\r",(int)sz_disk);

	/*
	 * Open file with required permissions.
	 * Here - Creating new file with read/write permissions. .
	 * To open file with write permissions, file system should not
	 * be in Read Only mode.
	 */
	SD_File = (char *) FileName;

	Res = f_open(&fil, SD_File, FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
	if (Res) {
		print("! f_open failed.\n\r");
		return XST_FAILURE;
	}
	print("f_open OK.\n\r");

	/* Pointer to beginning of file . */
	Res = f_lseek(&fil, 0);
	if (Res) {
		print("! f_lseek failed.\n\r");
		return XST_FAILURE;
	}
	print("f_lseek OK.\n\r");

	/* Write data to file. */
	Res = f_write(&fil, (const void*) SourceAddress, FileSize,
			&NumBytesWritten);
	if (Res) {
		print("! f_write failed.\n\r");
		return XST_FAILURE;
	}
	print("f_write OK.\n\r");

	/* Pointer to beginning of file . */
	Res = f_lseek(&fil, 0);
	if (Res) {
		print("! f_lseek failed.\n\r");
		return XST_FAILURE;
	}
	print("f_lseek OK.\n\r");

	/* Read data from file. */
	Res = f_read(&fil, (void*) DestinationAddress, FileSize, &NumBytesRead);
	if (Res) {
		print("! f_read failed.\n\r");
		return XST_FAILURE;
	}

	/* Data verification */
	for (BuffCnt = 0; BuffCnt < FileSize; BuffCnt++) {
		if (SourceAddress[BuffCnt] != DestinationAddress[BuffCnt]) {
			print("! data verification failed.\n\r");
			return XST_FAILURE;
		}
	}

	/* Close file. */
	Res = f_close(&fil);
	if (Res) {
		print("! f_close failed.\n\r");
		return XST_FAILURE;
	}

	print("SD card test OK.\n\r");

	return 0;
}
//#endif

#if 0
/*
 Basic instructions for recording data in an SD Card in native mode
 The SD card (3.3 V) must be properly interfaced to Arduino (5 V)

 The typical procedure is:
 Initialize SPI
 Initialize SD Card
 START
 -Blank vector of data (vBlock)
 -Record data in vector of data
 -Copy data from vector to CSD card
 GOTO START

 At your convenience:
 -Copy data from CSD card to vector of data
 -Read data from vector

 Starting from there, you will have to build your own file system...

 Useful links
 http://elm-chan.org/docs/mmc/mmc_e.html
 http://www.retroleum.co.uk/mmc_cards.html
 http://www.maxim-ic.com/appnotes.cfm/an_pk/3969

 No warranty, no claims, just fun

 Didier Longueville invenit et fecit February 2010
 */
#include "xil_types.h"
#include "ma_sd_spi.h"
#include "ma_sd_gpio.h"
#include "ma_delay.h"
#include "xil_printf.h"
#include "platform.h"

typedef u8 byte;

// Ports
//int PIN_CS = PINB2;      // chip select
//int PIN_MOSI = PINB3;    // master out slave in
//int PIN_MISO = PINB4;    // master in slave out
//int PIN_CLOCK = PINB5;   // clock

/********************** SPI SECTION BELOW **********************/

// SPI Variables
byte clr;// dummy variable used to clear some of the SPI registers
byte spi_err;// SPI timeout flag, must be cleared manually

// send an SPI command, includes time out management
// returns spi_err: "0" is "no error"
byte spi_cmd(volatile char data) {
	spi_err = 0; // reset spi error
//	SPDR = data; // start the transmission by loading the output byte into the spi data register
//	int i = 0;
//	while (!(SPSR & (1 << SPIF))) {
//		i++;
//		if (i >= 0xFF) {
//			spi_err = 1;
//			return (0x00);
//		}
//	}
//	// returned value
//	return (SPDR);
	return ma_sd_spi_send_recive_byte(data);
}

// initialize SPI port
void spi_initialize(void) {
//	SPCR = (1 << SPE) | (1 << MSTR); // spi enabled, master mode
//	clr = SPSR; // dummy read registers to clear previous results
//	clr = SPDR;
	ma_gpio_init();
	SD_CS_High()
	;
	ma_sd_spi_init();

}

/********************** SD CARD SECTION BELOW **********************/

// SD Card variables
#define blockSize 512          // block size (default 512 bytes)
byte vBlock[blockSize];// set vector containing data that will be recorded on SD Card
byte vBuffer[16];

#define GO_IDLE_STATE 0x00     // resets the SD card
#define SEND_CSD 0x09          // sends card-specific data
#define SEND_CID 0x0A          // sends card identification
#define READ_SINGLE_BLOCK 0x11 // reads a block at byte address
#define WRITE_BLOCK 0x18       // writes a block at byte address
#define SEND_OP_COND 0x29      // starts card initialization
#define APP_CMD 0x37           // prefix for application command
// Send a SD command, num is the actual index, NOT OR'ed with 0x40.
// arg is all four bytes of the argument
byte sdc_cmd(byte commandIndex, long arg) {
	int i;
	SD_CS_Low()
	;
	spi_cmd(0xFF);           // dummy byte
	commandIndex |= 0x40;// command token OR'ed with 0x40
	spi_cmd(commandIndex);// send command
	for (i = 3; i >= 0; i--) {
		spi_cmd(arg >> (i * 8)); // send argument in little endian form (MSB first)
	}
	spi_cmd(0x95); // checksum valid for GO_IDLE_STATE, not needed thereafter, so we can hardcode this value
	spi_cmd(0xFF);// dummy byte gives card time to process
	byte res = spi_cmd(0xFF);
	return (res);// query return value from card
}

// initialize SD card
// retuns 1 if successful
byte sdc_initialize(void) {
	byte i;

	SD_CS_High()
	;

	for (i = 0; i < 10; i++) {
		spi_cmd(0xFF);       // send 10 times 8 pulses for a warmup (74 minimum)
	}
	// set idle mode
	byte retries = 0;
	SD_CS_Low()
	;
	while (sdc_cmd(GO_IDLE_STATE, 0) != 0x01) { // while SD card is not in iddle state
		retries++;
		if (retries >= 0xFF) {
			return (0); // timed out!
		}
		ma_delay_ms(5);
	}
	xil_printf("GO_IDLE_STATE retries = %d\n\r",retries);

	// at this stage, the card is in idle mode and ready for start up
	retries = 0;
	sdc_cmd(APP_CMD, 0);// startup sequence for SD cards 55/41
	while (sdc_cmd(SEND_OP_COND, 0) != 0x00) {
		retries++;
		if (retries >= 0xFF) {
			return (0); // timed out!
		}
		sdc_cmd(APP_CMD, 0);
	}
	xil_printf("SEND_OP_COND retries = %d\n\r",retries);

	return (0x01); // returned value (success)
}

// clear block content
void sdc_clearVector(void) {
	int i;
	for (i = 0; i < blockSize; i++) {
		vBlock[i] = 0;
	}
}

// read SD card register content and store it in vBuffer
void sdc_readRegister(byte sentCommand) {
	int i;
	byte retries = 0x00;
	byte res = sdc_cmd(sentCommand, 0);
	while (res != 0x00) {
		ma_delay_ms(1);
		retries++;
		if (retries >= 0xFF)
		return; // timed out!
		res = spi_cmd(0xFF);// retry
	}
	// wait for data token
	while (spi_cmd(0xFF) != 0xFE)
	;
	// read data
	for (i = 0; i < 16; i++) {
		vBuffer[i] = spi_cmd(0xFF);
	}
	// read CRC (lost results in blue sky)
	spi_cmd(0xFF);// LSB
	spi_cmd(0xFF);// MSB
}

// get nbr of blocks on SD memory card from
long sdc_totalNbrBlocks(void) {
	sdc_readRegister(SEND_CSD);
	// compute size
	long C_Size = ((vBuffer[0x08] & 0xC0) >> 6) | ((vBuffer[0x07] & 0xFF) << 2)
	| ((vBuffer[0x06] & 0x03) << 10);
	long C_Mult = ((vBuffer[0x08] & 0x80) >> 7) | ((vBuffer[0x08] & 0x03) << 2);
	return ((C_Size + 1) << (C_Mult + 2));
}

// write block on SD card
// addr is the address in bytes (multiples of block size)
void sdc_writeBlock(long blockIndex) {
	int i;
	byte retries = 0;
	while (sdc_cmd(WRITE_BLOCK, blockIndex * blockSize) != 0x00) {
		//delay(1);
		ma_delay_ms(1);
		retries++;
		if (retries >= 0xFF)
		return;// timed out!
	}
	spi_cmd(0xFF); // dummy byte (at least one)
	// send data packet (includes data token, data block and CRC)
	// data token
	spi_cmd(0xFE);
	// copy block data
	for (i = 0; i < blockSize; i++) {
		spi_cmd(vBlock[i]);
	}
	// write CRC (lost results in blue sky)
	spi_cmd(0xFF);// LSB
	spi_cmd(0xFF);// MSB
	// wait until write is finished
	while (spi_cmd(0xFF) != 0xFF)
	//delay(1); // kind of NOP
	ma_delay_ms(1);
}

// read block on SD card and copy data in block vector
// retuns 1 if successful
void sdc_readBlock(long blockIndex) {
	int i;
	byte retries = 0x00;
	byte res = sdc_cmd(READ_SINGLE_BLOCK, (blockIndex * blockSize));
	while (res != 0x00) {
		//delay(1);
		ma_delay_ms(1);
		retries++;
		if (retries >= 0xFF)
		return;// timed out!
		res = spi_cmd(0xFF);// retry
	}
	// read data packet (includes data token, data block and CRC)
	// read data token
	while (spi_cmd(0xFF) != 0xFE)
	;
	// read data block
	for (i = 0; i < blockSize; i++) {
		vBlock[i] = spi_cmd(0xFF); // read data
	}
	// read CRC (lost results in blue sky)
	spi_cmd(0xFF);// LSB
	spi_cmd(0xFF);// MSB
}

// print vector of data
void sdc_printVectorContent(void) {
	int i;
	for (i = 0; i < blockSize; i++) {
		xil_printf("0x");
		if (vBlock[i] <= 0x0F)
		xil_printf("0");
		xil_printf("%x", vBlock[i]);
		//Serial.print(vBlock[i], HEX);
		xil_printf(" ");
		// append crlf to each line of 16 bytes
		if (((i + 1) % 16) == 0)
		xil_printf("\n\r");
	}
	xil_printf("\n\r");
}

/********************** MAIN ROUTINES SECTION  BELOW **********************/

int main() {
	int b;
	int i;

	init_platform();
	print("Hello World\n\r");

	spi_err = 0;        // reset SPI error
	spi_initialize();// initialize SPI port
	sdc_initialize();// Initialize SD Card

	xil_printf("%d blocks\n\r", sdc_totalNbrBlocks());

	xil_printf("Writing blocks...\n\r");
	for (b = 0; b < 5; b++) {
		xil_printf("Writing block ");
		xil_printf("%d\n\r", b);
		for (i = 0; i < blockSize; i++) {
			vBlock[i] = b; // write incremental data
		}
		sdc_writeBlock(b);         // copy vector of data on SD card
	}
	xil_printf("Reading blocks...\n\r");
	for (b = 0; b < 5; b++) {
		xil_printf("Reading block ");
		xil_printf("%d\n\r", b);
		sdc_readBlock(b);    // copy SD card block of data in vector of data
		sdc_printVectorContent();// print vector of data content
	}

	return 0;
}
#endif

