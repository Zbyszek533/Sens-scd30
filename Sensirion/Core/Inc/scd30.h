/*
 * scd30.h
 *
 *  Created on: 25 gru 2021
 *      Author: User
 */

#ifndef INC_SCD30_H_
#define INC_SCD30_H_

#include "i2c.h"
#include "printf_uart.h"

void readfirm();
void altComp();
void interRead();
void triggerStart();
void triggerStop();
void odczyt();

#endif /* INC_SCD30_H_ */
