#include "ubuffer.h"

void initCola(struct Qbuffer* bCircular)
{
	bCircular->size=0;
	bCircular->head=0;
	bCircular->tail=0;
}

void producirValor(struct Qbuffer* bCircular, uint8_t valor)
{
	bCircular->buffer[bCircular->head]=valor;
	bCircular->head=((bCircular->head+1)%SIZEBUFFER);
	bCircular->size++;
}

uint8_t consumirValor(struct Qbuffer* bCircular)
{
	uint8_t valor=0;
	if (bCircular->size>0)
		{
		valor=bCircular->buffer[bCircular->tail];
		bCircular->tail=((bCircular->tail+1)%SIZEBUFFER);
		bCircular->size--;
		}
	return valor;
}
