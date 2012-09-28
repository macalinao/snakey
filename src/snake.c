#include <stdlib.h>

#include "snake.h"

/**
 * Creates a new segment.
 * @param  x The x of the segment.
 * @param  y The y of the segment.
 * @return   The segment.
 */
static segment *segment_new(int x, int y) {
    segment *s = (segment*) malloc(sizeof(segment));
    s->x = x;
    s->y = y;
    return s;
}

/**
 * Inserts a segment between the two given adjacent segments.
 * This is ONLY for adjacent segments, unless you want a memory leak.
 * 
 * @param prev The segment to be previous.
 * @param next The segment to be next.
 * @param s    The segment to insert between prev and next.
 */
static void segment_insert(segment *prev, segment *next, segment *s) {
    prev->next = s;
    next->prev = s;

    s->prev = prev;
    s->next = next;
}

snake *snake_new(int x, int y) {
    snake *s = (snake*) malloc(sizeof(snake));

    // Snakes start out as 3 segments
    segment *head = segment_new(x, y);
    segment *middle = segment_new(x + 1, y);
    segment *tail = segment_new(x + 2, y);

    segment_insert(head, tail, middle);

    s->head = head;
    s->tail = tail;

    return s;
}

void snake_update(snake *snake) {
    // Prepend a new segment based on the current head
    segment *next = (segment*) malloc(sizeof(segment));
    segment *head = snake->head;

    next->next = head;
}

void snake_render(snake *snake) {

}

int snake_length(snake *snake) {
    int length;

    segment *seg = snake->head;
    while (seg->next != snake->tail) {
        length++;
    }

    return length;
}
