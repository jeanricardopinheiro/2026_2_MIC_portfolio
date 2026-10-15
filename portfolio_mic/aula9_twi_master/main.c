/*
 * main.c
 *
 * Created: 10/15/2026 8:59:17 AM
 *  Author: Jean Ricardo Pinheiro
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util\delay.h"

void TWI_master_config(){
	TWBR |= 64; // divisor de 64, fscl-100kHz
	TWSR |= (0<<TWPS1)|(0<<TWPS0); // prescaler de 1
	TWSR |= (1<<TWEN);	//
}

int main(void){
	TWI_master_config();
	_delay_ms(1000);
	uint8_t tSlaveAddress = 10;
    while(1){
		//escrever comunicação como mestre
        TWCR |= (1<<TWSTA); // inicia condiçaõ de start
		while((TWCR & (1<<TWINT)) == 0); //aguarda a flag de interrupção subir
		//condição de start ok??
		uint8_t tStatusCode = (TWSR & 0b11111000);
		if(tStatusCode == 0x08){ //condição de start ok
			//enviar byte para escravo 10
			TWDR |= (tSlaveAddress<<1) | 1 ; //endereço e flag de R/W(1 = leitura, 0=escrita)
			TWCR |= (1<<TWINT)|(1<<TWEN); // limpar flag de interrupção
			while((TWCR & (1<<TWINT)) == 0); //aguarda a flag de interrupção subir
			tStatusCode = (TWSR & 0b11111000);	//novo statuscode
			if(tStatusCode == 0x18){
				//ack recebido
			}else if(tStatusCode == 0x28){
				//ack nao recebido
			}else{
				//outro erro
			}
		}else{
			//algum erro...
		}
		_delay_ms(100);
    }
}