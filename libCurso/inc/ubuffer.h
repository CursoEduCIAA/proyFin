#define SIZEBUFFER 50

struct Qbuffer{
	uint8_t buffer[SIZEBUFFER];
	uint8_t head;
	uint8_t tail;
	uint8_t size;
};

void initCola(struct Qbuffer* buffer); //se inicializa para colocar parametros en cero
void producirValor(struct Qbuffer* buffer, uint8_t valor); //produce el valor y lo almacena en el buffer
uint8_t consumirValor(struct Qbuffer* buffer); // consume valor, y reduce la cantidad de valores del buffer
