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

enum States {Start, Off_Release, On_Press, On_Release} state;

void Tick() {
	switch(state) {
		case Start:
			state = Off_Release;
			break;
		case Off_Release:
			if(PINA == 0x02) {
				state = On_Press;
			}
			else if(PINA == 0x80) PORTB = 0x00;
			else state = Off_Release;
			break;
		case On_Press:
			if(!PINA) { state = On_Release; }
			else { state = On_Press; }
			break;
		case On_Release:
			if(PINA == 0x01) {
				PORTB = 0x01;
			}
			else if(PINA == 0x80) PORTB = 0x00;
			else state = On_Release;
			break;
		default:
			break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
    state = Start;
    while (1) {
	Tick();
    }
    PORTC = state;
    return 0;
}
