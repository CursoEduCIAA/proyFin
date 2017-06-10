#include "ubuffer.h"
#include "lpaquete.h"

#define SIZEPACKAGE 10

struct Qread{
	uint8_t paquete[SIZEPACKAGE];
	uint8_t indice;
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

void producirString(struct Qread* palabra, uint8_t valor)
{
	palabra->paquete[palabra->indice]=valor;
	palabra->indice++;
}

void borrarIndice(struct Qread* palabra)
{
	palabra->indice=0;
}

uint8_t ultimoIndice(struct Qread* palabra)
{
	if(palabra->indice==0)
		return 0;
	else
		return (palabra->indice-1);
}

uint8_t leerPosicionString(struct Qread* palabra, uint8_t indice)
{
	return (palabra->paquete[indice]);
}

void cerrarString(struct Qread* palabra)
{
	palabra->paquete[ultimoIndice(palabra)]='\0';
}

uint8_t* showPackage(struct Qread* palabra)
{
	return palabra->paquete;
}

void generarPaquete(struct Qbuffer* salida, struct Qread* entrada)
{
	uint8_t i=0, j=0;
	i=ultimoIndice(entrada);
	producirValor(salida,'*');
	for(j=0;j<=i;j++)
		producirValor(salida,leerPosicionString(entrada,j));
	producirValor(salida,'\n');
}

