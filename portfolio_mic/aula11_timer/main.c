/*
 * main.c
 *
 * Created: 10/22/2026 10:51:12 AM
 *  Author: Jean Ricardo Pinheiro
 */ 

#include <xc.h>
#include "avr/interrupt.h"

//objetivo: obter uma interupção com periodo de 10ms
ISR(TIMER0_COMPA_vect){ // interrupção com periodo de 10ms (comparação A com timer)
	PORTB ^=(1<<PORTB0); //altera estado PB3
}

void TMR0_config(){
	TCCR0A = (1<<WGM00) | (1<<WGM00); //configuração no modo CTC
	TCCR0B = (1<<WGM02)|(1<<CS02)|(0<<CS01)|(1<<CS00); 
	OCR0A = 155; //aproximadamente 10ms (9,984ms)
	TIMSK0 = (1<<OCIE0A); //habilita interrupção comparativa
}

int main(void){
	DDRB |= (1<<DDB0);//saida no PB3
	TMR0_config();
	sei();
    while(1){
        
    }
}