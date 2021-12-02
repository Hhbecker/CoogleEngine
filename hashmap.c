#include "hashmap.h"
#include <stdio.h>    
#include <stdlib.h>
// link to Header file "hashmap.h" which contains:
// linked list node struct "llnode"
// hashmap struct
// function headers for the functions in this file 


// hm_create: allocates space for a new hashmap struct using the specified number of buckets
// input: number of buckets in the hashmap
// returns: pointer to a hashmap struct
struct hashmap* hm_create(int num_buckets){ 
    
    // declare space in memory for a pointer to a hashmap struct 
    struct hashmap* myMap = (struct hashmap*) malloc(sizeof(struct hashmap));

    // declare space in memory for an array (contiguous memory blocks) of linked list node pointers
    myMap->map = (struct llnode**) malloc(sizeof(struct llnode*)*num_buckets);

    // initialize each linked list node pointer to null
    for(int i=0; i<num_buckets; i++){
        myMap->map[i] = NULL; 
    }
    
    // set the num_buckets variable in the struct equal to the parameter and set num elements to zero
    myMap->num_buckets=num_buckets; 
    myMap->num_elements=0;

    printf("Your map has been initialized with %d buckets!\n", num_buckets);

    return myMap;

}


// int hm_get(struct hashmap* hm, char* word, char* document_id){

//     return 0;
// }

// void hm_put(struct hashmap* hm, char* word, char* document_id, int num_occurrences){

// }

// void hm_destroy(struct hashmap* hm){

// }

// hash: sums ascii characters to assign word and doc ID to a bucket
// input: pointer to hashmap struct, pointer to a word, pointer to a doc ID
// returns: 
int hash(struct hashmap* hm, char* word, char* document_id){

    return 0;
}
