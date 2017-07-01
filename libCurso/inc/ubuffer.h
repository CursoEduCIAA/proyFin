#ifndef UBUFFER_H_
#define UBUFFER_H_

#include "stdint.h"

#define SIZEBUFFER 50

typedef struct Qbuffer{
	uint8_t buffer[SIZEBUFFER];
	uint8_t head;
	uint8_t tail;
	uint8_t size;
}Qbuffer;


void initCola(Qbuffer* buffer); //se inicializa para colocar parametros en cero


void producirValor(Qbuffer* buffer, uint8_t valor); //produce el valor y lo almacena en el buffer


uint8_t consumirValor(Qbuffer* buffer); // consume valor, y reduce la cantidad de valores del buffer

#endif UBUFFER_H_
