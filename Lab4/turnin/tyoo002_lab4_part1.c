/*	Author: tyoo002
 *  Partner(s) Name: Microcontroller [atmega1284]:
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Off_Release, On_Press, On_Release, Off_Press} state;

void Tick() {
	switch(state) {
		case Start:
			PORTB = 0x01;
			state = Off_Release;
			break;
		case Off_Release:
			state = PINA ? On_Press : Off_Release;
			if(PINA) PORTB = 0x02;
			break;
		case On_Press:
			state = PINA ? On_Press : On_Release;
			break;
		case On_Release:
			state = PINA ? Off_Press : On_Release;
			if(PINA) PORTB = 0x01;
		default:
			break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
    state = Start;
    while (1) {
	Tick();
    }
    return 1;
}
