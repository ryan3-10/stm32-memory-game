#include <event.h>
#include <game_io.h>
#include <mcu.h>
#include <systick.h>

#define DEBOUNCE_THRESHOLD (100u)

uint8_t debounce_detected(EVENT current) {
	static EVENT previous;

	uint8_t is_debounce = (
		current.timestamp - previous.timestamp < DEBOUNCE_THRESHOLD &&
		current.type == previous.type &&
		current.button == previous.button
	);
	previous = current;
	return is_debounce;
}

// This interrupt handler loops through button_pins to see which pending bit request is set
// It then sets pressed according to the pending request
void EXTI9_5_IRQHandler(void) {
	for (uint8_t i = 0; i < BUTTON_COUNT; ++i) {
		if (EXTI->PR & 1 << get_button_pin(i)) {
			EXTI->PR = 1 << get_button_pin(i);	// Clear pending bit

			EVENT event = {
				EVENT_BUTTON,
				(BUTTON)i,
				get_ms_ticks()
			};

			if (!debounce_detected(event)) {
				eq_push(event);
			}
		}
	}
}
