/*
 * main.c
 *
 * Created: 9/10/2026
 * Author: Jean Ricardo Pinheiro
 */

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

uint8_t barra = 0x00;

void GPIO_incBar() {
	barra = (barra << 1) | 0b00000001;
	PORTD = ~barra;
}

void GPIO_decBar() {
	barra = barra >> 1;
	PORTD = ~barra;
}

void GPIO_config() {
	DDRD = 0xFF;        // pinos usados pelos LEDs como saída
	PORTD = 0xFF;       // LEDs apagados
}

int main(void) {
	GPIO_config();

	while (1) {
		for (uint8_t i = 0; i < 8; i++) {
			GPIO_incBar();
			_delay_ms(200);
		}

		for (uint8_t i = 0; i < 8; i++) {
			GPIO_decBar();
			_delay_ms(200);
		}
	}
}