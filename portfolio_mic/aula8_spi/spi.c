/*
 * spi.c
 *
 * Created: 08/10/2026 10:33:27
 *  Author: Jean Ricardo Pinheiro
 */ 
#include <xc.h>

void SPI_master_config(){
	SPCR = (1<<SPE) | (0<<DORD) | (1<<MSTR) //habilita SPI, MSB primeiro(padrão)
	| (0<<CPOL) | (0<<CPHA) //modo 0 de operação
	|(0<<SPR1)| (0<<SPR0); // velocidade de fosc/2 , SPI->8MHz
	SPSR = (1<<SPI2X); //operação de velocidade
	DDRB = (1<<DDB3) | (1<<DDB5); //// MOSI e SCK como saída; MISO permanece como entrada
}

uint8_t SPI_transceive(uint8_t pTxByte){
	uint8_t tReceivedByte;
	SPDR = pTxByte; // escrita no SPDR dispara a transação
	while((SPSR & (1<<SPIF)) == 0); //isola a flag, espera a flag SPIF subir
	tReceivedByte = SPDR; //leitura de dados
	return tReceivedByte;
	
}