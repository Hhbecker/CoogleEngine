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
#include "header.h"
#include <assert.h>
#include <unistd.h>

// Potentially not used 
struct qeuryNode {
    char* word;
    struct queryNode* next; 
};


int main(void) {

    // skips user prompts for testing and debugging
    int debug = 0; // 1=true

    // message on start up
    printf("\n -- WELCOME TO COOGLE ENGINE -- \n\n");
  
    printf("This application is MIT licensed. Author: Henry Becker. Date: Jan 2022\n\n");

    // prompt user for directory to be searched and save it as a string
    char* directory;
    printf("Please specify the directory and document type you would like to search:\n");
    printf("Example: 'p5docs/*.txt'\n");

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
    // create pointer to a hashmap struct
    struct hashmap* hashmapPtr;

    // call training method
    hashmapPtr = training(directory, globPtr, numBuckets);


    // sleep is happening before dots are written to stdout 
    // printf("\n\nTRAINING HASHMAP");
    // fflush(stdout);
    // sleep(1);
    // printf(".");
    // fflush(stdout);
    // sleep(1);
    // printf(".");
    // fflush(stdout);
    // sleep(1);
    // printf(".");
    // fflush(stdout);
    // sleep(1);
    // printf("\n\nTRAINING PHASE COMPLETE\n");
    // fflush(stdout);
    // sleep(1);

    int queryResult = 1;

    while(queryResult == 1){
        queryResult = read_query(hashmapPtr, numFiles);
    }

    //printf("DESTROYING DATA STRUCTURES\n");
    hm_destroy(hashmapPtr);
    globfree(globPtr);
    free(line);
    
}


