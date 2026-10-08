/*
 * main.c
 *
 * Created: 10/8/2026 8:49:01 AM
 *  Author: Jean Ricardo Pinheiro
 */ 
#define  F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

void SPI_master_config(){
	SPCR = (1<<SPE) | (0<<DORD) | (1<<MSTR) //habilita SPI, MSB primeiro(padrão)
			| (0<<CPOL) | (0<<CPHA) //modo 0 de operação
			|(0<<SPR1)| (0<<SPR0); // velocidade de fosc/2 , SPI->8MHz 
	SPSR = (1<<SPI2X); //operação de velocidade
	DDRB = (1<<DDB3) | (1<<DDB5); //saída nos pinos mosi e miso
}


int main(void){
	SPI_master_config();
    while(1){
        SPDR = 0xC7; // mensagem a ser enviada
		_delay_ms(1);
    }
}