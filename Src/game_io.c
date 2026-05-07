#include <board.h>
#include <game_io.h>
#include <gpio.h>
#include <systick.h>
#include <stdint.h>
#include <event.h>

volatile BUTTON pressed = BUTTON_NONE;

uint8_t light_pins[] = {
	GREEN_LIGHT_PIN,
	WHITE_LIGHT_PIN,
	BLUE_LIGHT_PIN,
	RED_LIGHT_PIN
};

uint8_t button_pins[] = {
	GREEN_BUTTON_PIN,
	WHITE_BUTTON_PIN,
	BLUE_BUTTON_PIN,
	RED_BUTTON_PIN
};

void turn_on(LIGHT light) {
	gpio_write(LIGHT_PORT, light_pins[light], 1);
}

void turn_off(LIGHT light) {
	gpio_write(LIGHT_PORT, light_pins[light], 0);
}

void set_light(LIGHT light, uint8_t value) {
	gpio_write(LIGHT_PORT, light_pins[light], value);
}

void all_lights_off(void) {
	for (uint8_t i = 0; i < BUTTON_COUNT; ++i) {
		gpio_write(LIGHT_PORT, light_pins[i], 0);
	}
}

uint8_t is_pressed(BUTTON button) {
	return !gpio_read(BUTTON_PORT, button_pins[button]);
}

BUTTON get_input(void) {
	const uint8_t debounce_ticks = 30;
	static BUTTON current = BUTTON_NONE;
	static INPUT_STATE state = INPUT_IDLE;
	static uint32_t press_time;
	static uint32_t release_time;

	switch (state) {
		case INPUT_IDLE:
			if (pressed != BUTTON_NONE) {
				current = pressed;
				pressed = BUTTON_NONE;
				press_time = get_ms_ticks();
				state = INPUT_DEBOUNCE_PRESS;
			} break;
		case INPUT_DEBOUNCE_PRESS:
			if (get_ms_ticks() - press_time >= debounce_ticks) {
				turn_on((LIGHT)current);
				state = INPUT_WAIT_RELEASE;
			} break;
		case INPUT_WAIT_RELEASE:
			if (!is_pressed(current)) {
				release_time = get_ms_ticks();
				state = INPUT_DEBOUNCE_RELEASE;
			} break;
		case INPUT_DEBOUNCE_RELEASE:
			if (get_ms_ticks() - release_time >= debounce_ticks) {
				turn_off((LIGHT)current);
				state = INPUT_IDLE;
				return current;
			}
	}
		pressed = BUTTON_NONE;
		return BUTTON_NONE;
}

// This interrupt handler loops through button_pins to see which pending bit request is set
// It then sets pressed according to the pending request
void EXTI9_5_IRQHandler(void) {
	for (uint8_t i = 0; i < BUTTON_COUNT; ++i) {
		if (EXTI->PR & 1 << button_pins[i]) {
			EVENT event = {
				is_pressed((BUTTON)i) ? EVENT_BUTTON_PRESSED : EVENT_BUTTON_RELEASED,
				(BUTTON)i,
				get_ms_ticks()
			};
			eq_push(event);
			EXTI->PR = 1 << button_pins[i];
			break;
		}
	}
}

