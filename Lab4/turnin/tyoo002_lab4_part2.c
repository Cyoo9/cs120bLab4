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
                        PORTC = 0x07;
                        state = Off_Release;
                        break;
                case Off_Release:
			if(PINA != 0x00) {
				state = On_Press;
			}
			else { 
				state = Off_Release;
			}
			break;
		case On_Press:
			if(!PINA) { 
				state = On_Release;
			}
			else {
				state = On_Press;
			}
			break;
                default:
                        break;
        }	
	switch(state) {	
		case On_Press:
			if(PINA == 0x01) { 
				if(PORTC < 9) { PORTC++; }
			}
			else if(PINA == 0x02) {
				if(PORTC > 0) { PORTC--; }
			}
			else if(PINA == 0x03) { PORTC = 0; }
			break;
	}	

}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
    state = Start;
    while (1) {
        Tick();
    }
    return 0;
}

