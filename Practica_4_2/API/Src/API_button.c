#include "API_button.h"
#include "stm32f4xx_hal.h"
#include <API_button.h>
// Board configuration
#define BUTTON_PORT         GPIOC // Blue button port
#define BUTTON_PIN          GPIO_PIN_13 // Blue button pin
#define BUTTON_PULL_LOW     true   // Set to 0 if active-high

bool_t readButton(void) {
	bool_t pin_state = HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN);
    // If active-low, invert logic
    return BUTTON_PULL_LOW ? !pin_state : pin_state;
}

