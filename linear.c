#include "linear.h"

#include <stdint.h>
#include <stdlib.h>

entry_t entry_new(const entry_t link, uintptr_t *item) {
  entry_t entry = (entry_t)malloc(sizeof(struct entry));
  if (entry == nullptr) {
    return nullptr;
  }
  entry->item = item;
  entry->link = link;
  return entry;
}

uint16_t entry_walk(const entry_t self, void (*callback)(uintptr_t *item)) {
  uint16_t count   = 0;
  entry_t  current = self;
  while (current != nullptr) {
    callback(current->item);
    current = current->link;
    count++;
  }
  return count;
}

uint16_t entry_destroy(entry_t root) {
  uint16_t count   = 0;
  entry_t  next    = nullptr;
  entry_t  current = root;
  while (current != nullptr) {
    next = current->link;
    free(current);
    current = next;
    count++;
  }
  return count;
}

orbit_t orbit_new(orbit_t link, uintptr_t *item) {
  orbit_t orbit = (orbit_t)malloc(sizeof(struct orbit));
  if (orbit == nullptr) {
    return nullptr;
  }
  // if there's a link to connect
  if (link != nullptr) {
    orbit->left = link;
    link->right = orbit;
  }
  orbit->right = nullptr;
  orbit->item  = item;
  return orbit;
}

uint16_t orbit_walk(const orbit_t self, void (*callback)(uintptr_t *item)) {
  uint16_t count   = 0;
  orbit_t  current = self;
  while (current != nullptr) {
    callback(current->item);
    current = current->right;
    count++;
  }
  return count;
}

uint16_t orbit_walklt(const orbit_t self, void (*callback)(uintptr_t *item)) {
  uint16_t count   = 0;
  orbit_t  current = self;
  while (current != nullptr) {
    callback(current->item);
    current = current->left;
    count++;
  }
  return count;
}

uint16_t orbit_destroy(orbit_t root) {
  uint16_t count   = 0;
  orbit_t  next    = nullptr;
  orbit_t  current = root;
  while (current != nullptr) {
    next = current->right;
    free(current);
    current = next;
    count++;
  }
  return count;
}

uint16_t orbit_destroylt(orbit_t root) {
  uint16_t count   = 0;
  orbit_t  prev    = nullptr;
  orbit_t  current = root;
  while (current != nullptr) {
    prev = current->left;
    free(current);
    current = prev;
    count++;
  }
  return count;
}
