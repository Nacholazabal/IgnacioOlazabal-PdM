/*
 * API_debounce.h
 *
 *  Created on: Mar 27, 2025
 *      Author: Ignacio
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include <stdint.h>
#include <stdbool.h>

typedef bool bool_t;

// Initializes the debounce FSM. Sets initial state and debounce timer.
void debounceFSM_init(void);

// Updates the FSM. Must be called periodically.
void debounceFSM_update(void);

// Returns true if a valid button press event occurred since last check. Resets the event flag.
bool_t read_key(void);

#endif /* API_INC_API_DEBOUNCE_H_ */
