/* Copyright 2016, 6ta Escuela RUSE
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20160602 v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "proyFin.h"       /* <= own header */

#include "adc.h"
#include "uart.h"
#include "led.h"

#include "ubuffer.h"

/*==================[internal data declaration]==============================*/



/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */

void SendFloat(Qbuffer* sendBuffer, float val, uint8_t n_dec);
void SendByte(Qbuffer* sendBuffer, uint8_t byte);
void uartSend(Qbuffer* sendBuffer, uint8_t data);

volatile Qbuffer tx_buffer;


int main(void)
{
	uint8_t valorADC_H, valorADC_L;
	uint16_t valorADC;
	uint32_t i;
	float fVal;


	uint8_t j;


	adc_init(1);
	InitUart(UART2, 9600);
	leds_init();

	initCola(&tx_buffer);

	// adc_convertir();
	// valorADC=adc_pool(1);

	while(1){
		adc_convertir();
		valorADC=adc_pool(1);

		fVal=valorADC;
		fVal=(fVal*3.3)/1023;


		// Test!!!
		for(j=1;j<=40;j++)
		{
			uartSend(&tx_buffer, j + '0');
		}
		uartSend(&tx_buffer, '\r');
		uartSend(&tx_buffer, '\n');


		//SendFloat(&tx_buffer, fVal, 2);
		//SendByte(&tx_buffer, '\r');
		//Chip_UART_IntEnable(LPC_USART2, UART_IER_THREINT);


		//SendUartFloatAscii(UART2, fVal, 2);
		//WriteUartByte(UART2, '\r');

		//valorADC_L=(uint8_t)(valorADC&0x00FF);
		//valorADC_H=(uint8_t)((valorADC>>8)&0x00FF);

		//WriteUartByte(UART2, valorADC_L);
		//WriteUartByte(UART2, valorADC_H);

		for(i=0; i<6000000; i++);
	}
}


void uartSend(Qbuffer* sendBuffer, uint8_t data)
{
	producirValor(sendBuffer,data);
	if(sendBuffer->size == 1)
	{
		Chip_UART_SendByte(LPC_USART2, data);
		Chip_UART_IntEnable(LPC_USART2, UART_IER_THREINT);
	}
}


/**
 * Función:
 * void SendFloat(Qbuffer* sendBuffer, float val, uint8_t n_dec): Formatea y carga el valor de tensión
 * el buffer de salida de transmisión.
 *
 * Parámetros:
 * Qbuffer* sendBuffer: buffer de salida
 * float val: valor de tensión
 * uint8_t n_dec: cantidad de decimales que se quieren representar
 *
 * Devuelve:
 * void: nada
 */
void SendFloat(Qbuffer* sendBuffer, float val, uint8_t n_dec)
{
	int entero,i;

	entero=(int)val;
	if(sendBuffer->size == 0)
	{
		Chip_UART_SendByte(LPC_USART2, entero + '0');
		Chip_UART_IntEnable(LPC_USART2, UART_IER_THREINT);
	}
	else
	{
		producirValor(sendBuffer,entero + '0');
	}
	producirValor(sendBuffer, ',');

	for(i=0; i<n_dec; i++){
		val=val-entero;
		val=val*10;
		entero=(int)val;
		producirValor(sendBuffer,entero + '0');
	}
}

/**
 * Función:
 * void SendByte(Qbuffer* sendBuffer, uint8_t byte): Agrega un byte al buffer circular
 * de transmisión
 *
 * Parámetros:
 * Qbuffer* sendBuffer: buffer de salida
 * uint8_t byte: byte a agregar
 *
 * Devuelve:
 * void: nada
 */
void SendByte(Qbuffer* sendBuffer, uint8_t byte)
{
	producirValor(sendBuffer,byte);
}

void ISR_RIT_Handler(void)
{

}

void teclas_procesar(void)
{

}

void leds_procesar(void)
{

}

void UART2_IRQHandler(void)
{
	uint8_t tx;
	uint8_t status = Chip_UART_ReadLineStatus(LPC_USART2);
	static uint8_t primer_elemento = 0;

	/* Handle transmit interrupt if enabled */
	if(status & UART_LSR_THRE)
	//if (LPC_USART2->IER & UART_IER_THREINT)
	{
		tx = consumirValor(&tx_buffer);

		if(tx_buffer.size == 0)	//Buffer vacío
		{
			Chip_UART_IntDisable(LPC_USART2, UART_IER_THREINT);
			primer_elemento = 0;
		}
		else	// Existen elementos a enviar
		{
			if(primer_elemento != 0)
			{
				Chip_UART_SendByte(LPC_USART2, tx);
			}
			primer_elemento = 1;
		}
	}

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

