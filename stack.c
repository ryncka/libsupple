#include "stack.h"

#include <stdint.h>
#include <stdlib.h>

struct stack {
  int64_t     top;
  uint32_t    length;
  uintptr_t** elements;
};

struct dynamic_stack {
  stack_t stack;
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

dynstack_t dynstack_new(const uint32_t initial_length) {
  dynstack_t dynstack = malloc(sizeof(struct dynamic_stack));
  if (dynstack == nullptr) {
    return nullptr;
  }
  stack_t stack = stack_new(initial_length);
  if (stack == nullptr) {
    free(dynstack);
    return nullptr;
  }
  dynstack->stack = stack;
  return dynstack;
}

void dynstack_destroy(dynstack_t self) {
  stack_destroy(self->stack);
  free(self);
}

bool dynstack_push(dynstack_t self, uintptr_t* item) {
  if (stack_full(self->stack)) {
    uint32_t    old_lenght   = self->stack->length;
    uint32_t    new_length   = old_lenght * 2;
    uintptr_t** new_elements = malloc(sizeof(uintptr_t*) * new_length);
    if (new_elements == nullptr) {
      return false;
    }
    for (uint32_t i = 0; i < old_lenght; i++) {
      new_elements[i] = self->stack->elements[i];
    }
    free(self->stack->elements);
    self->stack->length   = new_length;
    self->stack->elements = new_elements;
  }
  return stack_push(self->stack, item);
}

uintptr_t* dynstack_peek(const dynstack_t self) {
  return stack_peek(self->stack);
}

uintptr_t* dynstack_t_pop(dynstack_t self) {
  return stack_pop(self->stack);
}

bool dynstack_empty(const dynstack_t self) {
  return stack_empty(self->stack);
}

int64_t dynstack_length(const dynstack_t self) {
  return stack_length(self->stack);
}
