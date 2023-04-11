#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "io.h"
#include "card_io.h"

#define Aplus	7
#define Aminus	6
#define Bplus	5
#define Bminus	4

#define MAX_SPEED	100

void step(int A,int B)
{
    switch(A){
        case -1: OUT_set(phases[Aminus]); OUT_unset(phases[Aplus]); break;
        case  1: OUT_unset(phases[Aminus]); OUT_set(phases[Aplus]); break;
        case  0: OUT_unset(phases[Aminus]); OUT_unset(phases[Aplus]); break;
    }
    switch(B){
        case -1: OUT_set(phases[Bminus]); OUT_unset(phases[Bplus]); break;
        case  1: OUT_unset(phases[Bminus]); OUT_set(phases[Bplus]); break;
        case  0: OUT_unset(phases[Bminus]); OUT_unset(phases[Bplus]); break;
    }
}

void speed_wait(int speed)
{
    int i;
    for(i=0;i<MAX_SPEED/speed;i++) _delay_ms(1);
}

void forward(int speed)
{
    step(1,1);
    speed_wait(speed);
    step(-1,1);
    speed_wait(speed);
    step(-1,-1);
    speed_wait(speed);
    step(1,-1);
    speed_wait(speed);
}

void backward(int speed)
{
    step(1,1);
    speed_wait(speed);
    step(1,-1);
    speed_wait(speed);
    step(-1,-1);
    speed_wait(speed);
    step(-1,1);
    speed_wait(speed);
}
  

int main(void)
{
    outputs_init(OUTPUT_PORTB,OUTPUT_PORTC,OUTPUT_PORTD);
    inputs_init(INPUT_PORTB,INPUT_PORTC,INPUT_PORTD,
                PULLUP_PORTB,PULLUP_PORTC,PULLUP_PORTD);

    int portb,portc,portd;
    int speed=0;
    while(1){
        inputs_get(&portb,&portc,&portd);
//         if(IN_glue(portb,portc,portd)/*&buttons[0]*/) if(speed<MAX_SPEED) speed++;
        if(IN_glue(portb,portc,portd)/*&buttons[1]*/) if(speed>-MAX_SPEED) speed--;
        if(speed>0) forward(speed);
        if(speed<0) backward(-speed);
        OUT_toggle(leds[0]);
    }

    return 0;
}

