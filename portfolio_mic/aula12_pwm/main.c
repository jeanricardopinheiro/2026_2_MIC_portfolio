/*
 * main.c
 *
 * Created: 11/1/2026 12:16:27 AM
 *  Author: Jean Ricardo Pinheiro
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

void PWM_config() {
	TCCR0A	= (1<<COM0A1)|(0<<COM0A0) //saida n inversora OCR0A
			| (1<<COM0B1)|(1<<COM0B0) //saida inversora OCR0B
			| (1<<WGM01)|(1<<WGM00); //pwm no modo fast
	TCCR0B	= (0<<WGM02)|(0<<CS02)|(0<<CS01)|(1<<CS00);	//ativa timer com prescaler de 1x
	OCR0A	= 163; //razao ciclo de 40% em OC0A
	OCR0B	= 76; //razao ciclo de 30% em OC0B
	DDRD	= (1<<DDD6)|(1<<DDD5); //configura pinos de saída do pwm OC0A e OC0B
}

void PWM_setVoltageA(uint16_t pMillivolts) {
	if(pMillivolts == 0) { //protecao contra parametros fora da faixa util
		OCR0A = 0;
	} else
	if(pMillivolts >= 5000) {
		OCR0A = 0xff;
	} else {
		//Ver: cast estático em linguagem C
		//cast estático é essa conversao de variavel (tipo) que é feita explicitamente
		//nesse caso abaixo é essa parada do (uint_8t) e do (uint32_t), na primeira é pra dar entrada
		//no registrador e na segunda pra garantir o valor da multiplicacao 
		OCR0A = (uint8_t)(0x000000FF & (((uint32_t) pMillivolts * 256) / 5000));
	}
}

int main(void) {
	PWM_config();
	PWM_setVoltageA(2500);
    while(1) {
		PWM_setVoltageA(2500); //fase 0graus
		_delay_ms(1);
		PWM_setVoltageA(3750); //fase 30graus
		_delay_ms(1);
		PWM_setVoltageA(4665); //fase 60graus
		_delay_ms(1);
		PWM_setVoltageA(5000); //fase 90graus
		_delay_ms(1);
		PWM_setVoltageA(4665);
		_delay_ms(1);
		PWM_setVoltageA(3750);
		_delay_ms(1);
		PWM_setVoltageA(2500);
		_delay_ms(1);
		PWM_setVoltageA(1250);
		_delay_ms(1);
		PWM_setVoltageA(335);
		_delay_ms(1);
		PWM_setVoltageA(0);
		_delay_ms(1);
		PWM_setVoltageA(335);
		_delay_ms(1);
		PWM_setVoltageA(1250);
		_delay_ms(1);
    }
}