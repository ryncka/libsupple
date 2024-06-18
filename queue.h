#include <stdint.h>
#pragma onc
#ifndef LIBSUPPLE_QUEUE_H
#define LIBSUPPLE_QUEUE_H

typedef struct queue* queue_t;

// Creates a new queue and initializes it
queue_t queue_new();

// Removes and returns the item at the front of the queue
// Returns nullptr if the queue is empty
uintptr_t* queue_pop(queue_t self);

// Returns the item at the front of the queue without removing it
// Returns nullptr if the queue is empty
uintptr_t* queue_peek(const queue_t self);

// Returns the number of entries in the queue
uint32_t queue_length(const queue_t self);

// Pushes an item onto the queue
// Returns true if successful, false if allocation failed
bool queue_push(queue_t self, uintptr_t* item);

// Destroys the queue and frees all allocated memory
void queue_destroy(queue_t self);

// Checks if the queue is empty
// Returns true if the queue is empty, false otherwise
bool queue_empty(const queue_t self);

#endif  // !LIBSUPPLE_QUEUE_H