#include "ubuffer.h"

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
void initCola(Qbuffer* buffer)
{
	buffer->size=0;
	buffer->head=0;
	buffer->tail=0;
}

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
void producirValor(Qbuffer* buffer, uint8_t valor)
{
	buffer->buffer[buffer->head]=valor;
	buffer->head=((buffer->head+1)%SIZEBUFFER);
	if(buffer->size<SIZEBUFFER)
		buffer->size++;
	else
	{
		/* Si el buffer est� lleno, se pierden los datos m�s antiguos */
		buffer->size=SIZEBUFFER;
		buffer->tail = buffer->head; /* buffer->head ya se encuentra apuntando al elemento
										siguiente al �ltimo valor escrito.
										Si el buffer est� lleno, ese elemento es el m�s antiguo */

	}
}
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
