/*
 * API_debounce.c
 *
 *  Created on: Mar 27, 2025
 *      Author: Ignacio
 */
// === Headers files inclusions ==================================================================================== //
#include <stdint.h>
#include <stdbool.h>

#include <API_debounce.h>
#include <API_delay.h>
#include <API_button.h>
#include <API_uart.h>

// === Macros definitions ========================================================================================== //
#define DEBOUNCE_PERIOD_MS (40U)
#define BUTTON_PRESSED   true
#define BUTTON_RELEASED  false

// === Private data type declarations ============================================================================== //
// This new type define the states of the debouncing state machine
typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
}debounce_state_t;

static debounce_state_t current_state;
static delay_t delay_debounce;
static bool_t pressed_key;

void debounceFSM_init(void){
	current_state = BUTTON_UP;
	delayInit(&delay_debounce, DEBOUNCE_PERIOD_MS);
}

static void on_button_pressed(void){
	uartSendString((uint8_t *)"Flanco ascendente detectado\r\n");
}

static void on_button_released(void){
	uartSendString((uint8_t *)"Flanco descendente detectado\r\n");
	pressed_key = true;
}

void debounceFSM_update(void){
	bool_t button_status = readButton();
	switch(current_state){
		case BUTTON_UP:
			if(button_status == BUTTON_PRESSED){
				current_state = BUTTON_FALLING;
				delayInit(&delay_debounce, DEBOUNCE_PERIOD_MS);
			}
			break;
		case BUTTON_FALLING:
			if(delayRead(&delay_debounce)){
				if(button_status == BUTTON_PRESSED){
					on_button_pressed();
					// nothing happens when button is pressed, only when released
					current_state = BUTTON_DOWN;
				}else{
					current_state = BUTTON_UP;
				}
			}
			break;
		case BUTTON_DOWN:
			if(button_status == BUTTON_RELEASED){
				current_state = BUTTON_RAISING;
				delayInit(&delay_debounce, DEBOUNCE_PERIOD_MS);
			}
			break;
		case BUTTON_RAISING:
			if(delayRead(&delay_debounce)){
				if(button_status == BUTTON_RELEASED){
					on_button_released();
					current_state = BUTTON_UP;
				}else{
					current_state = BUTTON_DOWN;
				}
			}
			break;
		default:
			debounceFSM_init();
		break;
	}
}

bool_t read_key(void){
	if(pressed_key == true){
		pressed_key = false;
		return true;
	}
	return false;
}

