/*
 * main.c
 *
 * Created: 9/3/2026 8:57:10 AM
 *  Author: Jean Ricardo Pinheiro
 */ 

#include <xc.h>

ISR(PCINT0_vect){
	
}

void GPIO_config(){
	//mascara final: 0b1111 0000;
	DDRB &= ~((1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3)); /*zera mascara, coloca 1 nos selecionados,
	depois inverte, Portas PB0,PB1,PB2,PB3 como entrada*/
	
	//DDRD= 0xff; seta tudo como saida mesmo que 0b11111111
	DDRD |= ((1<<DDD0)|(1<<DDD1)|(1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7));
	/*configura PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7 como saida*/
}

void PCINT_config(){
	
}

int main(void){
    while(1){
        //TODO:: Please write your application code 
    }
}