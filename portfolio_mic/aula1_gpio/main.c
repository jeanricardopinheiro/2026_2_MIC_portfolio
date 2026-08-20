/*
 * main.c
 *
 * Created: 8/20/2026 10:37:11 AM
 *  Author: Jean Ricardo Pinheiro
 */ 
#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

int main(void)
{
	DDRB |= 0b00100000; //define pino PB5 como saída
	DDRD &= 0b11110111; //define pino PD3 como entrada
    while(1)
    {
		if( (PIND & 0b00001000) !=0) { // ler valor da chave PD3 (operador & isola apenas o pino 3, se estiver alto > 0  continua o código abaixo) 
			PORTB|= 0b00100000; // atribui o nivel lógico alto ao pino PB5
			_delay_ms(100);
			PORTB &= 0b11011111; //atribui nivel lógico baixo ao pino PB5
			_delay_ms(900);
			//TODO:: Please write your application code 
		}
    }
}