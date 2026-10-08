/*
 * main.c
 *
 * Created: 10/8/2026 8:49:01 AM
 *  Author: Jean Ricardo Pinheiro
 */ 
#define  F_CPU 16000000
#include <xc.h>
#include "util/delay.h"
#include "spi.h"
#include "sm28vlt32.h"


int main(void){
	SPI_master_config();
	SM28VLT_config();
    while(1){
        uint16_t tMemoryData =SM28VLT_readword(1000);
		_delay_ms(1);
    }
}