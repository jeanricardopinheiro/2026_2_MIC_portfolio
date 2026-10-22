/*
 * main.c
 *
 * Created: 10/22/2026 10:51:12 AM
 *  Author: Jean Ricardo Pinheiro
 */ 

#include <xc.h>
#include "avr/interrupt.h"

uint16_t gMilliseconds = 0;
uint8_t gClockSeconds = 0;
uint8_t gClockMinutes = 0;
uint8_t gClockhours = 0;

//objetivo: obter uma interupção com periodo de 10ms
ISR(TIMER0_COMPA_vect){ // interrupção com periodo de 10ms (comparação A com timer)
	gMilliseconds += 10;
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
		if(gMilliseconds<100){
			PORTB |= (1<<PORTB0); //acende led por 100ms	
		}else{
			PORTB &= ~(1<<PORTB0);	//zera led por 900ms
		}
		//logica do RTC
		if(gMilliseconds >= 1000){
			gMilliseconds = 0;
			gClockSeconds++;
			if(gClockSeconds >= 60){
				gClockSeconds= 0;
				gClockMinutes++;
				if (gClockMinutes >= 60){
					gClockMinutes = 0;
					gClockhours++;
					if (gClockhours >= 24){
						gClockhours = 0;
					}
				}
			}
		}
    }
}