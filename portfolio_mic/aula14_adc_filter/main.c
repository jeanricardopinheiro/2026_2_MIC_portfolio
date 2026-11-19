/*
	* main.c
	*
	* Created: 11/19/2026 8:33:42 AM
	*  Author: Jean Ricardo Pinheiro
	*/ 
#define F_CPU 16000000
#include <xc.h>
#include "avr/interrupt.h"
	
uint16_t x[4]; //medias do ADC

ISR(TIMER1_COMPB_vect){
	PORTB ^= (1<<PORTB1); //debug para 
}

ISR(ADC_vect){ //interupção referente a converrsao concluida
	PORTB |= (1<<PORTB1);
	uint16_t tADCData = ADC;
		
	x[3] = x[2]; //linha de atraso
	x[2] = x[1];
	x[1] = x[0];
	x[0] = tADCData;
	uint16_t y = (x[0] +x[1] +x[2] +x[3])/4; //filtro média movel de ordem 4
		
	//ADCSRA |= (1<<ADIF); //limpa a flag para tentar encontrar o erro da simulacao
	//acender led abaixo de 720mV
	if (tADCData < 670){
		PORTB ^= (1<<PORTB0); //acender led
		}else{
		PORTB &= ~(1<<PORTB0); // apagar led
	}
	PORTB &=~(1<<PORTB1);
}

void ADC_config() {
	ADMUX = (0<<MUX3) | (0<<MUX2) | (0<<MUX1) | (0<<MUX0)	// canal de conversao ; pino adc0
			| (1<<REFS0) | (1<<REFS1);						//canal de referencia interna de 1.1V
	ADCSRA = (1<<ADEN) | (1<<ADATE)							// habilida o adc em modo "auto trigger"
			| (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0)			//fator de prescale de 128(adc operando em 125kHz)
			| (1<<ADIE);									//habilita interrupção do AD
	DIDR0 = (1<<ADC0D);										//desabilita porta pc0 
	ADCSRB = (1<<ADTS2)| (0<<ADTS1) | (1<<ADTS0);			//fonte do diaparto: TMR1 Compare match B
}

//configurar timer 1 para disparo a cada 1ms
void TMR1_config(){
	TCCR1A = (0<<WGM11)|(0<<WGM10); //
	TCCR1B = (0<<WGM13)|(1<<WGM12)				// modo 4: CTC com topo em OICR1A
			|(0<<CS12)|(0<<CS11)|(1<<CS10);		//prescaler unitário
	OCR1A = 16000;								//periodo de 1ms
	OCR1B = 0;
	TIMSK1 = (1<<OCIE1B); //debug: habilita interrupção compare match B
}

int main(void){
	DDRB = (1<<DDB0)|(1<<DDB1); //pinos PB0 E PB1 como saida
	TMR1_config();
	ADC_config();
	sei();
	while(1){
		//TODO:: Please write your application code 
	}
}