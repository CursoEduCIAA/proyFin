/* Copyright 2016, XXXXXXXXX
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

/** \brief Blinking Bare Metal driver led
 **
 **
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal LED Driver
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif

#include "uart.h"

/*==================[macros and definitions]=================================*/
#define UART2_PIN_PKG	7
#define UART2_PIN_TXD	1
#define UART2_PIN_RXD	2

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
/* GPIO5 LEDs pins to OUTPUT */

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
void InitUart(uint8_t uart_id, uint32_t baud)
{
	/*
	 * MD_PDN: Enable pull-down resistor at pad
	 * MD_PLN: Disable pull-down and pull-up resistor at resistor at pad
	 * MD_EZI: Input buffer enable
	 * MD_ZI: Disable input glitch filter
	*/

	if(uart_id==UART2){
		/* UART2 (USB-UART) */
		Chip_UART_Init (LPC_USART2);
		Chip_UART_SetBaud (LPC_USART2, baud);

		Chip_UART_SetupFIFOS(LPC_USART2, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0);

		Chip_UART_TXEnable(LPC_USART2);

		Chip_SCU_PinMux(UART2_PIN_PKG, UART2_PIN_TXD, MD_PDN, FUNC6);              /* P7_1: UART2_TXD */
		Chip_SCU_PinMux(UART2_PIN_PKG, UART2_PIN_RXD, MD_PLN|MD_EZI|MD_ZI, FUNC6); /* P7_2: UART2_RXD */

		Chip_UART_ConfigData (LPC_USART2, UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS );

		// Configuracion de la interrupcion de la UART
		Chip_UART_IntEnable(LPC_USART2, UART_IER_THREINT);
		NVIC_SetPriority(USART2_IRQn, 1);
		NVIC_EnableIRQ(USART2_IRQn);
	}
}

uint8_t ReadUartByte(uint8_t uart_id)
{
	uint8_t dat=0;

	if(UART2==uart_id){
		dat = Chip_UART_ReadByte(LPC_USART2);
	}

	return dat;
}

void WriteUartByte(uint8_t uart_id, uint8_t byte)
{
	if(uart_id==UART2){
		Chip_UART_SendByte(LPC_USART2, byte);
	}
}

void WriteUartNBytes(uint8_t uart_id, uint8_t* data, uint32_t n)
{
	uint32_t i;

	if(uart_id==UART2){
		for(i=0; i<n; i++){
			Chip_UART_SendByte(LPC_USART2, data[i]);
		}
	}
}


void SendUartFloatAscii(uint8_t uart_id, float val, uint8_t n_dec)
{
	uint32_t i;
	char str[10];
	int entero, decimal, env;

	if(uart_id==UART2){
		entero=(int)val;
		Chip_UART_SendByte(LPC_USART2, entero+'0');
		Chip_UART_SendByte(LPC_USART2, ',');

		for(i=0; i<n_dec; i++){
			val=val-entero;
			val=val*10;
			entero=(int)val;
			Chip_UART_SendByte(LPC_USART2, entero+'0');
		}
	}
}

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




/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
