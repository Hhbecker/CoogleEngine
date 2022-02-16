/*
Main and driver methods for the Coogle Search Engine.
Author: Henry Becker
Date: 2/10/22
This application is MIT licensed.
*/

#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>

#include "header.h"

int main(void) {

    // skips user prompts for testing and debugging
    int debug = 0; // 1=true

    // message on start up
    printf("\n -- WELCOME TO COOGLE ENGINE -- \n\n");
  
    printf("This application is MIT licensed. Author: Henry Becker. Date: Jan 2022\n\n");

    // prompt user for directory to be searched and save it as a string
    char* directory;
    printf("Please specify the directory and document type you would like to search:\n");
    printf("Example: 'testFiles/*.txt'\n");

    // getline() receives a pointer to a buffer in which to store the line string, a pointer to the size of the buffer, and a pointer to the input stream.
    // The function does the following:
    // •Allocates memory for the string buffer on the heap
    // •Updates the len variable to track the memory allocation
    // •Reads a line into the heap-allocated string buffer
    // •Returns the length of the string that has been read

    // Why do we have to free(line)? After all, there are no malloc family functions in the above code?
    // The answer is that getline() allocates memory to the buffer (in the example above, line) as required.

    //////////////////// GET DIRECTORY NAME FROM USER SAVE AS STRING //////////////////

    // create inputs for getline function
    char* line = NULL;
    size_t len = 0;
    size_t lineSize = 0;

    lineSize = getline(&line, &len, stdin);  

    directory = strtok(line, "\n");

    // hardcode directory during debugging
    if(debug){
        directory = "p5docs/*.txt";
    }

    //////////////////// GET LIST OF FILES FROM DIRECTORY SAVE AS STRING /////////////////

    // the glob function returns a struct containing a list of each file in the directory specified
    glob_t result;
    int retval = glob(directory, 0, NULL, &result);
    if(retval !=0){
        printf("Directory invalid, glob unsuccessful: exiting main\n");
        return -1;
    }

    // confirm searchable files are present in the requested directory
    int numFiles = (int) result.gl_pathc;
    // check the man page but i think result.gl_pathc will be 0 if the directory is empty
    if(result.gl_pathc<1){
        printf("No files in this directory: exiting main\n");
        return -1;
    }

    // create a pointer to glob struct which you can pass into hashmap functions
    glob_t* globPtr = &result;

    /////////////////// GET NUMBER OF TXT FILES IN DIR AND AVG SIZE TO CALCULATE NUMBER OF BUCKETS ////////////////
    // find number of .txt files and size of each file in bytes from OS
    // calculate best number of buckets 
    int numBuckets = 5;

    //////////////// TRAIN HASHMAP TO CALCULATE PRIORITY OF EACH DOC/WORD? /////////////

    // create pointer to hashmap struct, initialize hashmap with specified number of buckets
    struct hashmap* hashmapPtr = createHashmap(directory, globPtr, numBuckets);

    // call training method
    hashmapPtr = trainHashmap(hashmapPtr, globPtr);

    // sleep is happening before dots are written to stdout 
    printf("\n\nTRAINING HASHMAP");

    int queryResult = 1;

    while(queryResult == 1){
        queryResult = readQuery(hashmapPtr, numFiles);
    }

    //printf("DESTROYING DATA STRUCTURES\n");
    hmDestroy(hashmapPtr);
    globfree(globPtr);
    free(line);
    
}

// destroy: frees all memory allocated by hashmap
// input: pointer to hashmap struct
//returns: void
void hmDestroy(struct hashmap* hm){

    // call freeWord(wordPtr) on each word

    if(hm && hm->pointerArray){ // hm pointer is not NULL
        
        for(int i=0; i<hm->num_buckets; i++){

            if(hm->pointerArray[i]){ // this bucket has a linked list
                struct wordNode* PTR = hm->pointerArray[i];
                struct wordNode* trailingPTR = hm->pointerArray[i];

                while(PTR){
                    //set PTR to next node or NULL
                    PTR = PTR->nextWord;
                    // free word and all its documents
                    freeWord(trailingPTR);
                    free(trailingPTR);
                    // move trailing PTR up the list
                    trailingPTR = PTR;
                }
                //free(hm->pointerArray[i]);
            }
        }

        // free array of pointers
        free(hm->pointerArray);
        hm->pointerArray = NULL;

        // for(int j=0; j<hm->numFiles; j++){
        //     free(hm->fileNames[j]);
        // }
        hm->fileNames = NULL;
        
        free(hm);
    }
    else{
        printf("Attempting to pass invalid parameters into hm_destroy: returning\n");
        return;
    }

}

