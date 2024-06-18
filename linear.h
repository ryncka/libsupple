#pragma once
#ifndef LIBSUPPLE_LINEAR_H
#define LIBSUPPLE_LINEAR_H

#include <stdint.h>

// entry_t is a pointer to struct entry
typedef struct entry *entry_t;
struct entry {
  uintptr_t *item;
  entry_t    link;
};

// orbit_t is a pointer to struct orbit
typedef struct orbit *orbit_t;
struct orbit {
  uintptr_t *item;
  orbit_t    left;
  orbit_t    right;
};

// Creates a new entry node and returns a pointer to it
entry_t entry_new(const entry_t link, uintptr_t *item);

// Walk through the linked list starting from 'self' and apply 'callback' to
// each item Returns the number of entries walked
uint16_t entry_walk(const entry_t self, void (*callback)(uintptr_t *item));

// Destroy the linked list starting from 'root' and free memory
// Returns the number of entries destroyed
uint16_t entry_destroy(entry_t root);

// Creates a new orbit node and returns a pointer to it
orbit_t orbit_new(orbit_t link, uintptr_t *item);

// Walk through the linked list starting from 'self' and apply 'callback' to
// each item Returns the number of orbits walked
uint16_t orbit_walk(const orbit_t self, void (*callback)(uintptr_t *item));

// Walk through the linked list starting from 'self' and apply 'callback' to
// each item, moving leftwards (towards left orbits). Returns the number of
// orbits walked.
uint16_t orbit_walklt(const orbit_t self, void (*callback)(uintptr_t *item));

// Destroy the linked list starting from 'root' and free memory
// Returns the number of orbits destroyed
uint16_t orbit_destroy(orbit_t root);

// Destroy the linked list starting from 'root' and free memory,
// moving leftwards (towards left orbits).
// Returns the number of orbits destroyed.
uint16_t orbit_destroylt(orbit_t root);

#endif  // !LIBSUPPLE_LINEAR_H
