/*
 * main.c
 *
 * Created: 8/27/2026 8:26:03 AM
 *  Author: Jean Ricardo Pinheiro
 */ 
#define  F_CPU 16000000
#include <xc.h>
#include <stdint.h> // boa prática
#include "util/delay.h"

#define  BIT0_MASK 0b00000001
#define  BIT1_MASK 0b00000010
#define  BIT2_MASK 0b00000100
#define  BIT5_MASK 0b00100000

void GPIO_config()
{
	DDRB = (1<<DDB6) | (1<<DDB4) | (1<<DDB2) | (1<<DDB0);	//bits sao configurados com shift
	/*o final: 0b0101 0101*/
}

int main(void)
{
	
	GPIO_config();
	uint8_t tData = 0x03; //0b0000 0011
    while(1)
    {
		PORTB = tData;
		_delay_ms(1000);
		tData = tData << 1; //a cada iteração leva pra esquerda:
		/*-> 0b0000 0110 -> 0b0000 1100 -> 0b0001 1000 -> ...*/
		if(tData == 0)
		{
			tData = 0x03;
		}
	}
}