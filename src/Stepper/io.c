/** Functions for I/O **/

#include <avr/io.h>

// Input initialization

int in_portb=-1,in_portc=-1,in_portd=-1;
int in_pullupb=-1,in_pullupc=-1,in_pullupd=-1;

void inputs_init(int portb,int portc,int portd,int pullupb,int pullupc,int pullupd){
DDRB &= ~portb; PORTB |= pullupb;
DDRC &= ~portc; PORTC |= pullupc;
DDRD &= ~portd; PORTD |= pullupd;
in_portb=portb; in_pullupb=pullupb;
in_portc=portc; in_pullupc=pullupc;
in_portd=portd; in_pullupd=pullupd;
}

// Output initialization

int out_portb=-1,out_portc=-1,out_portd=-1;

void outputs_init(int portb,int portc,int portd){
DDRB |= portb;
DDRC |= portc;
DDRD |= portd;
out_portb=portb;
out_portc=portc;
out_portd=portd;
}

// Get inputs

void inputs_get(int *portb,int *portc,int *portd){
*portb=0; *portc=0; *portd=0;
if(in_portd>=0){ *portb=PINB & in_portb; *portb ^= in_pullupb; }
if(in_portc>=0){ *portc=PINC & in_portc; *portc ^= in_pullupc; }
if(in_portb>=0){ *portd=PIND & in_portd; *portd ^= in_pullupd; }
}

// Set output

void outputs_set(int portb,int portc,int portd){
if(out_portb>=0){ PORTB |= portb & out_portb; PORTB &= portb | ~out_portb; }
if(out_portc>=0){ PORTC |= portc & out_portc; PORTC &= portc | ~out_portc; }
if(out_portd>=0){ PORTD |= portd & out_portd; PORTD &= portd | ~out_portd; }
}
