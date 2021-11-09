#ifndef CACHE_H
#define CACHE_H

#include <stdbool.h>
#include "page.h"
#include "store.h"

// The latency of memory lookup from the cache (much smaller than the store)
#define CACHE_LATENCY 1

// A cache entry is a pointer to a page, and some metadata associated with it
typedef struct {
    page_t* page;

    // Add more metadata to the entry that you need
    // ...
} entry_t;

// Cache replacement policies
typedef enum {
    FIFO,
    LRU,
    MRU,
} policy_t;

// A cache is simply an array of cache entries of the given size
typedef struct cache {
    store_t* store;           // pointer to the store
    policy_t policy;          // the cache replacement policy
    int size;                 // the cache size
    entry_t* entries;         // the array of entries

    // Add more fields as needed
    // ...
} cache_t;



// Initialize a cache of the given size number of pages.
// The cache is backed by the store and is governed with the given cache
// replacement policy.
void cache_init(cache_t* cache, int size, store_t* store, policy_t policy);

// Return the value in memory corresponding to the given memory location.
// This function looks up whether the page exists in the cache first.
// If it does, it retrieves the Page from the cache, and updates the cache,
// and returns the value.
// If the Page is not present, it goes to the store to retrieve the page,
// updates the cache and returns the value.
// The time required for the get is set in the pointer latency.
unsigned char cache_get(cache_t* cache, int memory_location, int* latency);

// Return true if the page with page_no is present in the cache
bool cache_contains(cache_t* cache, int page_no);

#endif // CACHE_H
