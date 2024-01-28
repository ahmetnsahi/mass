/*
 * Programs.h
 *
 *  Created on: Jan 17, 2024
 *      Author: Ahmet
 */

#ifndef INC_PROGRAMS_H_
#define INC_PROGRAMS_H_

#include "main.h"








typedef struct prg{

	uint8_t time;
	uint8_t temp;
	uint8_t speed;
	uint16_t motor;


}prg;










void f1(int time,int valuduty, int motor,int temp);






#endif /* INC_PROGRAMS_H_ */
