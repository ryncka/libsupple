#pragma once
#ifndef LIBSUPPLE_LINEAR_H
#define LIBSUPPLE_LINEAR_H

#include <stdint.h>

typedef struct entry *entry_t;
struct entry {
  uintptr_t *item;
  entry_t    link;
};

typedef struct orbit *orbit_t;
struct orbit {
  uintptr_t *item;
  orbit_t    left;
  orbit_t    right;
};

// entry_new creates a new entry with the given link and item.
// Returns a pointer to the newly created entry or nullptr if memory alloc
// fails.
entry_t entry_new(const entry_t link, uintptr_t *item);

// entry_walk traverses the linked list starting from self, invoking the
// callback for each entry. Returns the number of entries traversed.
uint16_t entry_walk(const entry_t self, void (*callback)(uintptr_t *item));

// entry_destroy deallocates memory for the entire linked list starting from
// root. Returns the number of entries deallocated.
uint16_t entry_destroy(entry_t root);

// orbit_new creates a new orbit with the given link and item.
// If link is not nullptr, updates link's right child to point to the new orbit.
// Returns a pointer to the newly created orbit or nullptr if memory alloc
// fails.
orbit_t orbit_new(orbit_t link, uintptr_t *item);

// orbit_walk traverses the binary tree starting from self, invoking the
// callback for each orbit in rightward direction. Returns the number of orbits
// traversed.
uint16_t orbit_walk(const orbit_t self, void (*callback)(uintptr_t *item));

// orbit_walklt traverses the binary tree starting from self, invoking the
// callback for each orbit in leftward direction. Returns the number of orbits
// traversed.
uint16_t orbit_walklt(const orbit_t self, void (*callback)(uintptr_t *item));

// orbit_destroy deallocates memory for the binary tree starting from root in
// rightward direction. Returns the number of orbits deallocated.
uint16_t orbit_destroy(orbit_t root);

// orbit_destroylt deallocates memory for the binary tree starting from root in
// leftward direction. Returns the number of orbits deallocated.
uint16_t orbit_destroylt(orbit_t root);

#endif  // !LIBSUPPLE_LINEAR_H
