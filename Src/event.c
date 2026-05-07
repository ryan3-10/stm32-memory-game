#include <event.h>

static EVENT_QUEUE eq;

void eq_push(EVENT event) {
	// It is humanly impossible to press the buttons fast enough to fill up the queue,
	// but we'll add this check anyway for the sake of technical correctness
	if (!eq_is_full()) {
		eq.events[eq.head] = event;
		eq.head = (eq.head + 1) % EVENT_QUEUE_SIZE;
	}
}

EVENT eq_pop() {
	if (eq_is_empty()) {
		return EVENT_NONE;
	}

	EVENT event = eq.events[eq.tail];
	eq.tail = (eq.tail + 1) % EVENT_QUEUE_SIZE;
	return event;
}

uint8_t eq_is_empty() {
	return eq.tail == eq.head;
}

uint8_t eq_is_full() {
	return (eq.head + 1) % EVENT_QUEUE_SIZE == eq.tail;
}

void eq_clear() {
	eq.head = 0;
	eq.tail = 0;
}
