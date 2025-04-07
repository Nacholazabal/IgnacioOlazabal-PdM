/*
 * API_uart.c
 *
 *  Created on: Apr 5, 2025
 *      Author: Ignacio
 */
#include "API_uart.h"

extern UART_HandleTypeDef huart2;

#define MAX_UART_STRING_SIZE 256

static uint8_t rxChar = 0;
static volatile bool_t uartFlag = false;

void uartClearTerminal(void) {
    const char *clear = "\033[2J\033[H";  // ANSI: clear + home
    uartSendString((uint8_t *)clear);
}

void uartPrintConfig(void) {
    char buffer[100];
    snprintf(buffer, sizeof(buffer),
             "UART Config:\r\nBaudRate: %lu\r\nWord Length: %lu bits\r\nStop Bits: %lu\r\nParity: %s\r\n",
             huart2.Init.BaudRate,
             (huart2.Init.WordLength == UART_WORDLENGTH_8B) ? 8 : 9,
             (huart2.Init.StopBits == UART_STOPBITS_1) ? 1 : 2,
             (huart2.Init.Parity == UART_PARITY_NONE) ? "None" :
             (huart2.Init.Parity == UART_PARITY_EVEN) ? "Even" : "Odd");
    uartSendString((uint8_t *)buffer);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART2) {
        uartFlag = true;
        // Re-armar la recepción de 1 byte
        HAL_UART_Receive_IT(&huart2, &rxChar, 1);
    }
}

void uartCheckCommand_IT(void) {
    if (uartFlag) {
        uartFlag = false;
        if (rxChar == 'c') {
            uartClearTerminal();
            uartPrintConfig();
        }
    }
}

bool_t uartInit(void) {
    if (HAL_UART_Init(&huart2) == HAL_OK) {
    	HAL_UART_Receive_IT(&huart2, &rxChar, 1);  // Inicia la recepción por interrupción
        char msg[] = "UART Inicializada correctamente. BaudRate: 115200\r\n";
        HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
        return true;
    } else {
        return false;
    }
}

void uartSendString(uint8_t * pstring) {
    if (pstring == NULL){
    	return;
    }

    uint16_t len = strlen((char *)pstring);

    if (len > 0 && len < MAX_UART_STRING_SIZE) {
        HAL_UART_Transmit(&huart2, pstring, len, HAL_MAX_DELAY);
    }
}

void uartSendStringSize(uint8_t * pstring, uint16_t size) {
    if (pstring == NULL || size == 0 || size > MAX_UART_STRING_SIZE){
    	return;
    }

    HAL_UART_Transmit(&huart2, pstring, size, HAL_MAX_DELAY);
}

void uartReceiveStringSize(uint8_t * pstring, uint16_t size) {
    if (pstring == NULL || size == 0 || size > MAX_UART_STRING_SIZE){
    	return;
    }

    HAL_UART_Receive(&huart2, pstring, size, HAL_MAX_DELAY);
}

