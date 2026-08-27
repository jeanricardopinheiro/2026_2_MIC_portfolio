/*
 * main.c
 *
 * Created: 8/27/2026 10:25:12 AM
 *  Author: Jean Ricardo Pinheiro
 */ 
#define F_CPU 16000000
#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"
//configuração da interrupção externa (INT0/INT1)

ISR(INT0_vect) //função no vetor de interrupção INT0
{
	PORTB |= (1<< PORTB1); // acende led em PB1
	_delay_ms(100);
	PORTB &= ~(1<<PORTB1); // apaga led PB1
}

void INT_config()
{
	EICRA = (1<<ISC01) | (0<<ISC00); // CONFIGURA INT0 na borda de descida
	EIMSK = (1<<INT0); //habilida INT0
}

void GPIO_config()
{
	DDRB |= (1<<DDB0); //pino PB0 como saida
	DDRB |= (1<<DDB1); //pino PB1 como saida
}
int main(void)
{
    GPIO_config();
	INT_config();
	sei(); //habilida intrrupções globalmente
	while(1)
    {
        _delay_ms(100);
		PORTB ^= (1<<PORTB0);
    }
}