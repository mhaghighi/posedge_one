/*
 * delay.c
 *
 *  Created on: Mar 2, 2015
 *      Author: Mahdi
 */

#include "ma_delay.h"

void ma_delay_ms(int delay) {
	int i;
	for (i = 0; i < 10000 * delay; i++)
		;
}

void ma_delay_us(int delay) {
	int i;
	for (i = 0; i < 10 * delay; i++)
		;
}
