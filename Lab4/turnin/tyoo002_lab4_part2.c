/*	Author: tyoo002
 *  Partner(s) Name: Microcontroller [atmega1284]:
 *	Lab Section: 23
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

unsigned char countOne = 0;
unsigned char countTwo = 0;
enum States {Start, Off, WaitUntilThree, Increment, Decrement, Reset} state;

void Tick() { 
	switch(state) {
		case Start:
			PORTC = 0x07;
			state = Off;
			break;
		case Off:
			if(PINA == 0x01) {
				state = Increment;
				if(PORTC < 0x09) {
					PORTC++;
				}
				break;
			}
			else if(PINA == 0x02) {
				state = Decrement;
				if(PORTC > 0x00) {
					PORTC--;
				}
				break;
			}
			else if(PINA == 0x03) {
				PORTC = 0;
				state = Reset;
				break;
			}
			else { 
				state = Off;
				break;
			}
		case Increment:
			state = WaitUntilThree;
			break;
		case Decrement:
			state = WaitUntilThree;
			break;
		case WaitUntilThree:
			if(PINA == 0x01 || PINA == 0x02) {
				state = WaitUntilThree;
				break;
			}
			else if(PINA == 0x03) {
				state = Reset;
				PORTC = 0;
			}
			else { 
				state = Off; 
				break; 
			}
		case Reset:
			if(PINA == 0x01 || PINA == 0x02) {
				state = Reset;
				break;
			}
			else {
				state = Off;
				break;
			}
		default:
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

