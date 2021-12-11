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

    // 8. Remove stop words
    stop_word(hashmapPtr, numFiles);  

    return hashmapPtr;
}

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

            while(Ptr){
                // compare docFrequency to numFiles
                if(Ptr->docFrequency == numFiles){
                    printf("word %s found in all files: calling remove\n", Ptr->word);
                    removeWord(hm, trailingPtr, Ptr);
                    Ptr = trailingPtr->nextWord;
                }
                else{
                    trailingPtr = Ptr;
                    Ptr=Ptr->nextWord;
                }

            }
        }
    }

}


// remove: frees all memory allocated for linked list node and reconnects the list if necessary
// input: pointer to hashmap struct, pointers to the node key
// returns: void
void removeWord(struct hashmap* hm, struct wordNode* trailingPtr, struct wordNode* Ptr){
        // old parameters: struct hashmap* hm, char* word, char* document_id
    if(!(trailingPtr || Ptr)){
        printf("Passing NULL pointers into remove: returning\n");
    }
        
    if (Ptr==trailingPtr) // the target node is first in the list
    {
        int index=hash(hm->num_buckets, Ptr->word);

            if (Ptr->nextWord) // the target node has a node following it
            {
                printf("Target node is first with nodes after it\n");
                hm->pointerArray[index] = Ptr->nextWord;
                freeWord(Ptr);
                free(Ptr);
            }
            else // the target node is the only element in the list
            {
                printf("Target node is the only node in list\n");
                hm->pointerArray[index] = NULL;
                freeWord(Ptr);
                free(Ptr);
            }
    }	
    else // the target node is not first in the list
    {
            if (Ptr->nextWord) // the target node is in between two nodes
            {
                printf("Target node is between nodes\n");
                trailingPtr->nextWord = Ptr->nextWord;
                freeWord(Ptr);
                free(Ptr);
            }
            else // the target node is at the end of the list
            {
                printf("Target node is end of list\n");
                trailingPtr->nextWord = NULL;
                freeWord(Ptr);
                free(Ptr);
            }
    }
    return;
}

void freeWord(struct wordNode* wordPtr){
    printf("\nInside freeWord\n\n");
    // 1. walk down document list and free each document struct
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
            if(trailingPtr->tfidf){
                free(trailingPtr->tfidf);
            }
            free(trailingPtr);
            // move trailing PTR up the list
            trailingPtr = docPtr;
        }

    }

    printf("\nDoc list freed\n");

    // 2. free each necessary word struct data
    // free word string
    free(wordPtr->word);
    wordPtr->nextWord = NULL; 

    return;
}



// double tfidf(struct wordNode* wordPtr, int docID){
//     if(wordNode->docList->tfid){
//         return tfidf
//     }
//     else{
//         double* tfidf = (double*) malloc(sizeof(double));
//     }
// }



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
    int index = hash(hm->num_buckets, word);
    printf("hash index = %d\n", index);

    // returns pointer to a wordNode containing the word just passed into insert
    struct wordNode* wordPtr = findWord(hm, index, word, 1); // 1 for insert mode

    addDoc(wordPtr, docID);

    printf("word->word = %s\n\n", wordPtr->word);

    if(wordPtr){
        // to avoid unused error for now
    }
    


}

// addDoc: creates new docNode if doc not in list or adds to num occurences of existing docNode

void addDoc(struct wordNode* wordPtr, int docID){
    // null check
    if(!(wordPtr)|| (docID<0)){
        printf("Passing NULL or invalid parameters into addDoc\n");
        return;
    }
    // 1. docList not initialized
    if(!wordPtr->docList){
        printf("word '%s' does not have a docList - initializing now\n", wordPtr->word);
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
                printf("Doc found in docList, incrementing occurences\n");
                // increment numOccurences
                tempPTR->termFrequency++;
                return;
            }
            else{
                trailingPTR = tempPTR;
                tempPTR = tempPTR->nextDoc;
                printf("This node's docID did not match the query docID, checking next doc..\n");
            }
        }
    // 3. list is initialized doc not found
        printf("Doc not found in hashmap, creating new doc node now\n");
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

// pass in the pointerArray[index] pointer
// 
// returns: pointer to the word in question (returns NULL if on retrive mode and word does not exist)
struct wordNode* findWord(struct hashmap* hm, int index, char* word, int insertMode){

    // 1. word list not initialized 
    if(!(hm->pointerArray[index])){

        printf("Linked list in this bucket not initialized, creating first node now\n");
    
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
            printf("Word not found in retrieve findWord call\n");
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
                printf("Word found in hashmap, returning pointer\n");
                return tempPTR;
            }
            else{
                trailingPTR = tempPTR;
                tempPTR = tempPTR->nextWord;
                printf("This node's word did not match the query word, checking next node..\n");
            }
        }

    // 3. list is initialized item not found
        if(insertMode){
            printf("Word not found in hashmap, creating new word node now\n");
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
            printf("Word not found in hashmap: returning NULL\n");
            return NULL;
        }
    }
}

// hash: sums ascii characters to assign word and doc ID to a bucket
// input: pointer to hashmap struct, pointer to a word, pointer to a doc ID
// returns: 
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


char** read_query(void){
    // prompt user for search query
    printf("Enter search string or X to exit: ");

    char* queryLine = NULL;
    size_t queryLength = 0;
    size_t queryLineSize = 0;

    queryLineSize = getline(&queryLine, &queryLength, stdin); 

    printf("Whole line: %s\n", queryLine);
    printf("Query length: %d\n", (int) queryLineSize);

    int spaces = 0;
        for(int i=0; queryLine[i]!='\0'; i++){
            if(queryLine[i] == ' '){
                spaces++;
            
            }
            printf("%c\n", queryLine[i]);
        }
    printf("Spaces: %d\n", spaces);

    char* queryToken = strtok(queryLine, " ");

    // maximum word length in query is 20 chars
    char queryArray[spaces+1][20];

    if(queryArray[0]){

    }

    int count = 0;
    while(queryToken != NULL){
         printf("Entering '%s' into query array\n", queryToken);
         //queryArray[count] = queryToken; 
         queryToken = strtok(NULL, " "); 

    }

    return NULL;



}


void rank(struct hashmap* hm, char** query) {

    if(hm){
        // to avoid unused
    }
    if(query){
        // to avoid unused
    }

        // computes the score for each document based on DF-IDF rank of search query
        // must also determine if there is no document with a match (if none of the words in the search query appear in any of the documents)
        // for each document 
        //     score =0;
        //         for each word in each document{ 
        //             findWord
        //             get tfidf
        //             score = score + tfidf
        //         }
        //         save document score into 2D array 
        //         sort array using quicksort
        //         print rankings to file and to console
    
    
}

