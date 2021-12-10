#include "hashmap.h"
#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <stdbool.h>
#include "hashmap.h"
// link to Header file "hashmap.h" which contains:
// linked list node struct "llnode"
// hashmap struct
// function headers for the functions in this file 


// returns the populated hash table as output
struct hashmap* training(char* directory, char* charBuckets ){

    // 1. confirm inputs are not NULL
    if(!(directory)|| !(charBuckets)){
        printf("passing NULL pointers into training function: returning NULL\n");
        return NULL;
    }

    // 2. confirm number of buckets is valid
    int numBuckets = (int) strtoll(charBuckets, NULL, 10);
    if(numBuckets<1){
        printf("You can't create a hashmap with %d buckets: returning NULL\n", numBuckets);
        return NULL;
    }

    // 3. confirm glob return value is zero
    glob_t result;
    int retval = glob(directory, 0, NULL, &result);
    if(retval !=0){
        printf("Directory invalid, glob unsuccessful: returning NULL\n");
        return NULL;
    }

    // 4. confirm searchable files are present in the requested directory
    int numFiles = (int) result.gl_pathc;
    if(result.gl_pathc<1){
        printf("No files in this directory: returning NULL\n");
        return NULL;
    }

    printf("num files is: %d\n", numFiles);

    // 5. create hashmap with specified number of buckets
    struct hashmap* hashmapPtr = NULL; //hm_create(numBuckets);

    // 6. iterate through words in documents and call hash_table_insert
    for(int i=0; i<numFiles; i++){
        // create file pointer from file name char string
        FILE* filePtr = fopen(result.gl_pathv[i], "r"); // result.gl_pathv is an array of file names

        // this creates a char array of size 1023 because no word will be more than 1023 characters
        char buf[1023]; 

        // while fscanf does not throw an error
        while(fscanf(filePtr, "%s", buf)==1){
            // the buf variable contains the character string of the next word being scanned in
            printf("File: %s, word:'%s'\n", result.gl_pathv[i], buf);
            hash_table_insert(hashmapPtr, buf, i);
        }

        // close the file to flush the buffer 
        int fclose(FILE *filePtr);
    }

    return hashmapPtr;
}

// hm_create: allocates space for a new hashmap struct using the specified number of buckets
// input: number of buckets in the hashmap
// returns: pointer to a hashmap struct
// struct hashmap* hm_create(int num_buckets){ 
//     // null check parameters
//     if(num_buckets < 1){
//         printf("You can't initialize a map with %d buckets! Returning NULL\n", num_buckets);
//         return NULL;
//     }

//     // declare space in memory for a pointer to a hashmap struct 
//     struct hashmap* myMap = (struct hashmap*) malloc(sizeof(struct hashmap));

//     // declare space in memory for an array (contiguous memory blocks) of linked list node pointers
//     myMap->pointerArray = (struct llnode**) malloc(sizeof(struct llnode*)*num_buckets);

//     // initialize each linked list node pointer to null
//     for(int i=0; i<num_buckets; i++){
//         myMap->pointerArray[i] = NULL; 
//     }

//     // set the num_buckets variable in the struct equal to the parameter and set num elements to zero
//     myMap->num_buckets=num_buckets; 
//     myMap->num_elements=0;

//     printf("\nYour map has been initialized with %d buckets!\n\n", num_buckets);

//     return myMap;

// }


void hash_table_insert(struct hashmap* hashmapPtr, char* word, int docID){
    // hashes word and creates new node for the word or updates existing document frequency for that word and document combo

}

