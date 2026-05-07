#include <display.h>
#include <game_io.h>
#include <systick.h>
#include <stdint.h>

void update_animation(DISPLAY* display) {
	switch (display->state) {
		// Just grab a timestamp and pass to IDLE
	    case DISPLAY_NEW:
	    	display->timestamp = get_ms_ticks();
	    	display->state = DISPLAY_IDLE;
	    	break;
		case DISPLAY_IDLE:
			if (elapsed(display->timestamp) >= display->start_delay) {
				turn_on(display->lights[display->index % display->lights_size]);
				display->timestamp = get_ms_ticks();
				display->state = DISPLAY_LIGHT_ON;
			} break;
		case DISPLAY_LIGHT_ON:
			if (elapsed(display->timestamp) >= display->flash_delay) {
				turn_off(display->lights[display->index % display->lights_size]);
				display->timestamp = get_ms_ticks();
				++display->index;
				display->state = DISPLAY_LIGHT_OFF;
			} break;
		case DISPLAY_LIGHT_OFF:
			// If the animation is complete, state becomes DISPLAY_DONE
			if (display->index == display->flash_count) {
				display->state = DISPLAY_DONE;
			// Otherwise, continue the animation
			} else if (elapsed(display->timestamp) >= display->flash_delay) {
				turn_on(display->lights[display->index % display->lights_size]);
				display->timestamp = get_ms_ticks();
				display->state = DISPLAY_LIGHT_ON;
			} break;
		case DISPLAY_DONE:
			break;
	}
}

void reset_display(DISPLAY* display) {
	display->state = DISPLAY_NEW;
	display->index = 0;
}
