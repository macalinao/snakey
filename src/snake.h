/**
 * Represents a segment of the snake.
 */
typedef struct segment {
    struct segment *prev;
    struct segment *next;

    int x;
    int y;
} segment;

/**
 * Represents a direction a snake can be travelling.
 */
typedef enum {
    DIR_U,
    DIR_L,
    DIR_R,
    DIR_D
} direction;

/**
 * The snake itself.
 */
typedef struct {
    /**
     * The head of the snake.
     */
    segment *head;

    /**
     * The tail of the snake.
     */
    segment *tail;

    /**
     * The direction the snake is facing.
     */
    direction dir;

    /**
     * The amount of segments the snake still needs to append
     * and add to its body.
     */
    int segments_left;

    /**
     * The length of the snake.
     */
    int length;
} snake;

snake *snake_new(int x, int y);

void snake_advance(snake *snake);

void snake_render(snake *snake);
