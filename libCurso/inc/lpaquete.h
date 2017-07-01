#ifndef LPAQUETE_H_
#define LPAQUETE_H_

#include "ubuffer.h"

#include "stdint.h"

#define SIZEPACKAGE 10

typedef struct Qread{
	uint8_t paquete[SIZEPACKAGE];
	uint8_t indice;
}Qread;

// void initPaquete(Qread*);


void lecturaPaquete(Qbuffer* bCircular, Qread* lPaquete);


void producirString(Qread* palabra, uint8_t valor);


void borrarIndice(Qread* palabra);


uint8_t ultimoIndice(Qread* palabra);


uint8_t leerPosicionString(Qread* palabra, uint8_t indice);


void cerrarString(Qread* palabra);


uint8_t showPackage(Qread* palabra); // sacado puntero


void generarPaquete(Qbuffer* salida, Qread* entrada);

#endif LPAQUETE_H_
