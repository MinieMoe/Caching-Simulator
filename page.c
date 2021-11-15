#include <stdlib.h>
#include <string.h>
#include "page.h"


// allocate and return a page
void page_init(page_t* page, int pageno, unsigned char* bytes) {
    page->pageno = pageno;
    if (bytes == NULL) {
        memset(page->bytes, 0, PAGESIZE);
    } else {
        memcpy(page->bytes, bytes, PAGESIZE);
    }
}

// Return the page no
int page_pageno(page_t* page) {
    return page->pageno;
}

// Return the bytes for the page
unsigned char* page_bytes(page_t* page) {
    return page->bytes;
}


// Return the byte at the offset in the page
unsigned char page_get(page_t* page, int offset) {
    return page->bytes[offset];
}

// Set the byte at the offset in the page
void page_set(page_t* page, int offset, unsigned char c) {
    page->bytes[offset] = c;
}


