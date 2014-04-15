/*
 * Encoder.h
 *
 * Created: 14-04-2014 13:35:55
 *  Author: alexander
 */ 


#ifndef ENCODER_H_
#define ENCODER_H_

#define F_CPU 3686400UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void sendData();
void initTimer0();

#endif /* ENCODER_H_ */