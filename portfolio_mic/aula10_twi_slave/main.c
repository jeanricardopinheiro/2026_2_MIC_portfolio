/*
 * main.c
 *
 * Created: 10/22/2026 8:21:07 AM
 *  Author: Jean Ricardo Pinheiro
 */ 
#define F_CPU 16000000
#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"

ISR(TWI_vect){
	//tratar o estado atual da máquina do TWI
	PORTB |=(1<<PORTB0);
	uint8_t tStatusCode = (TWSR & 0b11111000);
	switch(tStatusCode){
		case (0x60): { //recebido SLA+W, inicio de escrita do mestre
			PORTB |=(1<<PORTB1);
			TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT)|(1<<TWEA); //envio do ACK
		}break;
		case (0x80): {
			uint8_t tReceivedByte = TWDR;//recebe o dado enviado pelo mestre
			PORTB |=(1<<PORTB2);
			TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT)|(1<<TWEA);//envio do ACK
		}break;
		case (0xA0):{ //final da transmissão (stop condition ou repeated start)
				PORTB |=(1<<PORTB3);
				TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT);
		}break;
		default:{
			//algum erro ou condição não tratada
			PORTB |=(1<<PORTB4);
			TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT);
		};
	}
	_delay_ms(1);
	PORTB = 0;
}

void TWI_slave_config(uint8_t pAddress){
	TWBR = 64; // divisor de 64, fscl-100kHz
	TWSR |= (0<<TWPS1)|(0<<TWPS0); // prescaler de 1
	TWSR |= (1<<TWEN);	//
	TWAR = pAddress<<1;
}

int main(void){
	DDRB |= (1<<DDB3)|(1<<DDB2)|(1<<DDB1)|(1<<DDB0)|(1<<DDB4); //saida leds de sinalização
	TWI_slave_config(10);
	sei();
    while(1){
        //TODO:: Please write your application code 
    }
}