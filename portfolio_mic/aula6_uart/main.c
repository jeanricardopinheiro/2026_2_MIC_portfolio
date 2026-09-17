/*
 * main.c
 *
 * Created: 9/17/2026 10:15:09 AM
 *  Author: Jean Ricardo Pinheiro
 */ 
#define  F_CPU 16000000
#include <xc.h>
#include "util/delay.h"
/*configuração do módulo USRT0 para o modo assíncrono , frame de 8 bits, pariedade par, BAUND de 9600*/
void UART_config(){
	UCSR0A = (0<<U2X0);							// modo "double speed" desativado
	UCSR0B = (0<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02); //habilita o transmissor UART0, frame de 8 bits 
	UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)			//modo assincrono
				|(1<<UPM01)|(0<<UPM00)			// habilita pariedade par
				|(0<<USBS0)						//1 BIT DE STOP
				|(1<<UCSZ01)|(1<<UCSZ00)		// frame de 8 bits
				|(0<<UCPOL0);					//polaridade do clock: ignorada
				
	UBRR0 = 103; //BAUD de 9600(freq de bits por seg.), erro de 0.16%
		
}
/*Envia um byte na USATR*/
void UART_send(){
	UDR0 = 0x53; //envia um byte de exemplo
	_delay_ms(2);
	
}
int main(void){
	UART_config();
	
    while(1){
        UART_send(); 
    }
}