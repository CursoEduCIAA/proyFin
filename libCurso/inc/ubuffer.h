#define SIZEBUFFER 50

struct Qbuffer{
	uint8_t buffer[SIZEBUFFER];
	uint8_t head;
	uint8_t tail;
	uint8_t size;
};
void initCola(struct Qbuffer* buffer);
void producirValor(struct Qbuffer* buffer, uint8_t valor);
uint8_t consumirValor(struct Qbuffer* buffer);
