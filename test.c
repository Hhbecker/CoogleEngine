#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"
#include <assert.h>

int main(void){

    // iterate through the list of documents
    // for each document iterate through each word 
    // pass each word with the docID into the get function
    

    // Workflow:
    // 1. First call get on a word which will return the number of occuerences of that word in the map
    // 2. If  -the value is -1 pass 1 into the put method with the key as a parameter 
    //        -the value is > 0 increment it and pass that number into the put method with the key as a parameter

    // create the 3 text documents 
    // figure out how to scan through each word in doc
    // call get and put on each word

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

    occurrences = hm_get(mapPTR, wordPTR, docidPTR);



    
        return 0;
}
