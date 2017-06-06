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

-----------------------------------------------------------


void lecturaPaquete(struct Qbuffer* bCircular, struct Qread* lPaquete)
{
	while(consumirValor(bCircular)=='*');
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

void borrarIndice(struct Qread* palabra)																			{palabra->indice=0;}

unsigned char ultimoIndice(struct Qread* palabra)															{return (palabra->indice);}

unsigned char leerPosicionString(struct Qread* palabra, unsigned char indice)	{return (palabra->paquete[indice]);}

void cerrarString(struct Qread* palabra)																			{palabra->paquete[(palabra->indice)+1]='\0';}

#define SIZEPACKAGE 10
struct Qread{
	unsigned char paquete[SIZEPACKAGE];
	unsigned char indice;
};
void initPaquete(struct Qread* lPaquete)
{
	unsigned i=0;
	for(i=SIZEPACKAGE;i>0;i--)
		lPaquete->paquete[i]=0;
	lPaquete->indice=0;
}
