#pragma once
#ifndef LIBSUPPLE_STACK_H
#define LIBSUPPLE_STACK_H

#include <stdint.h>

typedef struct stack* stack_t;

typedef struct dynamic_stack* dynstack_t;

// stack_new creates a new stack with the given length.
// Returns a pointer to the newly created stack or nullptr if memory alloc
// fails.
stack_t stack_new(const uint32_t length);

// stack_destroy deallocates memory for the stack and its elements.
void stack_destroy(stack_t self);

// stack_full checks if the stack is full.
// Returns true if the stack is full, false otherwise.
bool stack_full(const stack_t self);

// stack_empty checks if the stack is empty.
// Returns true if the stack is empty, false otherwise.
bool stack_empty(const stack_t self);

// stack_length returns the number of elements currently in the stack.
int64_t stack_length(const stack_t self);

// stack_push pushes an item onto the stack.
// Returns true if the item was successfully pushed, false if the stack is full.
bool stack_push(stack_t self, uintptr_t* item);

// stack_push_dynamic pushes an item onto the stack, dynamically resizing the
// stack if necessary. Returns true if the item was successfully pushed, false
// if memory allocation fails.
bool stack_push_dynamic(stack_t self, uintptr_t* item);

// stack_peek returns the item at the top of the stack without removing it.
// Returns nullptr if the stack is empty.
uintptr_t* stack_peek(const stack_t self);

// stack_pop removes and returns the item at the top of the stack.
// Returns nullptr if the stack is empty.
uintptr_t* stack_pop(stack_t self);

#endif  // !LIBSUPPLE_STACK_H