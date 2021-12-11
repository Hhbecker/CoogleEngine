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

// hm->num_elements NOT IMPLEMENTED CURRENTLY

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
    // change back to i<numFiles
    for(int i=0; i<1; i++){
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

// hash_table_insert: hashes word and creates new node for the word or updates existing document frequency for that word and document combo

// input:
// returns:
void hash_table_insert(struct hashmap* hm, char* word, int docID){

    // 1. null check 
    if(!(hm) || !(word)){
        printf("passing NULL pointers into insert function: returning\n");
        return;
    }
    if(docID<0){
        printf("docID can't be less than 0: returning\n");
        return;
    }

    // 2. hash 
    int index = hash(hm, word, docID);
    printf("hash index = %d\n", index);

    struct wordNode* headPtr = hm->pointerArray[index];


    printf("The value of headPtr before calling findWord is: %p\n", (void *) headPtr);
    printf("The direction of headPtr before calling findWord is: %p\n", (void *) &headPtr);

    // returns pointer to a wordNode containing the word just passed into insert
    struct wordNode* wordPtr = findWord(headPtr, word, 1); // 1 for insert mode

    if(wordPtr){
        // to avoid unused error for now
    }


}

// pass in the pointerArray[index] pointer
// 
// returns: pointer to the word in question (returns NULL if on retrive mode and word does not exist)
struct wordNode* findWord(struct wordNode* head, char* word, int insertMode){

    printf("The value of head is: %p\n", (void *) head);
    printf("The direction of head is: %p\n", (void *) &head);

    // 1. word list not initialized 
    if(!head){

        printf("Linked list in this bucket not initialized, creating first node now\n");
    
        if(insertMode){

            // 1. wordNode initialization
            // allocate space for a new word node 
            head = (struct wordNode*) malloc(sizeof(struct wordNode));
            // create pointer to this word node for return value;
            struct wordNode* wordPointer = head;
            // copy word into llnode (strdup automatically allocates space for the duplicate string) 
            wordPointer->word = strdup(word);
            // set df to 1
            wordPointer->df = 1;
            // set next pointer of llnode to NULL
            wordPointer->nextWord = NULL;
            // allocate space for docNode
            wordPointer->docList = (struct docNode*) malloc (sizeof(struct docNode));
            
            return wordPointer;
        }
    }
    // 2. list is initialized search for item - item found
    else{
        // create a llnode pointer and assign it to hm->map[index] which is pointing to the first node in the list
        struct wordNode* tempPTR = head;
        struct wordNode* trailingPTR = tempPTR;

        if(trailingPTR){
            // to avoid error: variable ‘trailingPTR’ set but not used
        }
        
        while(tempPTR){
        //compare word string 
            if( strcmp(tempPTR->word, word) == 0){
                //tempPTR->num_occurrences = num_occurrences;  
                printf("KVP found in hashmap, returning pointer\n");
                return tempPTR;
            }
            else{
                trailingPTR = tempPTR;
                tempPTR = tempPTR->nextWord;
                printf("This node key did not match the query key, checking next node..\n");
            }
        }
    }






    // 3. list is initialized item not found
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

    // debuggin only
    return NULL;


}

struct docNode* findDoc(struct wordNode* theWord, int docID, int insertMode){
       
       // 1. list not initialized 
    if(!theWord->docList){

        if(insertMode){
        // set docID
        theWord->docList->docID = docID;
        // set num occurences 
        theWord->docList->numOccurences = 1;
        // set pointer to next document to NULL
        theWord->docList->nextDoc = NULL;
        }
        else{
            printf("supposedly you're in retrieve mode but there's a word node with no document list so something went wrong\n");
        }
    }

    // debuggin only
    return NULL;

}

// hash: sums ascii characters to assign word and doc ID to a bucket
// input: pointer to hashmap struct, pointer to a word, pointer to a doc ID
// returns: 
int hash(struct hashmap* hm, char* word, int document_id){
    // Null check parameters
    if(hm && word && hm->pointerArray){
        // printf("You have valid parameters! Counting ASCII\n");
        // add the ascii values of the word and the docID and modulo by the number of buckets
        int ascii = 0;
        // count word ascii
        for(int i=0; i< (int) strlen(word); i++){
            ascii = ascii + ((int) word[i]);
        }
        // count docID ascii
            ascii = ascii + document_id;

        // modulo by number of buckets
        return (ascii) % (hm->num_buckets);
    }
    else{
        printf("Attempting to pass invalid parameters into hash: returning -1\n");
        return -1;
    }

}


