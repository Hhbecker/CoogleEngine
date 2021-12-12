#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <stdbool.h>
#include "hashmap.h"
#include <assert.h>


struct qeuryNode {
    char* word;
    struct queryNode* next; 
};

int main(void) {
    // skips user prompts for easy testing
    int debug = 1; // 1=true

    // 1. prompt user for number of buckets and save it as a string
    char* charBuckets;
    printf("How many buckets?: ");

    // create inputs for getline function
    char* input = NULL;
    size_t length = 0;
    size_t lnSize = 0;

    lnSize = getline(&input, &length, stdin); 
    if(lnSize){
        // to avoid error: variable ‘lnSize’ set but not used
    }

    charBuckets = strtok(input, "\n");

    if(debug){
        charBuckets = "5";
    }

    // 2. prompt user for directory to be searched and save it as a string
    char* directory;
    printf("Please specify the directory and document type you would like to search:\n");
    printf("Example: 'p5docs/*.txt'\n");

    
    // create inputs for getline function
    char* line = NULL;
    size_t len = 0;
    size_t lineSize = 0;

    lineSize = getline(&line, &len, stdin); 
    if(lineSize){
        // to avoid error: variable ‘lineSize’ set but not used
    }

    directory = strtok(line, "\n");
    

    if(debug){
        directory = "p5docs/*.txt";
    }



    glob_t result;
    int retval = glob(directory, 0, NULL, &result);
    if(retval !=0){
        printf("Directory invalid, glob unsuccessful: exiting main\n");
        return -1;
    }

        // 4. confirm searchable files are present in the requested directory
    int numFiles = (int) result.gl_pathc;
    if(result.gl_pathc<1){
        printf("No files in this directory: exiting main\n");
        return -1;
    }

    printf("num files is: %d\n", numFiles);

    glob_t* globPtr = &result;

    // 3. create pointer to hashmap struct
    struct hashmap* mapStructPtr;

    // 4. call training method
    mapStructPtr = training(directory, globPtr, charBuckets);

    printf("\n\n///////////////////    Training phase complete    \\\\\\\\\\\\\\\\\\\\\n\n");

    int queryResult = 1;

    while(queryResult == 1){
        queryResult = read_query(mapStructPtr, numFiles);
    }
 
    printf("User entered X: Destroying engine\n");
    hm_destroy(mapStructPtr);
    free(input);
    free(line);
    globfree(globPtr);
    
}


