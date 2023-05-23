#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "avr-millis-function-master/millis.h"


#define MAX_SPEED 100
#define Aplus	1
#define Aminus	0
#define Bplus	3
#define Bminus	2

unsigned long prev_millis;

void set_high(volatile uint8_t *port, volatile uint8_t pin){
	*port |= (1<<pin);
}

void set_low(volatile uint8_t *port, volatile uint8_t pin){
	*port &= ~(1<<pin);
}

void set(volatile uint8_t *port, volatile uint8_t pin, int val){
	if (val) set_high(port, pin);
	else set_low(port, pin);
}

void setup(){
    
    // Redéfinition horloge
    CLKSEL0 = 0b00010101;   // sélection de l'horloge externe
    CLKSEL1 = 0b00001111;   // minimum de 8Mhz
    CLKPR = 0b10000000;     // modification du diviseur d'horloge (CLKPCE=1)
    CLKPR = 0;              // 0 pour pas de diviseur OUT_unset&(diviseur de 1)
    
	//Setup des LEDs en sortie
	DDRB |= (1<<PB0);
    DDRB |= (1<<PB1);
    DDRB |= (1<<PB2);
    DDRB |= (1<<PB3);
    DDRB |= (1<<PB4);
    DDRB |= (1<<PB5);
    DDRB |= (1<<PB6);
    
    set_low(&PORTB, PB0);
    set_low(&PORTB, PB1);
    set_low(&PORTB, PB2);
    set_low(&PORTB, PB3);
	set_low(&PORTB, PB4);
    set_low(&PORTB, PB5);
    set_low(&PORTB, PB6);

	//Setup du timer
    init_millis(16000000UL);
    prev_millis = millis();
    
    //Setup du moteur
    DDRD |= (1<<PD0);
    DDRD |= (1<<PD1);
    DDRD |= (1<<PD2);
    DDRD |= (1<<PD3);
}

void cligno_droit(){
    int cd_millis = millis();
    
    while (millis() - cd_millis < 300){
        if (millis() - cd_millis < 150){
            set_high(&PORTB, PB1);
            set_high(&PORTB, PB6);
        }
        
        else{
            set_low(&PORTB, PB1);
            set_low(&PORTB, PB6);
        }
    }
}

void cligno_gauche(){
    int cg_millis = millis();
    
    while (millis() - cg_millis < 300){
        if (millis() - cg_millis < 150){
            set_high(&PORTB, PB2);
            set_high(&PORTB, PB5);
        }
        
        else{
            set_low(&PORTB, PB2);
            set_low(&PORTB, PB5);
        }
    }
}

void stop(){
    set_high(&PORTB, PB4);
}

void route1(){
    set_high(&PORTB, PB0);
    set_high(&PORTB, PB3);
    
    if (millis() - prev_millis < 2000){
        cligno_droit();
    }
    
    if ((millis() - prev_millis > 2400) && (millis() - prev_millis < 3600)){
        cligno_droit();
    }
    
    if ((millis() - prev_millis > 4000) && (millis() - prev_millis < 5000)){
        stop();
    }
    set_low(&PORTB, PB4);
    
    if ((millis() - prev_millis > 6000) && (millis() - prev_millis < 8000)){
        cligno_gauche();
    }
    
    set_low(&PORTB, PB0);
    set_low(&PORTB, PB3);
}

void step(int A,int B)
{
    switch(A){
        case -1: set_high(&PORTD, Aminus); set_low(&PORTD, Aplus); break;
        case  1: set_low(&PORTD, Aminus); set_high(&PORTD, Aplus); break;
        case  0: set_low(&PORTD, Aminus); set_low(&PORTD, Aplus); break;
    }
    switch(B){
        case -1: set_high(&PORTD, Bminus); set_low(&PORTD, Bplus); break;
        case  1: set_low(&PORTD, Bminus); set_high(&PORTD, Bplus); break;
        case  0: set_low(&PORTD, Bminus); set_low(&PORTD, Bplus); break;
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
    
void loop(){
    if (millis() - prev_millis > 9000){
        prev_millis = millis();
    }
    
    else{
        if ((millis() - prev_millis)/100 % 2){
            forward(100);
        }
        
        else{
            backward(100);
        }
        
        route1();
    }
//     else route1();
    
//     if (millis() - prev_millis < 100){
//         set_high(&PORTB, PB0);
//         set_high(&PORTB, PB1);
//         set_high(&PORTB, PB2);
//         set_high(&PORTB, PB3);
//         set_high(&PORTB, PB4);
//         set_high(&PORTB, PB5);
//         set_high(&PORTB, PB6);
//     }
//     
//     else if (millis() - prev_millis < 200){
//         set_low(&PORTB, PB0);
//         set_low(&PORTB, PB1);
//         set_low(&PORTB, PB2);
//         set_low(&PORTB, PB3);
//         set_low(&PORTB, PB4);
//         set_low(&PORTB, PB5);
//         set_low(&PORTB, PB6);
//     }
/*    
    else prev_millis = millis();*/
}

int main(){
	setup();

    forward(100);
    forward(100);
    forward(100);
    forward(100);

	while(1){
		loop();
	}
	return 0;
}
