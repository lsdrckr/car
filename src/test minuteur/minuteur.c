#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define CTC1            WGM12           // Meilleur nom pour le bit
#define PERIODE         1000

void init_minuteur(int diviseur,long periode){
    TCCR1A=0;               // Le mode choisi n'utilise pas ce registre
    TCCR1B=(1<<CTC1);       // Réinitialisation du minuteur sur expiration
    switch(diviseur){
        case    8: TCCR1B |= (1<<CS11); break;
        case   64: TCCR1B |= (1<<CS11 | 11<<CS10); break;
        case  256: TCCR1B |= (1<<CS12); break;
        case 1024: TCCR1B |= (1<<CS12 | 1<<CS10); break;
    }
// Un cycle prend 1/F_CPU secondes.
// Un pas de compteur prend diviseur/F_CPU secondes.
// Pour une periode en millisecondes, il faut (periode/1000)/(diviseur/F_CPU) pas
// soit (periode*F_CPU)/(1000*diviseur)
        OCR1A=F_CPU/1000*periode/diviseur;  // Calcul du pas
        TCNT1=0;                            // Compteur initialisé
        TIMSK1=(1<<OCIE1A);                 // Comparaison du compteur avec OCR1A
}

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

void invert(volatile uint8_t *port, volatile uint8_t pin){
    *port ^= (1<<pin);
}

ISR(TIMER1_COMPA_vect){    // Procédure d'interruption
    invert(&PORTB, PB5);
}

void setup(){
    //Setup des LEDs en sortie
	DDRB |= (1<<PB5);
	
	set_low(&PORTB, PB5);
    
    init_minuteur(8,PERIODE);
    sei();
}

int main(void)
{
    setup();
    while(1){
    }
}

