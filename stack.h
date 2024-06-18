#pragma once
#ifndef LIBSUPPLE_STACK_H
#define LIBSUPPLE_STACK_H

#include <stdint.h>

typedef struct stack* stack_t;

// Creates a new stack with the specified initial length
stack_t stack_new(const uint32_t length);

// Destroys the stack, freeing allocated memory
void stack_destroy(stack_t self);

// Pushes an item onto the stack
// Returns true if successful, false if stack is full
bool stack_push(stack_t self, uintptr_t* item);

// Pushes an item onto the stack, dynamically resizing if necessary
// Returns true if successful, false if allocation failed
bool stack_push_dynamic(stack_t self, uintptr_t* item);

// Returns the item at the top of the stack without removing it
// Returns nullptr if stack is empty
uintptr_t* stack_peek(const stack_t self);

// Pops the item at the top of the stack
// Returns nullptr if stack is empty
uintptr_t* stack_pop(stack_t self);

// Returns the current length (number of elements) in the stack
int64_t stack_length(const stack_t self);

// Checks if the stack is full
bool stack_full(const stack_t self);

// Checks if the stack is empty
bool stack_empty(const stack_t self);

#endif  // !LIBSUPPLE_STACK_H