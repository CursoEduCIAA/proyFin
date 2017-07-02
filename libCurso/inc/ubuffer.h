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

/**
 * Funci�n:
 * void initCola(Qbuffer* buffer): Inicializaci�n del buffer circular
 *
 * Par�metros:
 * Qbuffer* buffer: Puntero a la estructura del buffer
 *
 * Devuelve:
 * void: Nada
 */
void initCola(Qbuffer* buffer); //se inicializa para colocar parametros en cero

/**
 * Funci�n:
 * void producirValor(Qbuffer* buffer, uint8_t valor): Almacena un nuevo elemento en
 * el buffer e incrementa el �ndice de escritura. En caso de estar completo
 * el buffer, el nuevo elemento se almacena sobre el m�s antiguo.
 *
 * Par�metros:
 * Qbuffer* buffer: Puntero a la estructura del buffer
 * uint8_t valor: Valor del elemento a almacenar
 *
 * Devuelve:
 * void: Nada
 */
void producirValor(Qbuffer* buffer, uint8_t valor); //produce el valor y lo almacena en el buffer

/**
 * Funci�n:
 * uint8_t consumirValor(Qbuffer* buffer): Se lee el valor m�s antiguo del buffer y
 * se incrementa el �ndice de lectura.
 *
 * Par�metros:
 * Qbuffer* buffer: Puntero a la estructura del buffer
 *
 * Devuelve:
 * uint8_t valor: Valor recuperado del buffer. Si el buffer est� vac�o devuelve 0
 */
uint8_t consumirValor(Qbuffer* buffer); // consume valor, y reduce la cantidad de valores del buffer

#endif UBUFFER_H_
