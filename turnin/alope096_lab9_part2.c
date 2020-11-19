/*	Author: lab
 *  Partner(s) Name: none
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

#include "timer.h"

//we will be using PA0, PA1, PA2,PA3
unsigned char threeLEDs;
unsigned char blinkingLED;

enum BL_States{BL_Start, OffLed, OnLed}BL_state;

void Tick_BL(){
    switch(BL_state){
        case BL_Start:
            BL_state = OnLed;
        break;
        case OnLed:
            BL_state = OffLed;
        break;
        case OffLed:
            BL_state = OnLed;
        break;
    }
    switch(BL_state){
        case BL_Start:
            blinkingLED = 0x00;
        break;
        case OffLed:
            blinkingLED = 0x00;
        break;
        case OnLed:
            blinkingLED = 0x08;
        break;
    }
}

enum TL_States{TL_Start, Light0,Light1,Light2}TL_state;

void Tick_TL(){
    switch(TL_state){
        case TL_Start:
            TL_state = Light0;
        break;
        case Light0:
            TL_state = Light1;
        break;
        case Light1:
            TL_state = Light2;
        break;
        case Light2:
            TL_state = Light0;
        break;

    }
    switch(TL_state){
        case TL_Start:
            threeLEDs = 0x00;
        break;
        case Light0:
            threeLEDs = 0x01;
        break;
        case Light1:
            threeLEDs = 0x02;
        break;
        case Light2:
            threeLEDs = 0x04;
        break;
    }
}

void Tick_CombineLEDs(){
    PORTB= blinkingLED | threeLEDs;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA=0x00; PORTA=0xFF;
    DDRB=0xFF; PORTB=0x00;
   
    unsigned long BL_elapsedTime = 1000;
    unsigned long TL_elapsedTime = 300;
    const unsigned long timerPeriod = 100;

    TimerSet(timerPeriod);
    TimerOn();

    BL_state = BL_Start;
    TL_state = TL_Start;

    /* Insert your solution below */
    while (1) {
        if(BL_elapsedTime>=1000){
            Tick_BL();
            BL_elapsedTime =0;
        }
        if(TL_elapsedTime>=300){
            Tick_TL();
            TL_elapsedTime =0;
        }
        
        while(!TimerFlag){};
        TimerFlag = 0;
        BL_elapsedTime += timerPeriod;
        TL_elapsedTime += timerPeriod;
        Tick_CombineLEDs();
    }
    return 1;
}
