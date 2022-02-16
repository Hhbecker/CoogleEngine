#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <stdbool.h>
#include <glob.h>
#include <math.h>

// link to Header file "header.h" which contains:
// •linked list node structs for word and doc linked lists
// •hashmap struct
// •function headers for the functions in this file 
#include "header.h"

// hm->num_elements NOT IMPLEMENTED CURRENTLY

// struct docNode tfid storage NOT IMPLEMENTED CURRENTLY

///////////////////////////////////////////////////////////////

// hm_create: allocates space for a new hashmap struct using the specified number of buckets
// inputs: a char pointer to the directory to be searched, a glob ptr, and the number of buckets
// returns: pointer to a hashmap struct with a pointer to the list of filenames 
struct hashmap* createHashmap(char* directory, glob_t* globPtr, int numBuckets){ 

    // NULL check globPtr input
    if(!(globPtr || directory)){
        printf("passing NULL glob pointer into createHashmap: returning NULL\n");
        return NULL;
    }

    // NULL check numBuckets input
    if(numBuckets<1){
        printf("You can't create a hashmap with %d buckets: returning NULL\n", numBuckets);
        return NULL;
    }

    // alllocate space in memory for a hashmap struct 
    struct hashmap* hashmapPtr = (struct hashmap*) malloc(sizeof(struct hashmap));

    // allocate space in memory for an array (contiguous memory blocks) of wordNode pointers
    hashmapPtr->pointerArray = (struct wordNode**) malloc(sizeof(struct wordNode*)*numBuckets);

    // initialize each linked list node pointer to null
    for(int i=0; i<numBuckets; i++){
        hashmapPtr->pointerArray[i] = NULL; 
    }

    // set the num_buckets variable in the struct equal to the parameter
    hashmapPtr->num_buckets=numBuckets; 

    // add list of filenames in search dir to hashmap struct (what data structure is this list of filenames? linked list?)
    hashmapPtr->fileNames = globPtr->gl_pathv;

    // add number of files in search dir to hashmap struct
    int numFiles = (int) globPtr->gl_pathc;
    hashmapPtr->numFiles = numFiles;

    return hashmapPtr;

}

// trainHashmap: creates a linked list node for each unique word and add a document linked list containing the frequency per document for that word
// inputs: pointer to the hashmap, 
// returns: the populated hash table (if parameters are valid)
struct hashmap* trainHashmap(struct hashmap* hashmapPtr, glob_t* globPtr){

    // NULL check inputs
    if(!(hashmapPtr || globPtr)){
        printf("passing NULL pointers into training function: returning NULL\n");
        return NULL;
    }

    // iterate through each document and each word in each document 
    for(int i=0; i<hashmapPtr->numFiles; i++){
        // create file pointer from file name char string
        FILE* filePtr = fopen(globPtr->gl_pathv[i], "r"); // result.gl_pathv is an array of file names

        // create a buffer to hold the fscanf() input from stdin (char array of size 1023 because no word will be more than 1023 characters)
        char buf[1023]; 

        // while fscanf does not throw an error or reach a newline
        // scan words at a time
        while(fscanf(filePtr, "%s", buf)==1){
            // the buf variable contains the character string of the next word being scanned in
            // add the word to the hashmap 
            hash_table_insert(hashmapPtr, buf, i);
        }

        // close the file to flush the buffer 
        fclose(filePtr);
    }

    // At this point all unique words from all documents have been added to the hashmap
    // Remove stop words
    stop_word(hashmapPtr, hashmapPtr->numFiles);  

    return hashmapPtr;
}

// hash_table_insert: hashes a word then creates new node for the word or updates existing document frequency for that word and document combo
// input: hashmap pointer, word to be added, document in which the word was found
// returns: void
void hash_table_insert(struct hashmap* hm, char* word, int docID){

    // NULL check inputs
    if(!(hm) || !(word)){
        printf("passing NULL pointers into insert function: returning\n");
        return;
    }
    if(docID<0){
        printf("docID can't be less than 0: returning\n");
        return;
    }

    // returns pointer to a wordNode containing the word just passed into insert
    // if in insert mode a new word node will be created if one does not exist
    struct wordNode* wordPtr = findWord(hm, word, 1); // 1 for insert mode

    // creates new docNode if one is not already present or updates existing node frequency
    addDoc(wordPtr, docID);

    return;

}

// addDoc: creates new docNode if doc not in list or adds to num occurences of existing docNode
// inputs: pointer to word node in hashmap, ID of document in question
// returns: void
void addDoc(struct wordNode* wordPtr, int docID){
    // NULL check inputs
    if(!(wordPtr)|| (docID<0)){
        printf("Passing NULL or invalid parameters into addDoc\n");
        return;
    }

    // There are three cases: 
    // 1. docList is not initialized for that word (initialize docNode list)
    // 2. docList is initialized and the docID is found (increment num occurences)
    // 3. docList is initialized and the docID is not found (create new docNode)

    // 1. docList not initialized
    if(!wordPtr->docList){
        //printf("word '%s' does not have a docList - initializing now\n", wordPtr->word);
        // allocate space for docNode
        wordPtr->docList = (struct docNode*) malloc (sizeof(struct docNode));
        // set docID
        wordPtr->docList->docID = docID;
        // set num occurences to 1
        wordPtr->docList->termFrequency = 1;
        // set tf-idf pointer to NULL
        wordPtr->docList->tfidf = NULL;
        // set nextDoc to NULL
        wordPtr->docList->nextDoc = NULL;
        // increment word docFrequency 
        wordPtr->docFrequency++;
        if(wordPtr->docFrequency != 1){
            printf("word docFrequency not 1 after initializing docList so something's wrong\n");
        }
    }
    // 2. docList initialized doc found
    else{
        // create a doc node pointer and assign it to the docList head node
        struct docNode* tempPTR = wordPtr->docList;
        struct docNode* trailingPTR = tempPTR;

        if(trailingPTR){
            // to avoid error: variable ‘trailingPTR’ set but not used
        }
        
        while(tempPTR){
        //compare word string 
            if(tempPTR->docID == docID){ 
                // increment numOccurences
                tempPTR->termFrequency++;
                return;
            }
            else{
                trailingPTR = tempPTR;
                tempPTR = tempPTR->nextDoc;
            }
        }
    // 3. list is initialized doc not found
        trailingPTR->nextDoc = (struct docNode*) malloc(sizeof(struct docNode));
        // create direct pointer to new doc
        struct docNode* newNodePTR = trailingPTR->nextDoc;
        // set docID  
        newNodePTR->docID = docID;
        // set document frequency to 1
        newNodePTR->termFrequency = 1;
        // set tf-idf pointer to NULL
        wordPtr->docList->tfidf = NULL;
        // set next pointer of doc node to NULL
        newNodePTR->nextDoc = NULL;
        // increase word docFrequency
        wordPtr->docFrequency++;
        return;
    }

}


// stop_Word: searches through every word node and checks if its docFrequency is equal to the number of files (making it a stop word)
// if so it removes that word node and its document linked list from the hashmap
// inputs: pointer to word node in hashmap, ID of document in question
// returns: void
void stop_word(struct hashmap* hm, int numFiles){

    // Null check
    if(!hm){
        printf("passing NULL pointer into calculateIDF: returning\n");
        return;
    }

    // iterate through each bucket
    for(int i=0; i<hm->num_buckets; i++){

        // if bucket has a linked list
        if(hm->pointerArray[i]){ // this bucket has a linked list
            struct wordNode* Ptr = hm->pointerArray[i];
            struct wordNode* trailingPtr = hm->pointerArray[i];

            if(trailingPtr){
                // to avoid unused error
            }

            // if trailing ptr = ptr I can't 

            while(Ptr){
                // compare docFrequency to numFiles
                if(Ptr->docFrequency == numFiles){
                    if(Ptr != trailingPtr){
                        //printf("word %s found in all files: calling remove\n", Ptr->word);
                        removeWord(hm, trailingPtr, Ptr);
                        Ptr = trailingPtr->nextWord;
                    }
                    else{
                        // stop word is first in list so restart the pointers
                        removeWord(hm, trailingPtr, Ptr);
                        Ptr = hm->pointerArray[i];
                        trailingPtr = Ptr;
                    }
                }
                else{
                    trailingPtr = Ptr;
                    Ptr=Ptr->nextWord;
                }
            }
            free(Ptr);
        }
    }

}


// removeWord: frees all memory allocated for a wordNode and its associated docList nodes
// input: pointer to hashmap struct, pointers to the node to be removed and another pointer to the word node before it
// returns: void
void removeWord(struct hashmap* hm, struct wordNode* trailingPtr, struct wordNode* Ptr){

    // null check inputs
    if(!(trailingPtr || Ptr)){
        printf("Passing NULL pointers into remove: returning\n");
    }
        
    // if the target node is first in the list
    if (Ptr==trailingPtr) 
    {
        // get index of bucket 
        int index=hash(hm->num_buckets, Ptr->word);

            if (Ptr->nextWord) // the target node has a node following it
            {
                hm->pointerArray[index] = Ptr->nextWord;
                freeWord(Ptr);
                free(Ptr);
                Ptr = NULL;
            }
            else // the target node is the only element in the list
            {
                hm->pointerArray[index] = NULL;
                freeWord(Ptr);
                free(Ptr);
                Ptr = NULL;
            }
    }	
    else // the target node is not first in the list
    {
            if (Ptr->nextWord) // the target node is in between two nodes
            {
                trailingPtr->nextWord = Ptr->nextWord;
                freeWord(Ptr);
                free(Ptr);
                Ptr = NULL;
            }
            else // the target node is at the end of the list
            {
                trailingPtr->nextWord = NULL;
                freeWord(Ptr);
                free(Ptr);
                Ptr = NULL;
            }
    }
    return;
}

// freeWord: frees the docNode structs associated with the wordNode and then frees the wordNode
// inputs: pointer to word node being freed
// returns: void
void freeWord(struct wordNode* wordPtr){
    // walk down document list 
    // free docList ptr
    // free each nextDoc ptr 
    if(!wordPtr->docList){
        printf("freeing word node without doc list: something's wrong\n");
        return;

    }
    else{
        struct docNode* docPtr = wordPtr->docList;
        struct docNode* trailingPtr = docPtr;

        while(docPtr){
            //set PTR to next node or NULL
            docPtr = docPtr->nextDoc;
            // free node
            free(trailingPtr);
            // move trailing PTR up the list
            trailingPtr = docPtr;
        }

    }

    // 2. free wordNode struct data

    free(wordPtr->word);

    wordPtr->nextWord = NULL; 
    wordPtr->docList = NULL;

    return;
}

// findWord: hash the word then iterate through the associated linked list to see if the word is present in a wordNode in the hashmap
// if the function is called with the insertMode flag it will insert a word that is not already present
// inputs: pointer to hashmap, pointer to char array containing the word, flag for insert mode or search mode
// returns: pointer to the word in question (returns NULL if on retrive mode and word does not exist)
struct wordNode* findWord(struct hashmap* hm, char* word, int insertMode){

    // hash 
    int index = hash(hm->num_buckets, word);

    // 1. word list not initialized 
    if(!(hm->pointerArray[index])){
    
        if(insertMode){

            // 1. wordNode initialization
            // allocate space for a new word node 
            hm->pointerArray[index] = (struct wordNode*) malloc(sizeof(struct wordNode));
            // copy word into word node (strdup automatically allocates space for the duplicate string) 
            hm->pointerArray[index]->word = strdup(word);
            // set docFrequency to 1
            hm->pointerArray[index]->docFrequency = 0;
            // set next pointer of llnode to NULL
            hm->pointerArray[index]->nextWord = NULL;
            // set docList to NULL
            hm->pointerArray[index]->docList = NULL;
            
            return hm->pointerArray[index];
        }
        else{
            //printf("Word not found in retrieve findWord call\n");
            return NULL;
        }
    }
    // 2. list is initialized search for item - item found
    else{
        // create a llnode pointer and assign it to hm->map[index] which is pointing to the first node in the list
        struct wordNode* tempPTR = hm->pointerArray[index];
        struct wordNode* trailingPTR = tempPTR;

        if(trailingPTR){
            // to avoid error: variable ‘trailingPTR’ set but not used
        }
        
        while(tempPTR){
        //compare word string 
            if( strcmp(tempPTR->word, word) == 0){
                //tempPTR->num_occurrences = num_occurrences;  
                return tempPTR;
            }
            else{
                trailingPTR = tempPTR;
                tempPTR = tempPTR->nextWord;
            }
        }

    // 3. list is initialized item not found
        if(insertMode){
            trailingPTR->nextWord = (struct wordNode*) malloc(sizeof(struct wordNode));
            // create direct pointer to new word
            struct wordNode* newNodePTR = trailingPTR->nextWord;
            // copy word into word node  
            newNodePTR->word = strdup(word);
            // set document frequency to 1
            newNodePTR->docFrequency = 0;
            // set next pointer of word node to NULL
            newNodePTR->nextWord = NULL;
            // set docList pointer to null
            newNodePTR->docList = NULL;
            return newNodePTR;
        }
        else{
            //printf("Word '%s' not found in hashmap: returning NULL\n", word);
            return NULL;
        }
    }
}

// hash: sums ascii characters to assign word and doc ID to a bucket
// input: pointer to hashmap struct, pointer to a word, pointer to a doc ID
// returns: index of bucket where word should be placed in hashmap
int hash(int numBuckets, char* word){
    // Null check parameters
    if(word){
        // printf("You have valid parameters! Counting ASCII\n");
        // add the ascii values of the word and the docID and modulo by the number of buckets
        int ascii = 0;
        // count word ascii
        for(int i=0; i< (int) strlen(word); i++){
            ascii = ascii + ((int) word[i]);
        }
        // modulo by number of buckets
        return (ascii) % (numBuckets);
    }
    else{
        printf("Attempting to pass invalid parameters into hash: returning -1\n");
        return -1;
    }

}

