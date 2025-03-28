#ifndef API_INC_API_BUTTON_H_
#define API_INC_API_BUTTON_H_

#include <stdbool.h>
typedef bool bool_t;
// Initializes GPIO configurations, but on this case no other conf are needed
//void debounceGpioInit(void);

// Reads current button status:
// Returns true if button is PRESSED, false if RELEASED
// This helps abstract from the voltage value of the pressed or released button
// Basically if its pulled low or high, debounce shouldnt know that
bool_t readButton(void);

#endif /* API_INC_API_BUTTON_H_ */
