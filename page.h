#ifndef PAGE_H
#define PAGE_H

// The size of a page is fixed at 4 bytes
#define PAGESIZE 4

// Define a memory page
typedef struct {
    int pageno;
    unsigned char bytes[PAGESIZE];
} page_t;

// Allocate and return a page with all bytes set to 0
void page_init(page_t* page, int pageno, unsigned char* bytes);

// Return the page no
int page_pageno(page_t* page);

// Return the bytes for the page
unsigned char* page_bytes(page_t* page);

// Return the byte at the offset in the page
unsigned char page_get(page_t* page, int offset);

// Set the byte at the offset in the page
void page_set(page_t* page, int offset, unsigned char c);

#endif // PAGE_H
