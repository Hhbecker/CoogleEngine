#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <stdbool.h>
#include "hashmap.h"
#include <assert.h>


int main() {
    // skips user prompts for easy testing
    bool debug = true;

    // STEPS
    // prompt user for num buckets
    // initialize hashmap with that many buckets
    // prompt user for search string 
    // read in search string (example search string: "p5docs/*.txt")
    // pass search string into glob 
    // iterate through this array of file pointers 
    // open each file, add each word to hashmap, and close each file

    printf("How many buckets?: ");

        char* charBuckets;

    if(debug){
        charBuckets = "15";
    }
    else{
        // create inputs for getline function
        char* input = NULL;
        size_t length = 0;
        size_t lnSize = 0;

        lnSize = getline(&input, &length, stdin); 

        charBuckets = strtok(input, "\n");
    }

    printf("Please specify the directory and document type you would like to search:\n");
    printf("Example: 'p5docs/*.txt'\n");

    char* directory;

    if(debug){
        directory = "p5docs/*.txt";
    }
    else{
        // create inputs for getline function
        char* line = NULL;
        size_t len = 0;
        size_t lineSize = 0;

        lineSize = getline(&line, &len, stdin); 

        directory = strtok(line, "\n");
    }

    // create pointer to hashmap struct
    struct hashmap* mapStructPtr;
    mapStructPtr = training(directory, charBuckets);
 

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
