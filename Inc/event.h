#ifndef EVENT_H_
#define EVENT_H_

#include <game_io.h>
#include <stdint.h>

#define EVENT_QUEUE_SIZE 16

typedef enum {
	EVENT_NONE,
	EVENT_DISPLAY_DONE,
	EVENT_TIMEOUT,
	EVENT_BUTTON
} EVENT_TYPE;

typedef struct {
	EVENT_TYPE type;
	BUTTON button;
} EVENT;

typedef struct {
	EVENT events[EVENT_QUEUE_SIZE];
	uint8_t head;
	uint8_t tail;
} EVENT_QUEUE;

void eq_push(EVENT event);
EVENT eq_pop(void);
uint8_t eq_is_empty(void);
uint8_t eq_is_full(void);
void eq_clear(void);

#endif /* EVENT_H_ */
