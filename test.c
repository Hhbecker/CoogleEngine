#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"
#include <assert.h>

int main(void){

 // Workflow:
    // iterate through the list of documents
    // for each document, iterate through each word 
    // 1. First call get on a word which will return the number of occuerences of that word in the map
    // 2. If  -the value is -1 pass 1 into the put method with the key as a parameter 
    //        -the value is > 0 increment it and pass that number into the put method with the key as a parameter

    ////////////////////////////////////////////////////////////////////////////////////

    // declare a pointer to a hashmap struct 
    struct hashmap* mapPTR;
    // set it equal to hm_create(num_buckets);

    mapPTR = hm_create(5);

    assert (mapPTR);

    // Testing hash

    //char word[] = "George";
    char* wordPTR = "George";
    char* wordPTR2 = "Washington";

    //char docID[] = "D1";
    char* docidPTR = "D1";

    // • figure out how to approach freeing memory 
    
    hm_put(mapPTR, wordPTR, docidPTR, 1); 
    hm_put(mapPTR, wordPTR, docidPTR, 3); 
    hm_put(mapPTR, wordPTR2, docidPTR, 2);

    int occurrences = hm_get(mapPTR, wordPTR, docidPTR);

    printf("num occurences = %d\n", occurrences);

    hm_remove(mapPTR, wordPTR, docidPTR);

    occurrences = hm_get(mapPTR, wordPTR, docidPTR);

    printf("num occurences = %d\n", occurrences);

    hm_destroy(mapPTR);

    //occurrences = hm_get(mapPTR, wordPTR, docidPTR);

// 1. Pass NULL and invalid parameters into each function



// 2. Create a hashmap with 6 buckets

// Three put cases:
// 1. list not initialized 
// 2. adding item to rear of existing list
// 3. overwriting num occurences in an existing node

// Five get cases 
// 1. list not initialized 
// 2. list initialized but item not present (return -1)
// 3. list initialized and item at front of list 
// 4. list initialized and item in between two nodes
// 5. list initialized and item at rear of list

// Six remove cases:
// 1. List uninitialized
// 2. Target node is not found (list is present).
// 3. Target node is the only node in the list.
// 4. Target node is the first node but has nodes after it.
// 5. Target node is not first but has no nodes after it.
// 6. Target node is in between two nodes.

// Remake list to test destroy 
    
    return 0;
}
