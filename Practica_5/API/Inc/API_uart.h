/*
 * API_uart.h
 *
 *  Created on: Apr 5, 2025
 *      Author: Ignacio
 */

#ifndef INC_API_UART_H_
#define INC_API_UART_H_

#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdbool.h>

typedef bool bool_t;

bool_t uartInit(void);
void uartSendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);

// Interrupt-driven command check (to call from main loop)
void uartCheckCommand_IT(void);

// Optional extras if you want to call them independently
void uartClearTerminal(void);
void uartPrintConfig(void);

#endif /* INC_API_UART_H_ */
