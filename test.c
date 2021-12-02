#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

int main(void){

    // this test file must at the end provide 3 documents which the 
    // Question: each of the hashmap functions operates on a specific word and docID combo
    // therefore, i would assume the code in this test file must i
    // iterate through the list of documents
    // for each document iterate through each word 
    // pass each word with the docID into the put function

    // however I heard the test file can have whatever we want? 

    // Testing hm_create

    // declare a pointer to a hashmap struct 
    struct hashmap* mapPTR;
    // set it equal to hm_create(num_buckets);
    mapPTR = hm_create(5);

    // Testing hash

    char word[] = "Washington";
    char* wordPTR = word;

    char docID[] = "D1";
    char* docidPTR = docID;

    docidPTR = NULL;

    int hashResult = hash(mapPTR, wordPTR, docidPTR);

    printf("hash result is = %d\n", hashResult);

    
        return 0;
}
