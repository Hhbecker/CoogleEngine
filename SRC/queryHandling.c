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

// readQuery: prompt user for search query and save it as a string, call rank function to rank documents in directory
// inputs: pointer to hashmap, number of files in the directory 
// returns: int 1 to continue while loop in main, 0 to end loop
int readQuery(struct hashmap* mapStructPtr, int numFiles){

 // prompt user for search query
    printf("\nEnter search string or x to exit:\n");

    // establish variables for getline() function
    char* queryLn = NULL;
    char* queryToken = NULL;
    size_t queryLength = 0;
    size_t queryLineSize = 0;

    // passes char string of queryLength from stdin into queryLn char array
    queryLineSize = getline(&queryLn, &queryLength, stdin); 

    // copy query line into another variable 
    char* queryLine = NULL;
    queryLine = strdup(queryLn);

    if(queryLineSize == 0){
        // to avoid error
    }

    // if query is empty try again
    if(queryLine[0]=='\n'){
        printf("query is empty, try again.\n\n");
        return 1;
    }

    // count number of spaces to determine wether query is a single word
    int spaces = 0;
    for(int i=0; queryLine[i]!='\0'; i++){
        if(queryLine[i] == ' '){
            spaces++;
            
        }
    }

    // tokenize query line previously read from stdin
    queryToken = strtok(queryLine, " \n");
    
    // check if query is really an x to exit
    if(spaces==0){
        if((int) strlen(queryToken)==1){
            if((int) queryToken[0] == 120){
                // user inputed X
                return 0;
            }
        }
    }

    // declare space for 2D array 
    // maximum word length in query is 20 chars
    char** queryArray = (char**) malloc(sizeof(char*)*(spaces+1));

    //char* copy;
    int count = 0;

    // save each word of query into a 2D array 
    while(queryToken != NULL){
        queryArray[count] = strdup(queryToken);
        queryToken = strtok(NULL, " \n"); 
        count++;
    }

    // call rank to calculate scores for each document and print them to console
    rank(mapStructPtr, numFiles, spaces+1, queryArray);

    // iterrate through 2D array and free all memory
    for(int k=0; k<spaces+1; k++){
        free(queryArray[k]);
    }
    free(queryArray);
    free(queryLine);
    free(queryToken);
    free(queryLn);
    queryLength = 0;
    queryLineSize = 0;

    // return 1 for true
    return 1;
}

// rank: moves through each document and scores the document for each word in the query and sums the scores 
// inputs: pointer to hashmap, number of words in query, pointer to 2D array storing query
// returns: void
void rank(struct hashmap* hm, int numFiles, int querySize, char** query) {

    // null check inputs
    if(!(hm || query)){
        printf("Passing NULL parameters into rank: returning\n");
        return;
    }

    // computes the score for each document based on TF-IDF rank of search query

    // declare variables to store calculated values etc 
    double score;
    struct wordNode* wordPtr;
    int retrieveMode = 0;
    double tfidf;

    // allocate space for an array to store indicies of files in the file list
    int* indicies = (int*) malloc(sizeof(int*)*numFiles);

    // allocate space for an array to store the tf-idf scores of files in the file list
    double* scores = (double*) malloc(sizeof(double*)*numFiles);

    // allocate space for an array to keep track of query words that have been confirmed to be found or not
    // this prevents repeated searching for words that have already been found to not exist in the hashmap
    int* wordPresence = (int*) malloc(sizeof(int*)*querySize);
    // set default value of words in query to "present in hashmap"
    for(int k=0; k<querySize; k++){
        wordPresence[k] = 1;
    }

        // for each file in the directory
        for(int i=0; i<numFiles; i++){
            // fill indices array with the index of the document in the file list
            indicies[i] = i;
            // set document score to zero
            score = 0.0;

            // for each word in query
            for(int j=0; j<querySize; j++){ 
                // if word is present according to wordPresence array
                if(wordPresence[j]){
                    // reset tf-idf value
                    tfidf = 0.0;
                    // get a pointer to the word in question
                    wordPtr = findWord(hm, query[j], retrieveMode);
                    // if the word was succesfully found
                    if(wordPtr){
                        // calculate the tf-idf score of the word
                        tfidf = tfidfCalc(wordPtr, i, numFiles);
                    }
                    // if the word was not found set its presence to 0 in the word presence array
                    else{
                        wordPresence[j] = 0;
                    }
                    // note if the word was not found its tfidf score will be 0 as this value is reset on each iteration
                    score = score + tfidf;
                }

            }   
            scores[i] = score;
        // save document score into 2D array 
        }
    
    // For debugging: to see unsorted scores
    // printf("\n\n Scores unsorted:\n");
    // for(int i=0; i<numFiles; i++){
    //     printf("Index %d, score: %f\n",indicies[i], scores[i]);
    // }

    // sort scores and whenever you swap indicies do the same in indicies 
    int i, j; 
    double temp1; // for scores
    int temp2; // for indices

    for (i = 0; i < numFiles-1; i++){   

    // QUICKSORT

    // Last i elements are already in place   
        for (j = 0; j < numFiles-i-1; j++){
            if (scores[j] < scores[j+1]){
            // swap(&arr[j], &arr[j+1]);

                // swap(scores[j], scores[j+1])
                temp1 = scores[j];
                scores[j] = scores[j+1];
                scores[j+1] = temp1;

                // swap indicies[j], indicies[j+1]
                temp2 = indicies[j];
                indicies[j] = indicies[j+1];
                indicies[j+1] = temp2;

            }
        }
    }

    // For debugging: to see scores after sort
    // printf("\nSorted scores:\n");
    // for(int i=0; i<numFiles; i++){
    //     printf("Index %d, score: %f\n",indicies[i], scores[i]);
    // }

    FILE *fp;
    // open file in mode 'a' for append
    fp = fopen ("search_scores.txt", "a");

    char* queryWord;

    // 1. open search_scores.txt file
    // 2. print a tab
    // 3. print score as a double %g
    // 4. add newline
    // 5. close file
    
    fprintf(fp, "\nQuery:\n"); 
    for (int i = 0; i<querySize; i++) {
        queryWord = query[i];
        fprintf(fp, "%s ", queryWord);
    }
    fprintf(fp, "\n\nDocument Rankings:\n"); 
    printf("\n\nDocument Rankings:\n"); 

    // print query here
    int index; 

    char* fileName;

    for (int i = 0; i<numFiles; i++) {
        // write to file using fputc() function 
        index = indicies[i];
        fileName = hm->fileNames[index];
            fprintf(fp, "%s    %f\n", fileName, scores[i]);
            printf("%s\n", fileName);
    }
    
    fclose (fp);

    free(indicies);
    free(scores);
    free(wordPresence);
    return;
    
}

// tfidfCalc: perform tf*idf
// input: pointer to the word and doc for which the score is being calculated
// returns: a double containing the tf-idf score
double tfidfCalc(struct wordNode* wordPtr, int docNum, int numFiles){
    // declare variables to store calculated values
    double tfidf = 0.0;
    double idf;
    double tf;

    // create pointer to docList node
    struct docNode* docPtr = wordPtr->docList;

    // if there are any documents for each document
    while(docPtr){
        // check to see if the document being pointed to has the same ID as the docID passed into the function
        if(docPtr->docID == docNum){
            tf = docPtr->termFrequency;
            // cast numFiles and docFrequency to doubles
            idf = ((double) numFiles/((double) wordPtr->docFrequency));
            idf = log(idf);
            tfidf = tf*idf;
            return tfidf;
        }
        // this doc is not the right doc move to the next one
        docPtr=docPtr->nextDoc;
    }
    // I can store the tfidf for a document here if I want to
    //(double*) malloc(sizeof(double));
    //printf("Doc not found in tfidf Calc function: returning score of 0\n");
    return 0.0;
}
