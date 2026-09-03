/*
 * main.c
 *
 * Created: 9/3/2026 8:57:10 AM
 *  Author: Jean Ricardo Pinheiro
 */ 
#define  F_CPU 16000000
#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"
#include <stdint.h>

#define KEY_RELEASED 0
#define KEY_PRESSED 1

uint8_t gKeyState_w = 0;
uint8_t gKeyState_a = 0;
uint8_t gKeyState_s = 0;
uint8_t gKeyState_d = 0;

void GPIO_config(){
	//mascara final: 0b1111 0000;
	DDRB &= ~((1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3)); /*zera mascara, coloca 1 nos selecionados,
	depois inverte, Portas PB0,PB1,PB2,PB3 como entrada*/
	
	PORTB |= (1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3);  /*habilita o pullup para os pinos 
	PB0,PB1,PB2,PB3 */
	
	//DDRD= 0xff; seta tudo como saida na porta D, mesmo que 0b11111111
	DDRD |= ((1<<DDD0)|(1<<DDD1)|(1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7));
	/*configura PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7 como saida*/
	DDRC |= (1<<DDC0); //configura PC0 como saída
}

void GPIO_incBar(){
	PORTD = PORTD >> 1;
	PORTD |= 0b10000000; // aciona o bit mais significativo
}

void GPIO_decBar(){
	PORTD = PORTD << 1;
}

ISR(PCINT0_vect){
	uint8_t tCurrentKeyState_w = 0;
	if((PINB & (1<<PINB0)) !=0){ //testa pino PB0
		//PB0 = 1, tecla w solta
		tCurrentKeyState_w = KEY_RELEASED;
	}else{
		//PB0 = 0, tecla w pressionada
		tCurrentKeyState_w = KEY_PRESSED;
	}
	
	if(tCurrentKeyState_w == KEY_PRESSED && gKeyState_w ==  KEY_RELEASED){
		//tecla w acabou de ser pressionada
		gKeyState_w = KEY_PRESSED;
		GPIO_incBar();
	}else if(tCurrentKeyState_w == KEY_RELEASED && gKeyState_w ==  KEY_PRESSED){
		//tecla w acabou de ser solta
		gKeyState_w = KEY_RELEASED;
	}
	
	//tecla s
	uint8_t tCurrentKeyState_s = 0;
	if((PINB & (1<<PINB2)) !=0){ //testa pino PB0
		//PB0 = 1, tecla s solta
		tCurrentKeyState_s = KEY_RELEASED;
		}else{
		//PB0 = 0, tecla s pressionada
		tCurrentKeyState_s = KEY_PRESSED;
	}
	
	if(tCurrentKeyState_s == KEY_PRESSED && gKeyState_s ==  KEY_RELEASED){
		//tecla s acabou de ser pressionada
		gKeyState_s = KEY_PRESSED;
		GPIO_decBar();
		}else if(tCurrentKeyState_s == KEY_RELEASED && gKeyState_s ==  KEY_PRESSED){
		//tecla s acabou de ser solta
		gKeyState_s = KEY_RELEASED;
	}
	
	
	PORTC ^= (1<<PORTC0); //seta pino PC0 (nivel 1)
	/*_delay_ms(100);
	PORTC &= ~(1<<PORTC0); //zera pino PC0*/
	
}

void PCINT_config(){
	PCICR |= (1<<PCIE0); // habilita o grupo 0 de vetores
	PCMSK0 |= (1<<PCINT0)|(1<<PCINT1)|(1<<PCINT2)|(1<<PCINT3); //habilita interrupção para os pinos escolhidos
}

int main(void){
	GPIO_config();
	PCINT_config();
	sei();
    while(1){
        //TODO:: Please write your application code 
    }
}