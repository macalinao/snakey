#include <stdlib.h>

#include "snake.h"

snake *snake_new(int x, int y) {
    snake *s = (snake*) malloc(sizeof(snake));

    // Snakes start out as 3 segments
    segment *head = (segment*) malloc(sizeof(segment));
    segment *middle = (segment*) malloc(sizeof(segment));
    segment *tail = (segment*) malloc(sizeof(segment));

    head->next = middle;
    middle->prev = head;
    middle->next = tail;
    tail->prev = middle;

    s->head = head;
    s->tail = tail;

    return s;
}

void snake_update(snake *snake) {

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
