#include "hashmap.h"
#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
// link to Header file "hashmap.h" which contains:
// linked list node struct "llnode"
// hashmap struct
// function headers for the functions in this file 


// hm_create: allocates space for a new hashmap struct using the specified number of buckets
// input: number of buckets in the hashmap
// returns: pointer to a hashmap struct
struct hashmap* hm_create(int num_buckets){ 
    // null check parameters
    if(num_buckets < 1){
        printf("You can't initialize a map with %d buckets! Returning NULL\n", num_buckets);
        return NULL;
    }

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

    printf("\nYour map has been initialized with %d buckets!\n\n", num_buckets);

    return myMap;

}

// hm_get: gets the value associated with the query key 
// input: pointer to hashmap struct, pointer to word and doc id
// returns: returns num_occurences if key found, returns -1 if key not found
int hm_get(struct hashmap* hm, char* word, char* document_id){
   // null check parameter pointers
   if(hm && word && document_id){

        int index = hash(hm, word, document_id);
        
        if(!hm->map[index]){
            return -1;
        }
        else{
            // create a llnode pointer and assign it to hm->map[index] which is pointing to the first node in the list
            struct llnode* tempPTR = hm->map[index];
           
            while(tempPTR){
            //compare word string and docID
                if( (strcmp(tempPTR->document_id, document_id) == 0) && (strcmp(tempPTR->word, word) == 0) ){
                    printf("KVP found in hashmap, num occurrences = %d\n", tempPTR->num_occurrences);
                    return tempPTR->num_occurrences; 
                }
                else{
                    tempPTR = tempPTR->next;
                    printf("This node key did not match the query key, checking next node..\n");
                }
            }

            printf("KVP not found in hashmap, returning -1\n");
            return -1;
        }

   }
   else{
       printf("Attempting to pass invalid parameters into hm_get: returning -1\n");
       return -1;
    }
    return 0;
}

// hm_put: adds a given key value pair into the hashmap
// input: pointer to hashmap struct, pointer to word and doc id, number of occurences 
// returns: void
void hm_put(struct hashmap* hm, char* word, char* document_id, int num_occurrences){
    if(num_occurrences<1){
    printf("You are trying to add a KVP with num_occerences less than 1! Returning now\n");
        return;
    }
    if(hm && word && document_id){

        //call hash function on word and docID 
        int index = hash(hm, word, document_id);
        printf("Hash value equals %d\n", index);

        // if KVP is found overwrite occurence count 
        // if KVP is not found:
        // • malloc space for a new node
        // • set next pointer of previous node to new node
        // • set next pointer of new node to null
        // • allocate space for word and doc ID strings (strdup does this automatically)
        // • increment num_elements in hashmap

        // 1. list not initialized
        if(!hm->map[index]){
            printf("Linked list in bucket %d not initialized, creating first node now\n", index);
            // allocate space for a new node 
            hm->map[index] = (struct llnode*) malloc(sizeof(struct llnode));
            printf("succesful malloc bub\n");

            // copy word into llnode (strdup automatically allocates space for the duplicate string) 
            hm->map[index]->word = strdup(word);
            // copy doc ID into llnode
            hm->map[index]->document_id = strdup(document_id);
            // set next pointer of llnode to NULL
            hm->map[index]->next = NULL;
            //increment num elements 
            hm->num_elements++;
            
            return;
        }
        // 2. list is initialized item found
        else{
            // create a llnode pointer and assign it to hm->map[index] which is pointing to the first node in the list
            struct llnode* tempPTR = hm->map[index];
            struct llnode* trailingPTR = hm->map[index];
           
            while(tempPTR){
            //compare word string and docID
                if( (strcmp(tempPTR->document_id, document_id) == 0) && (strcmp(tempPTR->word, word) == 0) ){
                    tempPTR->num_occurrences = num_occurrences;  
                    printf("KVP found in hashmap, overwriting occurence count now\n");
                    return;
                }
                else{
                    trailingPTR = tempPTR;
                    tempPTR = tempPTR->next;
                    printf("This node key did not match the query key, checking next node..\n");
                }
            }
        // 3. list is initialized item not found
                printf("KVP not found in hashmap, creating new list node now\n");
                struct llnode* newNodePTR = trailingPTR->next;
                newNodePTR = (struct llnode*) malloc(sizeof(struct llnode));
                // copy word into llnode  
                newNodePTR->word = strdup(word);
                // copy doc ID into llnode
                newNodePTR->document_id = strdup(document_id);
                // set next pointer of llnode to NULL
                newNodePTR->next = NULL;
                //increment num elements 
                hm->num_elements++;
                return;
        }
    }
    else{
        printf("Attempting to pass invalid parameters into hm_put: returning\n");
        return;
    }
}

// hash: sums ascii characters to assign word and doc ID to a bucket
// input: pointer to hashmap struct, pointer to a word, pointer to a doc ID
// returns: 
int hash(struct hashmap* hm, char* word, char* document_id){
    // Null check parameters
    if(hm && word && document_id){
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

// remove: frees all memory allocated for linked list node and reconnects the list if necessary
// input: pointer to hashmap struct, pointers to the node key
// returns: void
void hm_remove(struct hashmap* hm, char* word, char* document_id){

    if(hm && word && document_id){

        int index = hash(hm, word, document_id);
        printf("Hash value equals %d\n", index);

        // if bucket doesn't have a linked list return 
        if(!hm->map[index]){
            printf("Item in hm_remove call does not exist: returning\n");
            return;
        }
        else{
            struct llnode* PTR = hm->map[index];
            struct llnode* trailingPTR = hm->map[index];
           
            while(PTR){
            //compare word string and docID
                if( (strcmp(PTR->document_id, document_id) == 0) && (strcmp(PTR->word, word) == 0) ){

                    //////////////////////////////////////

                    if (PTR==trailingPTR) // the target node is first in the list
                    {
                            if (PTR->next) // the target node has a node following it
                            {
                                hm->map[index	] = PTR->next;
                                free(PTR->word);
                                free(PTR->document_id);
                                free(PTR);
                            }
                            else // the target node is the only element in the list
                            {
                                hm->map[index	] = NULL;
                                free(PTR->word);
                                free(PTR->document_id);
                                free(PTR);
                            }
                    }	
                    else // the target node is not first in the list
                    {
                            if (PTR->next) // the target node is in between two nodes
                            {
                                trailingPTR->next = PTR->next;
                                free(PTR->word);
                                free(PTR->document_id);
                                free(PTR);
                            }
                            else // the target node is at the end of the list
                            {
                                trailingPTR->next = NULL;
                                free(PTR->word);
                                free(PTR->document_id);
                                free(PTR);
                            }
                    }

                    ///////////////////////////////////////
                    hm->num_elements--;
                    return;
                }
                else{
                    trailingPTR = PTR;
                    PTR = PTR->next;
                }
            }
            printf("Item in hm_remove call does not exist: returning\n");
            return;
        }



    }
    else{
        printf("Attempting to pass invalid parameters into hm_remove: returning\n");
        return;
    }


}

//destroy: frees all memory allocated by hashmap
// input: pointer to hashmap struct
//returns: void
void hm_destroy(struct hashmap* hm){

    if(hm){ // hm pointer is not nULL
        
        for(int i=0; i<hm->num_buckets; i++){

            if(hm->map[i]){ // this bucket has a linked list
                struct llnode* PTR = hm->map[i];
                struct llnode* trailingPTR = hm->map[i];

                while(PTR){
                    //set PTR to next node or NULL
                    PTR = PTR->next;
                    // free node
                    free(trailingPTR->word);
                    free(trailingPTR->document_id);
                    free(trailingPTR);
                    // move trailing PTR up the list
                    trailingPTR = PTR;
                }

            }
        }

        // free array of pointers
        free(hm->map);
        free(hm);
    }
    else{
        printf("Attempting to pass invalid parameters into hm_destroy: returning\n");
        return;
    }

}
