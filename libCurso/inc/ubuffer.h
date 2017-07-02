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
 * Función:
 * void initCola(Qbuffer* buffer): Inicialización del buffer circular
 *
 * Parámetros:
 * Qbuffer* buffer: Puntero a la estructura del buffer
 *
 * Devuelve:
 * void: Nada
 */
void initCola(Qbuffer* buffer); //se inicializa para colocar parametros en cero

/**
 * Función:
 * void producirValor(Qbuffer* buffer, uint8_t valor): Almacena un nuevo elemento en
 * el buffer e incrementa el índice de escritura. En caso de estar completo
 * el buffer, el nuevo elemento se almacena sobre el más antiguo.
 *
 * Parámetros:
 * Qbuffer* buffer: Puntero a la estructura del buffer
 * uint8_t valor: Valor del elemento a almacenar
 *
 * Devuelve:
 * void: Nada
 */
void producirValor(Qbuffer* buffer, uint8_t valor); //produce el valor y lo almacena en el buffer

/**
 * Función:
 * uint8_t consumirValor(Qbuffer* buffer): Se lee el valor más antiguo del buffer y
 * se incrementa el índice de lectura.
 *
 * Parámetros:
 * Qbuffer* buffer: Puntero a la estructura del buffer
 *
 * Devuelve:
 * uint8_t valor: Valor recuperado del buffer. Si el buffer está vacío devuelve 0
 */
uint8_t consumirValor(Qbuffer* buffer); // consume valor, y reduce la cantidad de valores del buffer

#endif UBUFFER_H_
