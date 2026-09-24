/*
 * main.c
 *
 * Created: 9/24/2026 10:20:39 AM
 *  Author: Jean Ricardo Pinheiro
 */ 
#define  F_CPU 16000000
#include <xc.h>
#include <string.h>
#include "util/delay.h"
#include "avr/interrupt.h"

#define RX_BUFFER_SIZE 16 // boas práticas

uint8_t gMessage[RX_BUFFER_SIZE]; //buffer global da UART
uint16_t gRxCounter = 0 ; //contagem de bytes recebidos
uint8_t gMessageReady = 0;

/*configuração do módulo USRT0 para o modo assíncrono , frame de 8 bits, pariedade par, BAUND varialvel*/
void UART_config_rx(uint16_t pBAUND){
	UCSR0A = (0<<U2X0);							// modo "double speed" desativado
	UCSR0B = (1<<RXEN0)|(0<<TXEN0)|(0<<UCSZ02) //habilita o receptor UART0, frame de 8 bits
			| (1<<RXCIE0); //habilita a interrupção de recebimento da UART
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


ISR(USART_RX_vect){
	uint8_t tReceivedByte = UDR0; //leitura do buffer UART
	gMessage[gRxCounter] = tReceivedByte; //armazena byte a ser recebido no buffer
	gRxCounter++;
	if(gRxCounter == RX_BUFFER_SIZE){ //proteção contra estouro do buffer
		gRxCounter = 0;
	}
	if(tReceivedByte == '\n'){
		gMessageReady = 1; //flag de mensagem completa 
	}
}

int main(void){
	GPIO_config();
	UART_config_rx(9600);
	sei(); //habilita interrupções globais
    while(1){
		if(gMessageReady){ //aguarda mensagem completa
			gMessageReady = 0;
			//Tratamendo da mensagem recebida
			if(strcmp(gMessage, "Messagem")){
				PORTC |= (1<<PORTC0); //led verde
				}else{
				PORTC |= (1<<PORTC1); //led vermelho
			}
			_delay_ms(10);
			PORTC = 0; // apaga os leds que estiverem acessos
		}
	}
}