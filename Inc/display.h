#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>
#include <game_io.h>

typedef enum {
	DISPLAY_NEW,
	DISPLAY_IDLE,
	DISPLAY_LIGHT_ON,
	DISPLAY_LIGHT_OFF,
	DISPLAY_DONE
} DISPLAY_STATE;

typedef struct {
	DISPLAY_STATE state;
	uint32_t timestamp;
	uint32_t index;
	LIGHT* lights;
	uint8_t lights_size;
	uint32_t start_delay;
	uint32_t flash_count;
	uint32_t flash_delay;
} DISPLAY;

void update_animation(DISPLAY* display);
void reset_display(DISPLAY* display);

#endif /* DISPLAY_H_ */
