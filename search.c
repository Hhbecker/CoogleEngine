#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <stdbool.h>
#include "hashmap.h"
#include <assert.h>


int main(void) {
    // skips user prompts for easy testing
    int debug = 1; // 1=true

    // 1. prompt user for number of buckets and save it as a string
    char* charBuckets;
    printf("How many buckets?: ");
    if(debug){
        charBuckets = "3";
    }
    else{
        // create inputs for getline function
        char* input = NULL;
        size_t length = 0;
        size_t lnSize = 0;

        lnSize = getline(&input, &length, stdin); 
        if(lnSize){
            // to avoid error: variable ‘lnSize’ set but not used
        }

        charBuckets = strtok(input, "\n");
    }

    // 2. prompt user for directory to be searched and save it as a string
    char* directory;
    printf("Please specify the directory and document type you would like to search:\n");
    printf("Example: 'p5docs/*.txt'\n");
    if(debug){
        directory = "p5docs/*.txt";
    }
    else{
        // create inputs for getline function
        char* line = NULL;
        size_t len = 0;
        size_t lineSize = 0;

        lineSize = getline(&line, &len, stdin); 
        if(lineSize){
            // to avoid error: variable ‘lineSize’ set but not used
        }

        directory = strtok(line, "\n");
    }

    // 3. create pointer to hashmap struct
    struct hashmap* mapStructPtr;

    // 4. call training method
    mapStructPtr = training(directory, charBuckets);

    if(mapStructPtr){
        // to avoid error: variable ‘mapStructPtr’ set but not used
    }
 
    // 5. prompt user for search query and save it as a string

    // For reading in a line of words (word search query)

    // char* line = NULL;
    // size_t len = 0;
    // size_t lineSize = 0;

    // // uncomment line below to read in a line of words from standard in
    // //lineSize = getline(&line, &len, stdin); 

    // char* token = strtok(line, " ");

    // while(token != NULL){
    //     printf("Word by word: %s\n", token);
    //     token = strtok(NULL, " "); 
    // }
   
}
