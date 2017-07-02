#include "ubuffer.h"

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
void initCola(Qbuffer* buffer)
{
	buffer->size=0;
	buffer->head=0;
	buffer->tail=0;
}

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
void producirValor(Qbuffer* buffer, uint8_t valor)
{
	buffer->buffer[buffer->head]=valor;
	buffer->head=((buffer->head+1)%SIZEBUFFER);
	if(buffer->size<SIZEBUFFER)
		buffer->size++;
	else
	{
		/* Si el buffer está lleno, se pierden los datos más antiguos */
		buffer->size=SIZEBUFFER;
		buffer->tail = buffer->head; /* buffer->head ya se encuentra apuntando al elemento
										siguiente al último valor escrito.
										Si el buffer está lleno, ese elemento es el más antiguo */

	}
}
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
uint8_t consumirValor(Qbuffer* buffer)
{
	uint8_t valor=0;
	if (buffer->size>0)
		{
		valor=buffer->buffer[buffer->tail];
		buffer->tail=((buffer->tail+1)%SIZEBUFFER);
		buffer->size--;
		}
	return valor;
}
