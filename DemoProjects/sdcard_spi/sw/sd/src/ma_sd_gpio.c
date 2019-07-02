/*
 * gpio.c
 *
 *  Created on: Apr 14, 2014
 *      Author: MA
 */
#include "ma_sd_gpio.h"
//////////////////////////////////////////////////////////////////////////////////
void ma_gpio_init(void) {
	int status;
	status = XGpio_Initialize(&SD, GPIO_SD);
	if (status != XST_SUCCESS)
		print("!SD_GPIO init Failed\n\r");

	//							4			3			2		  1			  0
	// SCLK,DO,DI,CD,CS    SCLK:output   DO:input   DI:output  CD:input   CS:output
	// DO = MISO
	// DI = MOSI
	//Bits set to 0 are output and bits set to 1 are input.
	//XGpio_SetDataDirection(&SD, 1, 0b01010);

	XGpio_SetDataDirection(&SD, 1, 0b10);

	SD_CS_High();
	//SD_DI_High();
	//SD_SCLK_Low();
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
