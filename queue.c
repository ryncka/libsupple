#include "queue.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "linear.h"
#include "stack.h"

struct queue {
  entry_t  root;
  entry_t  last;
  stack_t  idle;
  uint32_t number_of_entry;
};

queue_t queue_new() {
  stack_t stack = stack_new(25);
  if (stack == nullptr) {
    return nullptr;
  }
  queue_t queue = malloc(sizeof(struct queue));
  if (queue == nullptr) {
    stack_destroy(stack);
    return nullptr;
  }
  queue->root            = nullptr;
  queue->last            = nullptr;
  queue->idle            = stack;
  queue->number_of_entry = 0;
  return queue;
}

bool queue_push(queue_t self, uintptr_t* item) {
  entry_t entry = nullptr;

  // Check if the idle stack is empty; if so, create a new entry
  if (stack_empty(self->idle)) {
    entry = entry_new(self->last, item);
  } else {
    entry = (entry_t)stack_pop(self->idle);
  }

  // Check if entry creation or stack pop failed
  if (entry == nullptr) {
    printf("entry is nullptr\n");
    return false;
  }

  // Initialize entry
  entry->item = item;
  entry->link = nullptr;

  if (self->root == nullptr) {
    // if queue is empty, update root pointer to the new entry
    self->root = entry;
  } else {
    // otherwise, link last entry to the new entry
    self->last->link = entry;
  }

  self->last = entry;
  self->number_of_entry++;

  return true;
}

uintptr_t* queue_pop(queue_t self) {
  // Check if the queue is empty
  if (queue_empty(self)) {
    return nullptr;
  }

  entry_t    entry = self->root->link;
  uintptr_t* item  = self->root->item;

  // Push the current root entry onto the idle stack for reuse
  if (!stack_push(self->idle, (uintptr_t*)self->root)) {
    // Free the root entry if pushing onto the stack fails
    free(self->root);
  }

  self->number_of_entry--;

  // If there are no more entries in the queue
  if (!self->number_of_entry) {
    self->root = nullptr;
    self->last = nullptr;
  } else {
    // Set root pointer to the next entry in the queue
    self->root = entry;
  }

  return item;
}

uintptr_t* queue_peek(const queue_t self) {
  if (queue_empty(self)) {
    return nullptr;
  }
  return self->root->item;
}

void queue_destroy(queue_t self) {
  // Free all items in the idle stack
  while (true) {
    uintptr_t* item = stack_pop(self->idle);
    if (item == nullptr) {
      break;  // Break the loop if the idle stack is empty
    }
    free(item);
  }
  // Free all entries in the queue
  entry_t entry = self->root;
  while (entry != nullptr) {
    self->root = entry->link;
    free(entry);
    entry = self->root->link;
    self->number_of_entry--;
  }
  // Destroy the idle stack
  stack_destroy(self->idle);
  // Free the queue structure itself
  free(self);
}

bool queue_empty(const queue_t self) {
  return !self->number_of_entry;
}

uint32_t queue_length(const queue_t self) {
  return self->number_of_entry;
}