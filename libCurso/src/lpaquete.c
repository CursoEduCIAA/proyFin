#include "ubuffer.h"
#include "lpaquete.h"

#define SIZEPACKAGE 10

struct Qread{
	unsigned char paquete[SIZEPACKAGE];
	unsigned char indice;
};

void lecturaPaquete(struct Qbuffer* bCircular, struct Qread* lPaquete)
{
	while(consumirValor(bCircular)!='*');
	producirString(lPaquete,consumirValor(bCircular));

	while(leerPosicionString(lPaquete, ultimoIndice(lPaquete))!='\n')
		{
		if(leerPosicionString(lPaquete, ultimoIndice(lPaquete))=='*')
			borrarIndice(lPaquete);
		else
			producirString(lPaquete,consumirValor(bCircular));
		}
	cerrarString(lPaquete);
}

void producirString(struct Qread* palabra, unsigned char valor)
{
	palabra->paquete[palabra->indice]=valor;
	palabra->indice++;
}

void borrarIndice(struct Qread* palabra)
{
	palabra->indice=0;
}

unsigned char ultimoIndice(struct Qread* palabra)
{
	if(palabra->indice==0)
		return 0;
	else
		return (palabra->indice-1);
}

unsigned char leerPosicionString(struct Qread* palabra, unsigned char indice)
{
	return (palabra->paquete[indice]);
}

void cerrarString(struct Qread* palabra)
{
	palabra->paquete[(palabra->indice)+1]='\0';
}

