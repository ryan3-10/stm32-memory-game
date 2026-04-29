#include <components.h>

void turn_on(LIGHT light) {
	const uin8_t on_value = 1;

	switch (light) {
	case LIGHT_GREEN:
		gpio_write(LIGHT_PORT, GREEN_LIGHT_PIN, on_value);
		break;
	case LIGHT_WHITE:
		gpio_write(LIGHT_PORT, WHITE_LIGHT_PIN, on_value);
		break;
	case LIGHT_BLUE:
		gpio_write(LIGHT_PORT, BLUE_LIGHT_PIN, on_value);
		break;
	case LIGHT_RED:
		gpio_write(LIGHT_PORT, RED_LIGHT_PIN, on_value);
		break;
	}
}

void turn_off(LIGHT light) {
	const off_value = 0;

	switch (light) {
	case LIGHT_GREEN:
		gpio_write(LIGHT_PORT, GREEN_LIGHT_PIN, off_value);
		break;
	case LIGHT_WHITE:
		gpio_write(LIGHT_PORT, WHITE_LIGHT_PIN, off_value);
		break;
	case LIGHT_BLUE:
		gpio_write(LIGHT_PORT, BLUE_LIGHT_PIN, off_value);
		break;
	case LIGHT_RED:
		gpio_write(LIGHT_PORT, RED_LIGHT_PIN, off_value);
		break;
	}
}

void all_lights_off() {
	const off_value = 0;

	gpio_write(LIGHT_PORT, GREEN_LIGHT_PIN, off_value);
	gpio_write(LIGHT_PORT, WHITE_LIGHT_PIN, off_value);
	gpio_write(LIGHT_PORT, BLUE_LIGHT_PIN, off_value);
	gpio_write(LIGHT_PORT, RED_LIGHT_PIN, off_value);
}

uint8_t is_pressed(BUTTON button) {
	uint8_t output;
	switch (button) {
	case BUTTON_GREEN:
		output = !gpio_read(BUTTON_PORT, GREEN_BUTTON_PIN);
		break;
	case BUTTON_WHITE:
		output = !gpio_read(BUTTON_PORT, WHITE_BUTTON_PIN);
		break;
	case BUTTON_BLUE:
		output = !gpio_read(BUTTON_PORT, BLUE_BUTTON_PIN);
		break;
	case BUTTON_RED:
		output = !gpio_read(BUTTON_PORT, RED_BUTTON_PIN);
		break;
	}

	return output;
}

BUTTON get_input() {
	const uint8_t debounce_delay = 30;
	BUTTON pressed = BUTTON_NONE;

	while (pressed == BUTTON_NONE) {
		if (!gpio_read(BUTTON_PORT, GREEN_BUTTON_PIN)) pressed = BUTTON_GREEN;
		else if (!gpio_read(BUTTON_PORT, WHITE_BUTTON_PIN)) pressed = BUTTON_WHITE;
		else if (!gpio_read(BUTTON_PORT, BLUE_BUTTON_PIN)) pressed = BUTTON_BLUE;
		else if (!gpio_read(BUTTON_PORT, RED_BUTTON_PIN)) pressed = BUTTON_RED;
	}

	delay(debounce_delay); // debounce check

	if (!is_pressed(pressed)) {
	        return get_input();
	}

	turn_on((LIGHT)pressed);

	while (is_pressed(pressed));
	delay(debounce_delay);

	turn_off((LIGHT)pressed);

	return pressed;
}

void delay(uint32_t ms) {
    // 16000 ticks = 1 ms at 16 MHz
    SYSTICK->LOAD = 16000 - 1;

    // Clear current value register
    SYSTICK->VAL = 0;

    // Enable SysTick, use processor clock
    SYSTICK->CTRL = CTRL_ENABLE | CTRL_CLKSOURCE;

    for (uint32_t i = 0; i < ms; i++) {
        // Wait until COUNTFLAG is set
        while (!(SYSTICK->CTRL & CTRL_COUNTFLAG));
    }

    // Disable SysTick
    SYSTICK->CTRL = 0;
}







