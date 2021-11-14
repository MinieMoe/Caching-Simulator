#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "cache.h"


void cache_init(cache_t* cache, int size, store_t* store, policy_t policy) {
    cache->policy = policy;
    cache->size = size;
    cache->store = store;
    cache->cur = 0;

    /*reserve memories for array of entries within cache
        entries is array of cache entry, which is a struct with pointer to a page
        so basically a cache entry is a page; therefore, size (number of pages) = number of cache entries
    */
    cache->entries = (entry_t*)malloc(size*sizeof(entry_t));
    
    //initilize the caches within the array
    for(int i = 0; i < size; i++){
        cache->entries[i].page = NULL;
    }
}

unsigned char cache_get(cache_t* cache, int memory_location, int* latency) {
    //extracting page no. and offset from memory_location
    int offset = memory_location % PAGESIZE;
    int pageno = memory_location/PAGESIZE;

    //deciding whether to get info from cache or store
    if(cache_contains(cache,pageno)){
        //updates the caches?: telling the page has just been used?
        *latency = CACHE_LATENCY;                           //cache_latency is passed on if page is retrieve from cache
        
    }else{
        if(cache->cur + 1 == cache->size){
            //use the remove policy when the cache is full
        }
        *latency = STORE_LATENCY;                           //store_latency is passed on if page is retrieve from store
        /*Update the caches: 
            storing the pages in cache
            update cur
        */
        //cache->entries[cache->cur].page = &(cache->store->pages[memory_location]);
        
        cache->cur ++;

        //return cache->store->pages[memory_location].bytes;
    }
}
//is page_no and memory location the same??? what is memory location? is it the index of entry_t in entry_t array?
bool cache_contains(cache_t* cache, int page_no) {
    for(int i = 0; i < cache->size; i++){
        if(cache->entries[i].page->pageno == page_no){
            return true;
        }
    }
    return false;
}

//3 cache replacement policies
