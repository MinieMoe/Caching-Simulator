#include <stdlib.h>
#include "store.h"

// Initialize a memory store with the given number of pages
void store_init(store_t* store, int numpages) {
    store->numpages = numpages;
    store->pages = (page_t*)malloc(numpages*sizeof(page_t));
    //initialize that content of each Page to 0
    //memset(store->pages,0,numpages);
    for(int i = 0; i < numpages; i++){
        page_init(&(store->pages[i]),i,NULL);
    }
}

// Return the page corresponding to the given memory location
page_t* store_get(store_t* store, int location) {
    //pages[location] return object of type page_t; so we have to return the address to match the function
    return &(store->pages[location]);
}
