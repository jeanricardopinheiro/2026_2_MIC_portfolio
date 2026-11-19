/*
 * main.c
 *
 * Created: 11/12/2026 10:16:31 AM
 *  Author: Jean Ricardo Pinheiro
 */ 


#define F_CPU 16000000
#include <xc.h>

void ADC_config() {
	ADMUX = (0<<MUX3) | (0<<MUX2) | (0<<MUX1) | (0<<MUX0) // canal de conversao ; pino adc0
	| (1<<REFS0) | (1<<REFS1); //canal de referencia interna de 1.1V
	ADCSRA = (1<<ADEN) | (0<<ADATE) // habilida o adc em modo "manual"
	| (1<<ADPS2)| (1<<ADPS1) | (1<<ADPS0); //fator de prescale de 128(adc operando em 125kHz)
	DIDR0 = (1<<ADC0D); //desabilita porta pc0
}

int main(void){
	DDRB |= (1<<DDB0); //define pb0 como saida
	ADC_config();
    while(1){
		ADCSRA |= (1<<ADSC); // inicia uma conversão
		while((ADCSRA & (1<<ADIF)) == 0); //prende ela até que seja concluida
		//acesso a ADCH e ADCL como um unico registrador de 16 bits (faixa de 0 a 1023) ADLAR = 0;
        uint16_t tADCData = ADC;
		ADCSRA |= (1<<ADIF); //limpa a flag para tentar encontrar o erro da simulacao
		//acender led abaixo de 720mV
		if (tADCData < 670){
			PORTB|= (1<<PORTB0); //acender led
		}else{
			PORTB &= ~(1<<PORTB0); // apagar led
		}
	}
}