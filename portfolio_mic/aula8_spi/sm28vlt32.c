/*
 * sm28vlt32.c
 *
 * Created: 08/10/2026 10:34:50
 *  Author: Jean Ricardo Pinheiro
 */ 
#include <xc.h>
#include "spi.h"

void SM28VLT_config(void){
	DDRC =	(1<<DDC0); //usando PC0 como Slave Selectd (saída)
	PORTC |= (1<<PORTC0); //define nivel alto no PC0
}

uint8_t SM28VLT_readword(uint32_t pAddress){
	
	uint8_t tAddressByte2 = (pAddress & 0x00FF0000) >> 16;
	uint8_t tAddressByte1 = (pAddress & 0x0000FF00) >> 8;
	uint8_t tAddressByte0 = (pAddress & 0x000000FF) >> 0;
	uint8_t tDataByte1;
	uint8_t tDataByte0;
	PORTC &= ~(1<<PORTC0); //Sleve select em nivel baixo
	SPI_master_config(0x15); //comando 'read Word' ver datasheet
	SPI_transceive(tAddressByte0);
	SPI_transceive(tAddressByte1);
	SPI_transceive(tAddressByte2);
	tDataByte1 = SPI_transceive(0x00);
	tDataByte0 = SPI_transceive(0x00);
	SPI_transceive(0x00);//dummy
	PORTC |= (1<<PORTC0); //sleve selectd em nivel alto
	uint16_t tDataWord = ((uint16_t) tDataByte1) << 8
						|((uint16_t) tDataByte1) << 0;
	return tDataWord;
}