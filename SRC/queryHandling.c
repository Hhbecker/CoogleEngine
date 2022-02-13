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

// prompt user for search query and save it as a string
int readQuery(struct hashmap* mapStructPtr, int numFiles){

    // most breakable function
    // adding space after last word breaks it


    // prompt user for search query
    printf("\nEnter search string or x to exit:\n");

    char* queryLn = NULL;
    char* queryToken = NULL;
    size_t queryLength = 0;
    size_t queryLineSize = 0;

    queryLineSize = getline(&queryLn, &queryLength, stdin); 

    // copy query line into another variable 
    char* queryLine = NULL;
    queryLine = strdup(queryLn);
    free(queryLn);

    if(queryLineSize == 0){
        // to avoid error
    }

    if(queryLine[0]=='\n'){
        printf("query is empty, try again.\n\n");
        return 1;
    }

    int spaces = 0;
        for(int i=0; queryLine[i]!='\0'; i++){
            if(queryLine[i] == ' '){
                spaces++;
            
            }
        }

    queryToken = strtok(queryLine, " \n");
    

        if(spaces==0){
        if((int) strlen(queryToken)==1){
            if((int) queryToken[0] == 120){
                // user inputed X
                return 0;
            }
        }
    }

    // maximum word length in query is 20 chars
    char** queryArray = (char**) malloc(sizeof(char*)*(spaces+1));

    //char* copy;
    int count = 0;

    while(queryToken != NULL){
        queryArray[count] = strdup(queryToken);
        queryToken = strtok(NULL, " \n"); 
        count++;
    }

    

    // 6. call rank to calculate scores for each document and print them to console
    rank(mapStructPtr, numFiles, spaces+1, queryArray);

    for(int k=0; k<spaces+1; k++){
        free(queryArray[k]);
    }
    free(queryArray);
    free(queryLine);
    free(queryToken);
    queryLength = 0;
    queryLineSize = 0;


    // return 1 for true
    return 1;
}


void rank(struct hashmap* hm, int numFiles, int querySize, char** query) {

    if(!(hm || query)){
        printf("Passing NULL parameters into rank: returning\n");
        return;
    }

    // computes the score for each document based on DF-IDF rank of search query

    // must be able to determine if there is no document with a match 
    // (if none of the words in the search query appear in any of the documents)
  
    double score;
    struct wordNode* wordPtr;
    int retrieveMode = 0;
    double tfidf;

    int* indicies = (int*) malloc(sizeof(int*)*numFiles);

    double* scores = (double*) malloc(sizeof(double*)*numFiles);

    int* wordPresence = (int*) malloc(sizeof(int*)*querySize);

    for(int k=0; k<querySize; k++){
        wordPresence[k] = 1;
    }

    // create an array of 1's size numWords in query called wordPresence
    // if word not found set that wordPresence index to zero
    // check word presence index before calling find word

        // for each document
        for(int i=0; i<numFiles; i++){
            // fill indices array
            indicies[i] = i;
            // set document score to zero
            score = 0.0;

            // for each word
            for(int j=0; j<querySize; j++){ 
                if(wordPresence[j]){
                    tfidf = 0.0;

                    wordPtr = findWord(hm, query[j], retrieveMode);

                    if(wordPtr){
                        tfidf = tfidfCalc(wordPtr, i, numFiles);
                    }
                    else{
                        wordPresence[j] = 0;
                    }
                    score = score + tfidf;
                }

            }   
            scores[i] = score;
        //         save document score into 2D array 
        //         sort array using quicksort
        //         print rankings to file and to console
        }
    
    // sort scores and whenever you swap indicies do the same in indicies 

    double temp1;
    int temp2;

    // printf("\n\n Scores unsorted:\n");

    // for(int i=0; i<numFiles; i++){
    //     printf("Index %d, score: %f\n",indicies[i], scores[i]);
    // }

    int i, j;

    for (i = 0; i < numFiles-1; i++){   

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

    // printf("\nSorted scores:\n");

    // for(int i=0; i<numFiles; i++){
    //     printf("Index %d, score: %f\n",indicies[i], scores[i]);
    // }

    FILE *fp;
    // fopen in mode 'a' for append
    fp = fopen ("search_scores.txt", "a");

    //char* concatenation;
    //char* fileName;
    char* queryWord;

    // 1. get correct fileName pointed at by fileName char pointer
    // 2. print a tab
    // 3. print score as a double %g
    // 4. add newline

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


// 
double tfidfCalc(struct wordNode* wordPtr, int docNum, int numFiles){
    double tfidf = 0.0;

    // if(wordPtr->docList->tfidf){
    //     // dereference pointer with *
    //     tfidf = *wordPtr->docList->tfidf;
    //     return tfidf;
    // }
    //else{
        double idf;
        double tf;

        struct docNode* docPtr = wordPtr->docList;

        while(docPtr){
            if(docPtr->docID == docNum){
                tf = docPtr->termFrequency;
               // cast numFiles and docFrequency to doubles
                idf = ((double) numFiles/((double) wordPtr->docFrequency));
                idf = log(idf);
                tfidf = tf*idf;
                return tfidf;
            }
            docPtr=docPtr->nextDoc;
        }
        // I can store the tfidf for a document here if I want to
        //(double*) malloc(sizeof(double));
        //printf("Doc not found in tfidf Calc function: returning score of 0\n");
        return 0.0;
    //}
}
