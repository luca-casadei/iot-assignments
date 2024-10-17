#include <stdlib.h>

/* 
 * Puts an element into the queue. 
 */
void enqueue(unsigned char pin);

/* 
 * Removes an element from the queue and gets it.
 */
void dequeue(void);

/* 
 * Initializes the queue and allocates memory.
 */
void queue_init(size_t queue_size);

/* 
 * Frees the memory allocated for the queue. 
 */
void queue_destroy(void);

/* 
 * Gets an element without dequeuing it.
 */
unsigned char peek(void);

/* 
 * Empties the queue.
 */
void queue_empty(void);