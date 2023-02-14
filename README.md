# Caching
The assignment is available [here](https://docs.google.com/document/d/1krVDlHdCIv8yh06-lXeByNJrssV6ib1xtKPMiS56pYk/edit?usp=sharing).

An assignment for Computer System class I took in 2021 with See-Mong Tan

# Description
A C program replicating how data are stored and fetched from physical to virtual memory. Implement 3 cache replacement policies (FIFO, LRU, MRU) that are used to evict existing data in cache to make rooms for new one coming from physical memory.

store.c & store.h: these represent physical memory that contain multiple memory pages, each of which is 4 bytes. cache.c & cache.h: these represent virtual memory or cache that hold pages that were fetched from store for faster access in the future store has bigger size than cache

page.c & page.h: these represent memory pages that hold data. A page can be seen as an array of 4 bytes and store has an array of pages. How do we access memory in store? For example, if there are 2 pages in store, the total size will be 4 bytes x 2 = 8 bytes. If we want to get a data at memory location 3, this tells us to go to the first page in store and get the data at index 3 of that page.

In main(), user can put in how many pages store and cache can have. After that, type in the memory location to retrieve data at that location. main() will return the total latency that shows how long it takes to fetch a data depending on where it was fetched (from store or cache).
