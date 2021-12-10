#include "hashmap.h"
#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <stdbool.h>
#include "hashmap.h"
// link to Header file "hashmap.h" which contains:
// linked list node structs for word and doc linked lists
// hashmap struct
// function headers for the functions in this file 

// training: 
// inputs:
// returns: the populated hash table (if parameters are valid)
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
    struct hashmap* hashmapPtr = hm_create(numBuckets);

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
            //hash_table_insert(hashmapPtr, buf, i);
        }

        // close the file to flush the buffer 
        int fclose(FILE *filePtr);
    }

    return hashmapPtr;
}

// hm_create: allocates space for a new hashmap struct using the specified number of buckets
// input: number of buckets in the hashmap
// returns: pointer to a hashmap struct
struct hashmap* hm_create(int num_buckets){ 
    // null check parameters
    if(num_buckets < 1){
        printf("You can't create a map with %d buckets: returning NULL\n", num_buckets);
        return NULL;
    }

    // declare space in memory for a hashmap struct 
    struct hashmap* myMap = (struct hashmap*) malloc(sizeof(struct hashmap));

    // declare space in memory for an array (contiguous memory blocks) of wordNode pointers
    myMap->pointerArray = (struct wordNode**) malloc(sizeof(struct wordNode*)*num_buckets);

    // initialize each linked list node pointer to null
    for(int i=0; i<num_buckets; i++){
        myMap->pointerArray[i] = NULL; 
    }

    // set the num_buckets variable in the struct equal to the parameter and set num elements to zero
    myMap->num_buckets=num_buckets; 
    myMap->num_elements=0;

    printf("\nHashmap initialized with %d buckets\n\n", num_buckets);

    return myMap;

}

// hash_table_insert
// input:
// returns:
//void hash_table_insert(struct hashmap* hashmapPtr, char* word, int docID){
    // hashes word and creates new node for the word or updates existing document frequency for that word and document combo

    // 1. null check 

    // 2. hash 

    // 3. several different insert cases 

//}

// // hm_put: adds a given key value pair into the hashmap
// // input: pointer to hashmap struct, pointer to word and doc id, number of occurences 
// // returns: void
// void hm_put(struct hashmap* hm, char* word, char* document_id, int num_occurrences){
//     if(num_occurrences<1){
//     printf("You are trying to add a KVP with num_occerences less than 1! Returning now\n");
//         return;
//     }
//     if(hm && word && document_id && hm->map){

//         //call hash function on word and docID 
//         int index = hash(hm, word, document_id);
//         printf("Hash value equals %d\n", index);

//         // if KVP is found overwrite occurence count 
//         // if KVP is not found:
//         // • malloc space for a new node
//         // • set next pointer of previous node to new node
//         // • set next pointer of new node to null
//         // • allocate space for word and doc ID strings (strdup does this automatically)
//         // • increment num_elements in hashmap

//         // 1. list not initialized
//         if(!hm->map[index]){
//             printf("Linked list in bucket %d not initialized, creating first node now\n", index);
//             // allocate space for a new node 
//             hm->map[index] = (struct llnode*) malloc(sizeof(struct llnode));
//             printf("succesful malloc bub\n");

//             // copy word into llnode (strdup automatically allocates space for the duplicate string) 
//             hm->map[index]->word = strdup(word);
//             // copy doc ID into llnode
//             hm->map[index]->document_id = strdup(document_id);
//             // set next pointer of llnode to NULL
//             hm->map[index]->next = NULL;
//             //increment num elements 
//             hm->num_elements++;
            
//             return;
//         }
//         // 2. list is initialized item found
//         else{
//             // create a llnode pointer and assign it to hm->map[index] which is pointing to the first node in the list
//             struct llnode* tempPTR = hm->map[index];
//             struct llnode* trailingPTR = hm->map[index];
           
//             while(tempPTR){
//             //compare word string and docID
//                 if( (strcmp(tempPTR->document_id, document_id) == 0) && (strcmp(tempPTR->word, word) == 0) ){
//                     tempPTR->num_occurrences = num_occurrences;  
//                     printf("KVP found in hashmap, overwriting occurence count now\n");
//                     return;
//                 }
//                 else{
//                     trailingPTR = tempPTR;
//                     tempPTR = tempPTR->next;
//                     printf("This node key did not match the query key, checking next node..\n");
//                 }
//             }
//         // 3. list is initialized item not found
//                 printf("KVP not found in hashmap, creating new list node now\n");
//                 struct llnode* newNodePTR = trailingPTR->next;
//                 newNodePTR = (struct llnode*) malloc(sizeof(struct llnode));
//                 // copy word into llnode  
//                 newNodePTR->word = strdup(word);
//                 // copy doc ID into llnode
//                 newNodePTR->document_id = strdup(document_id);
//                 // set next pointer of llnode to NULL
//                 newNodePTR->next = NULL;
//                 //increment num elements 
//                 hm->num_elements++;
//                 return;
//         }
//     }
//     else{
//         printf("Attempting to pass invalid parameters into hm_put: returning\n");
//         return;
//     }
// }

// hash: sums ascii characters to assign word and doc ID to a bucket
// input: pointer to hashmap struct, pointer to a word, pointer to a doc ID
// returns: 
int hash(struct hashmap* hm, char* word, char* document_id){
    // Null check parameters
    if(hm && word && document_id && hm->pointerArray){
        // printf("You have valid parameters! Counting ASCII\n");
        // add the ascii values of the word and the docID and modulo by the number of buckets
        int ascii = 0;
        // count word ascii
        for(int i=0; i< (int) strlen(word); i++){
            ascii = ascii + ((int) word[i]);
        }
        // count docID ascii
        for(int i=0; i< (int) strlen(document_id); i++){
            ascii = ascii + ((int) document_id[i]);
        }

        // modulo by number of buckets
        return (ascii) % (hm->num_buckets);
    }
    else{
        printf("Attempting to pass invalid parameters into hash: returning -1\n");
        return -1;
    }

}

