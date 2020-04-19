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

enum States {Start, Off_Release, On_Press} state;

unsigned char code[4] = {0x04,0x01,0x02,0x01}; // code to unlock/lock
unsigned char i = 0; //array index

void Tick() {
	//initial state is locked 
	switch(state) {
		case Start:
			state = Off_Release;
			break;
		case Off_Release:
			if(PINA == code[i]) {	
				if(i == 3) { //last code required 'X'
					//i = 0;
					if(PORTB == 0x00) { PORTB = 0x01; }
					else { PORTB = 0x00; }
				}
				else { i++; }
				state = On_Press;
			}
			else if(PINA == 0x80) { PORTB = 0x00; }
			else state = Off_Release;
			break;
		case On_Press:
			if(!PINA) { 
				state = Off_Release;
			}
			else { state = On_Press; }
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
    //PORTC = state;
    return 0;
}
