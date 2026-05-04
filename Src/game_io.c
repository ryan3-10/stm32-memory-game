#include <board.h>
#include <game_io.h>
#include <systick.h>

BUTTON pressed;

void turn_on(LIGHT light) {
	switch (light) {
	case LIGHT_GREEN:
		gpio_write(LIGHT_PORT, GREEN_LIGHT_PIN, 1);
		break;
	case LIGHT_WHITE:
		gpio_write(LIGHT_PORT, WHITE_LIGHT_PIN, 1);
		break;
	case LIGHT_BLUE:
		gpio_write(LIGHT_PORT, BLUE_LIGHT_PIN, 1);
		break;
	case LIGHT_RED:
		gpio_write(LIGHT_PORT, RED_LIGHT_PIN, 1);
		break;
	}
}

void turn_off(LIGHT light) {
	switch (light) {
	case LIGHT_GREEN:
		gpio_write(LIGHT_PORT, GREEN_LIGHT_PIN, 0);
		break;
	case LIGHT_WHITE:
		gpio_write(LIGHT_PORT, WHITE_LIGHT_PIN, 0);
		break;
	case LIGHT_BLUE:
		gpio_write(LIGHT_PORT, BLUE_LIGHT_PIN, 0);
		break;
	case LIGHT_RED:
		gpio_write(LIGHT_PORT, RED_LIGHT_PIN, 0);
		break;
	}
}

void all_lights_off() {
	gpio_write(LIGHT_PORT, GREEN_LIGHT_PIN, 0);
	gpio_write(LIGHT_PORT, WHITE_LIGHT_PIN, 0);
	gpio_write(LIGHT_PORT, BLUE_LIGHT_PIN, 0);
	gpio_write(LIGHT_PORT, RED_LIGHT_PIN, 0);
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
	// Should never reach here, but I'm getting a warning for not including it
	case BUTTON_NONE:
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

// Interrupt handler
void EXTI9_5_IRQHandler() {
	if (EXTI->PR & 1 << GREEN_BUTTON_PIN) {
		pressed = BUTTON_GREEN;
		EXTI->PR = 1 << GREEN_BUTTON_PIN;
	} else if (EXTI->PR & 1 << WHITE_BUTTON_PIN) {
		pressed = BUTTON_WHITE;
		EXTI->PR = 1 << WHITE_BUTTON_PIN;
	} else if (EXTI->PR & 1 << BLUE_BUTTON_PIN) {
		pressed = BUTTON_BLUE;
		EXTI->PR = 1 << BLUE_BUTTON_PIN;
	} else if (EXTI->PR & 1 << RED_BUTTON_PIN) {
		pressed = BUTTON_RED;
		EXTI->PR = 1 << RED_BUTTON_PIN;
	}
}

