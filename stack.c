#include "stack.h"

#include <stdint.h>
#include <stdlib.h>

struct stack {
  int64_t     top;
  uint32_t    length;
  uintptr_t** elements;
};

stack_t stack_new(const uint32_t length) {
  stack_t stack = (stack_t)malloc(sizeof(struct stack));
  if (stack == nullptr) {
    return nullptr;
  }
  uintptr_t** elements = (uintptr_t**)malloc(sizeof(uintptr_t*) * length);
  if (elements == nullptr) {
    free(stack);
    return nullptr;
  }
  stack->top      = -1;
  stack->length   = length;
  stack->elements = elements;
  return stack;
}

void stack_destroy(stack_t self) {
  free(self->elements);
  free(self);
}

bool stack_push(stack_t self, uintptr_t* item) {
  if (stack_full(self)) {
    return false;
  }
  self->top++;
  self->elements[self->top] = item;
  return true;
}

bool stack_push_dynamic(stack_t self, uintptr_t* item) {
  if (stack_full(self)) {
    // allocate new elements array
    const uint32_t new_length   = self->length * 2;
    uintptr_t**    new_elements = malloc(sizeof(uintptr_t*) * new_length);
    if (new_elements == nullptr) {
      return false;
    }
    // copy existing elements to the new array
    for (uint32_t i = 0; i < self->length; i++) {
      new_elements[i] = self->elements[i];
    }
    free(self->elements);
    self->length   = new_length;
    self->elements = new_elements;
  }
  self->top++;
  self->elements[self->top] = item;
  return true;
}

uintptr_t* stack_peek(const stack_t self) {
  if (stack_empty(self)) {
    return nullptr;
  }
  return self->elements[self->top];
}

uintptr_t* stack_pop(stack_t self) {
  uintptr_t* item = stack_peek(self);
  if (item == nullptr) {
    return nullptr;
  }
  self->top--;
  return item;
}

bool stack_full(const stack_t self) {
  return self->top + 1 == self->length;
}

bool stack_empty(const stack_t self) {
  return self->top == -1;
}

int64_t stack_length(const stack_t self) {
  return self->top + 1;
}
