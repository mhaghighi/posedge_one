/*
 * gpio.h
 *
 *  Created on: Apr 14, 2014
 *      Author: MA
 */

#ifndef MA_SD_GPIO_H_
#define MA_SD_GPIO_H_

#include <stdio.h>
#include "xparameters.h"
#include "xgpio.h"

#define GPIO_SD       XPAR_AXI_GPIO_0_DEVICE_ID

XGpio SD;

//NET "axi_gpio_0_GPIO_IO_pin[0]" LOC = P127 | IOSTANDARD = LVCMOS33 | PULLUP;    #CS
//NET "axi_gpio_0_GPIO_IO_pin[1]" LOC = P120 | IOSTANDARD = LVCMOS33 | PULLUP;    #CD
//NET "axi_gpio_0_GPIO_IO_pin[2]" LOC = P126 | IOSTANDARD = LVCMOS33 | PULLUP;    #DI
//NET "axi_gpio_0_GPIO_IO_pin[3]" LOC = P123 | IOSTANDARD = LVCMOS33 | PULLUP;    #DO
//NET "axi_gpio_0_GPIO_IO_pin[4]" LOC = P124 | IOSTANDARD = LVCMOS33 | PULLDOWN;  #SCLK

//							4			3			2		  1			  0
// SCLK,DO,DI,CD,CS    SCLK:output   DO:input   DI:output  CD:input   CS:output
// DO = MISO
// DI = MOSI

#define CS_PIN		1<<0
#define CD_PIN		1<<1
//#define DI_PIN		1<<2
//#define DO_PIN		1<<3
//#define SCLK_PIN	1<<4

#define SD_CS_High()	XGpio_DiscreteSet  (&SD, 1, CS_PIN)
#define SD_CS_Low()	    XGpio_DiscreteClear(&SD, 1, CS_PIN)

//#define SD_DI_High()	XGpio_DiscreteSet  (&SD, 1, DI_PIN)
//#define SD_DI_Low()	    XGpio_DiscreteClear(&SD, 1, DI_PIN)
//
//#define SD_SCLK_High()	XGpio_DiscreteSet  (&SD, 1, SCLK_PIN)
//#define SD_SCLK_Low()	XGpio_DiscreteClear(&SD, 1, SCLK_PIN)

#define SD_CD_Read() 	XGpio_DiscreteRead (&SD, 1) & CD_PIN
//#define SD_DO_Read() 	XGpio_DiscreteRead (&SD, 1) & DO_PIN


void ma_gpio_init(void);


#endif /* MA_SD_GPIO_H_ */
