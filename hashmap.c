#include "hashmap.h"    
// link to Header file "hashmap.h" which contains:
// linked list node struct "llnode"
// hashmap struct
// function headers for the functions in this file 


// allocate a new HashMap with the specified number of buckets
// input: number of buckets in the hashmap
// return: pointer to a hashmap struct
struct hashmap* hm_create(int num_buckets){ 

    // use malloc to allocate space on the heap for the size of a hashmap struct 
    struct hashmap myMap = malloc(sizeof(hashmap));

}


int hm_get(struct hashmap* hm, char* word, char* document_id){

}

void hm_put(struct hashmap* hm, char* word, char* document_id, int num_occurrences){

}

void hm_destroy(struct hashmap* hm){

}

int hash(struct hashmap* hm, char* word, char* document_id){

}
