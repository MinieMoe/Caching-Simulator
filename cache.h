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
    //  maybe a variable telling the order of page/entry was put into cache array
    //int index;              //entry_t position in entry_t* array
    int timestamp;            //record when a page has just been used recently
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
    //maybe an array to track the order of page/entry was put into cache array
    int cur;                  //USED ONLY WHEN CACHE IS EMPTY - the latest index of entries; increment every time a new page is stored into cache 
    int timer;                //timer to keep track of how many times a page is used; tell which page is most recently used
    int hit;                  //store the index of cache that is just hit
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

//Store a new page into cache at cacheIndex
void cache_miss(cache_t* cache, int cacheIndex, int memory_location,int offset);

/*MRU -evict the most recently used cache: utilize timer and timestamp
    check which page has timestamp == timer --> that page is MRU
        timer tells the latest time a page is used
    put the new page into that slot
*/
unsigned char evictMRU(cache_t* cache, int memory_location,int offset);

/*LRU - evict the least recently used cache: utilize timer and timestamp
    check which page in cache has the smallest timestamp --? that page is LRU
    put the new page into that slot
*/
unsigned char evictLRU(cache_t* cache, int memory_location,int offset);

/*FIFO - first added to array is first out: use array-based queue
    shift the array toward the front to push the first page in cache out
*/
unsigned char evictFIFO(cache_t* cache, int memory_location,int offset);

#endif // CACHE_H
