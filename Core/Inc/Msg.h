/*
 * Msg.h
 *
 *  Created on: Sep 14, 2023
 *      Author: ahmet
 */

#ifndef SRC_MSG_H_
#define SRC_MSG_H_

#include "main.h"


typedef struct Motor{
	TIM_HandleTypeDef Tımer;
	uint32_t *Channel;
	uint16_t *Duty;

};



typedef struct{

     uint16_t MSayi;
	 uint16_t Speeds;


}Massage;

typedef struct {

	Massage Mass;

}Mod_t;







#endif /* SRC_MSG_H_ */
