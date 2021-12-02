#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

int main(void){

    // call hashmap.h hm_create function which finds that function in the hashmap.c file and executes it
    // declare a pointer to a hashmap struct 
    // set it equal to hm_create(num_buckets);
    struct hashmap* hashPTR;
 
    hashPTR = hm_create(5);
    
        return 0;
}
