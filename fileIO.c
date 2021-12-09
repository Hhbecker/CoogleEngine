#include <stdio.h>    
#include <stdlib.h>
#include <string.h>

int main() {
    // get input from file

    FILE* filePtr = fopen("D1.txt", "r");

    char buf[1023]; // no word will be greater than 1023
    while(fscanf(filePtr, "%s", buf)==1){
        printf("%s\n", buf);

    }

    char* line = NULL;
    size_t len = 0;
    size_t lineSize = 0;

    lineSize = getline(&line, &len, stdin); 

    char* token = strtok(line, " ");

    while(token != NULL){
        printf("%s\n", token);
        token = strtok(NULL, " "); 
    }

    printf("Line: %s\n", line);





}