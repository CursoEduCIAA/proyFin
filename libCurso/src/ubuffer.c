#include "ubuffer.h"


void initCola(Qbuffer* buffer)
{
	buffer->size=0;
	buffer->head=0;
	buffer->tail=0;
}

void producirValor(Qbuffer* buffer, uint8_t valor)
{
	buffer->buffer[buffer->head]=valor;
	buffer->head=((buffer->head+1)%SIZEBUFFER);
	if(buffer->size<SIZEBUFFER)
		buffer->size++;
	else
		buffer->size=SIZEBUFFER;
}

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
