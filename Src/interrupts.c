#include <event.h>
#include <game_io.h>
#include <mcu.h>
#include <systick.h>

#define DEBOUNCE_THRESHOLD (15u)

// This interrupt handler loops through button_pins to see which pending bit request is set
// It then handles the request according to the pending request
void EXTI9_5_IRQHandler(void) {
	static uint32_t last_press_times[BUTTON_COUNT] = {0, 0, 0, 0};

	for (uint8_t i = 0; i < BUTTON_COUNT; ++i) {
		if (EXTI->PR & 1 << get_button_pin(i)) {
			EXTI->PR = 1 << get_button_pin(i);	// Clear pending bit

			uint32_t now = get_ms_ticks();

			if (is_pressed((BUTTON)i) && !last_press_times[i]) {
				last_press_times[i] = now;
			} else if (!is_pressed((BUTTON)i) && now - last_press_times[i] > DEBOUNCE_THRESHOLD) {
				EVENT event = {EVENT_BUTTON, (BUTTON)i};
				eq_push(event);
			}

		}
	}
}
