#include "ubuffer.h"

void initPaquete(struct Qread*);
void lecturaPaquete(struct Qbuffer*, struct Qread*);
void producirString(struct Qread*, unsigned char);
void borrarIndice(struct Qread*);
void cerrarString(struct Qread*);
unsigned char ultimoIndice(struct Qread*);
unsigned char leerPosicionString(struct Qread*, unsigned char);
unsigned char* showPackage(struct Qread*);
void generarPaquete(struct Qbuffer*, struct Qread*);
