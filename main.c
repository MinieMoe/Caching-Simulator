#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"


int main(int argc, char** argv) {
    // keep a counter of cache latency
    int total_latency = 0;

    //default specification
    int store_size = 16;
    int cache_size = 4;
    int policy = FIFO;

    int i=1;                        //counter to track index of argv; argv[0] = ./cache_sim
    
    if(argc < 1 || argc > 7){
        printf("Before while: Usage: ./cache_sim [-s storesize] [-c cachesize] [-p policy]\n");
        exit(0);
    }
    //retrieving input from command line
    while(i < argc){
        if(argv[i][1] == 's'){
            if(argv[i+1] != 0){
                store_size= atoi(argv[i+1]);      
                i+=2;//jump to the next flag if -s has a value next to it
            }else{
                i++;//jump to the next flag if -s doesn't have a value next to it
            }
            printf("s %d\n", store_size);
        }else if(argv[i][1] == 'c'){
            
            if(argv[i+1] != 0){
                cache_size= atoi(argv[i+1]);
                i+=2;
            }else{
                i++;
            }
            printf("c %d\n", cache_size);
        }else if(argv[i][1] == 'p'){
            printf("p %s\n", argv[i+1]);

            if ((strcmp(argv[i+1],"mru") == 0)){
                policy = MRU;
                i+=2;
            }else if ((strcmp(argv[i+1],"lru") == 0)){
                policy = LRU;
                i+=2;
            }else if ((strcmp(argv[i+1],"fifo") == 0)){
                i+=2;
            }else{
                i++;
            }
            printf("Policy: %d\n", policy);

        }else{
            printf("After while: Usage: ./cache_sim [-s storesize] [-c cachesize] [-p policy]\n");
            exit(0);
        }
    }

    //initialize store and cache once get the info from input
    store_t store;
    cache_t cache;

    store_init(&store,store_size);
    cache_init(&cache,cache_size,&store,policy);

    //read from standard input to know which page to get from memory
    char buffer [99];
    int latency = 0;
    printf("Enter the memory location you want to retrieve:\n");
    //read from user input till fgets encounter EOF
    while(fgets(buffer,99,stdin)!=NULL){
        //buffer[strlen(buffer)-1] = '\0';
        cache_get(&cache,atoi(buffer),&latency);
        total_latency += latency;
        memset(buffer,0,99);
    }
    // print out total latency at the end
    printf("Total latency=%d\n", total_latency);
}
