#include <ncurses.h>
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

snake *snake_new(int x, int y, int color) {
    snake *s = (snake*) malloc(sizeof(snake));

    // Snakes start out as 3 segments
    segment *head = segment_new(x, y);
    segment *middle = segment_new(x + 1, y);
    segment *tail = segment_new(x + 2, y);

    segment_insert(head, tail, middle);

    s->head = head;
    s->tail = tail;

    s->length = 3;

    s->color = color;
    s->dir = DIR_L;

    return s;
}

void snake_advance(snake *snake, segment **old_tail) {
    // Prepend a new segment based on the current head
    segment *old_head = snake->head;

    int xoff = 0;
    int yoff = 0;

    switch (snake->dir) {
        case DIR_U: yoff = -1; break;
        case DIR_L: xoff = -1; break;
        case DIR_R: xoff =  1; break;
        case DIR_D: yoff =  1; break;
    }

    segment *new_head = segment_new(old_head->x + xoff, old_head->y + yoff);
    snake->head = new_head;

    old_head->prev = new_head;
    new_head->next = old_head;

    int *segs_left = &(snake->segments_left);

    if (*segs_left == 0) {
        // Remove the last segment; we aren't shrinking
        *old_tail = snake->tail;

        // Update the tail
        segment *new_tail = (*old_tail)->prev;
        new_tail->next = NULL;
        snake->tail = new_tail;
    } else {
        (snake->length)++;
        (*segs_left)--;
    }
}

void snake_draw(snake *snake, int xoff, int yoff) {
    attron(COLOR_PAIR(snake->color));
    segment *seg = snake->head;
    while (seg != NULL) {
        mvaddch(seg->y + yoff, seg->x + xoff, '+');
        seg = seg->next;
    }
    attroff(COLOR_PAIR(snake->color));
}
