/*
 * ma_ff_timer.h
 *
 *  Created on: Aug 19, 2016
 *      Author: Mahdi
 */

#ifndef MA_FF_TIMER_H_
#define MA_FF_TIMER_H_

#include "xparameters.h"
#include "xtmrctr.h"
#include "xil_exception.h"
#include "xintc.h"
#include <stdio.h>

/* The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are only defined here such that a user can easily
 * change all the needed parameters in one place.
 */

#define TMRCTR_DEVICE_ID	XPAR_TMRCTR_0_DEVICE_ID
#define TMRCTR_INTERRUPT_ID	XPAR_INTC_0_TMRCTR_0_VEC_ID
#define INTC_DEVICE_ID		XPAR_INTC_0_DEVICE_ID

// function that call in timer interrupt service routine
extern void disk_timerproc(void);

int ma_timer_init(void);

#endif /* MA_FF_TIMER_H_ */
