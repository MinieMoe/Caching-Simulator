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
    cache->timer = 0;
    cache->hit = 0;

    /*reserve memories for array of entries within cache
        entries is array of cache entry, which is a struct with pointer to a page
        so basically a cache entry is a page; therefore, size (number of pages) = number of cache entries
    */
    cache->entries = (entry_t*)malloc(size*sizeof(entry_t));

    //initilize the caches within the array and its timestamp
    for(int i = 0; i < size; i++){
        cache->entries[i].page = NULL;
        cache->entries[i].timestamp = 0;
    }
}

unsigned char cache_get(cache_t* cache, int memory_location, int* latency) {
    //extracting page no. and offset from memory_location
    int offset = memory_location % PAGESIZE;
    int pageno = memory_location/PAGESIZE;

    //everytime a page/cache is used, increment the timer
    cache->timer ++;

    //deciding whether to get info from cache or store

        // CACHE_HIT: go to cache if item is in cache
    if(cache_contains(cache,pageno)){
        //updates the caches?: telling the page has just been used?
        *latency = CACHE_LATENCY;                                        //cache_latency is passed on if page is retrieve from cache
        cache->entries[cache->hit].timestamp == cache->timer;            //mark the cache's timestamp to keep track of when  it's used

        return page_get(cache->entries[cache->hit].page,offset);

    }else{//CACHE_MISS: go to Store (physical memory) to fetch data if NOT in cache
        *latency = STORE_LATENCY;                                        //store_latency is passed on if page is retrieve from store
        
        //use the remove policy when the cache is full
        if(cache->cur == cache->size){
            switch (cache->policy){
            case FIFO:
                return evictFIFO(cache,memory_location,offset);
                break;
            
            case LRU:
                return evictLRU(cache,memory_location,offset);
                break;
            case MRU:
                return evictMRU(cache,memory_location,offset);
                break;
            default:
                break;
            }
        }else{//if cache is not full, fetch page from store and append it at the end of cache/the entry_t* array
            cache_miss(cache,cache->cur,memory_location,offset);
            cache->cur ++;                                              //now that a new page is added to cache array, move to the next slot in cache
            return page_get(cache->entries[cache->cur-1].page,offset);
        }
    }
}

bool cache_contains(cache_t* cache, int page_no) {
    for(int i = 0; i < cache->size; i++){
        //check if the page has been initialized first to avoid segfault
        if(cache->entries[i].page == NULL){
            return false;
        //if it is initialtized, is it the page we're looking for
        }else if(cache->entries[i].page->pageno == page_no){
            cache->hit = i;
            return true;
        }   
    }
    //if after going through the entire cache and can't find the page, then it's not in there
    return false;

}

//store a new page into cache at cacheIndex
void cache_miss(cache_t* cache, int cacheIndex, int memory_location,int offset){
    /*Update the caches: 
                retrieve page from store and store it at the end of the array
                update cur
    */
            cache->entries[cacheIndex].page = store_get(cache->store,memory_location);
            cache->entries[cacheIndex].timestamp = cache->timer;        //mark the cache's timestamp to keep track of when  it's used
            
}

//3 cache replacement policies

/*MRU -evict the most recently used cache: utilize timer and timestamp
    check which page has timestamp == timer --> that page is MRU
        timer tells the latest time a page is used
    put the new page into that slot
*/
unsigned char evictMRU(cache_t* cache, int memory_location,int offset){
    int toReplace = 0;
    //look for MRU
    for(int i = 0; i < cache->size; i++){
        if(cache->entries[i].timestamp +1 == cache->timer){
            toReplace = i;
            break;
        }
        //store the new page in the index of MRU cache
        cache_miss(cache,toReplace,memory_location,offset);
        return page_get(cache->entries[toReplace].page,offset);
    }
}

/*LRU - evict the least recently used cache: utilize timer and timestamp
    check which page in cache has the smallest timestamp --? that page is LRU
    put the new page into that slot
*/
unsigned char evictLRU(cache_t* cache, int memory_location,int offset){
    int toReplace = 0;
    int min = cache->timer;
    //look for LRU
    for(int i = 0; i < cache->size; i++){
        if(cache->entries[i].timestamp < min){
            min = cache->entries[i].timestamp;
            toReplace = i;
        }
    }
    //store the new page in the index of MRU cache
        cache_miss(cache,toReplace,memory_location,offset);
    return page_get(cache->entries[toReplace].page,offset);
}

/*FIFO - first added to array is first out: use array-based queue
    shift the array toward the front to push the first page in cache out
*/
unsigned char evictFIFO(cache_t* cache, int memory_location,int offset){
    for(int i = 0; i < cache->size; i++){
        //once everything is shifted to the left, store the new page at the end of the cache array
        if(i == cache->size-1){
            cache_miss(cache,i,memory_location,offset);
            return page_get(cache->entries[i].page,offset);
        }
        cache->entries[i].page = cache->entries[i+1].page;
        cache->entries[i].timestamp = cache->entries[i+1].timestamp;
    }
}
