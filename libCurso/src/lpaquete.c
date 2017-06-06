#include "ubuffer.h"
#include "lpaquete.h"

void lecturaPaquete (struct Qbuffer* bCircular, uint8_t lon)
{
	uint8_t paquete[lon];
	uint8_t indice=0;

	if(lon>SIZEBUFFER)
		return;
	while(consumirValor(bCircular)!='*'); //ac� estaba ==, lo cambi� a !=

	paquete[indice]=consumirValor(bCircular);

	while(paquete[indice]!='\n')
	{

		if(paquete[indice]=='*')
			indice=0;
		else
			indice++;


		paquete[indice]=consumirValor(bCircular);
	}

}
