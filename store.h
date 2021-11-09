#ifndef STORE_H
#define STORE_H

#include "page.h"

// The latency of a memory lookup from the store (much larger than the cache)
#define STORE_LATENCY 10

// A store is an array of pages
typedef struct {
    int numpages;
    page_t* pages;
} store_t;

// Initialize a memory store with the given number of pages
// This creates numpages of Pages in the store and initializes
// the content of each Page to 0
void store_init(store_t* store, int numpages);

// Return the page corresponding to the given memory location
page_t* store_get(store_t* store, int location);

#endif // STORE_H
