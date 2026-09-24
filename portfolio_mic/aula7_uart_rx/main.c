/*
 * main.c
 *
 * Created: 9/24/2026 10:20:39 AM
 *  Author: Jean Ricardo Pinheiro
 */ 
#define  F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

/*configuração do módulo USRT0 para o modo assíncrono , frame de 8 bits, pariedade par, BAUND varialvel*/
void UART_config_rx(uint16_t pBAUND){
	UCSR0A = (0<<U2X0);							// modo "double speed" desativado
	UCSR0B = (1<<RXEN0)|(0<<TXEN0)|(0<<UCSZ02); //habilita o receptor UART0, frame de 8 bits
	UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)			//modo assincrono
	|(1<<UPM01)|(0<<UPM00)			// habilita pariedade par
	|(1<<USBS0)						//2 BIT DE STOP
	|(1<<UCSZ01)|(1<<UCSZ00)		// frame de 8 bits
	|(0<<UCPOL0);					//polaridade do clock: ignorada
	
	UBRR0 = (1000000/pBAUND) - 1 ; //BAUD de 9600(freq de bits por seg.), erro de 0.16%
	
}

void GPIO_config(){
	DDRC = (1<<DDC0)|(1<<DDC1); //PC0 e PC1 como saida
}

int main(void){
	GPIO_config();
	UART_config_rx(9600);
    while(1){
        while((UCSR0A & (1<<RXC0) ) == 0); //semáforo na flag de recebimento da UART
		uint8_t tReceivedByte = UDR0; //leitura do buffer UART
		//Tratamendo da mensagem recebida
		if(tReceivedByte == 'M'){
			PORTC |= (1<<PORTC0); //led verde
		}else{
			PORTC |= (1<<PORTC1); //led vermelho
		}
		_delay_ms(1);
		PORTC = 0; // apaga os leds que estiverem acessos
    }
}