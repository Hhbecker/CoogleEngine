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
    if(debug){
        charBuckets = "5";
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

    printf("\n\nTraining phase complete\n\n\n");
 
    // 5. prompt user for search query and save it as a string
    char** queryArray = read_query();

    // 6. call rank to calculate scores for each document and print them to console
    rank(mapStructPtr, queryArray);
    
}

