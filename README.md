# CoogleEngine
Meet Coogle: Henry's very own C implementation of a search engine backend.

Hashmap vs Hashtable
https://www.geeksforgeeks.org/differences-between-hashmap-and-hashtable-in-java/

How I'll handle collisions: chaining

Key = word+documentID asccii sum
Value = number of occurences of the word in that document

This hashmap will free memory automatically when nodes are removed to prevent memory leaks and maintain performance over time.


To Do 
* read through specs and powerpoint on project 5
* make testing suite that uses fileIO to accomplish operations that search engine would need (test each scenario layed out below for each method)

* compare this algorithm to page rank algorithm


* in put method: efficiency gain by adding new node to front instead of back? 

* transfer testing print statement from hashmap.c into assert statements in test.c

* man pages
* GDB
* valgrind
* make file
* assert statements to test
* comment in info on each line of makefile 
* for each function for each parameter null check it 
* use Strcmp = string compare 
* write in some assembly directly into C to make it faster 

* make a demo folder so people can clone the repo and search amongst given files (maybe integrate a java or python GUI)

Questions
* how would I go about integrating a Java or Python GUI with this C code?
* what is the point of the #define HASHMAP_H command at the top of the header file? It's a compiler thing - find out more 

Why would the number of occurences passed into hm_put ever be more than one?
the number of occurences passed into put is determined by calling get and incrementing the number of occurences returned

Is chaining the linked list in a buckett design choice or is it overwriting num occurences 

Each value is assigned a key
The key is input into a hashing function which places the key in a bucket out of N buckets
The key value pair is then added to the end of the linked list at that bucket

A collision, or more specifically, a hash code collision in a HashMap, is a situation where two or more key objects produce the same final hash value and hence point to the same bucket location or array index.

## A satsifying bug fix 
After completing each method and writing a simple test case I ran Valgrind to check for memory leaks. While I did not have any leaks I did have 3 invalid read errors which led to a segmentation fault. I realized quickly that 1.) I did not set the pointer to the word and document id passed in as a parameter to NULL in the remove method. This means the pointers to the word and  , the pointer to the word

In C, pointers are passed by value meaning a copy of the value is made and that copy is passed into the function. Therefore, setting the paremter pointer equal to NULL is setting a copy of the original pointer equal to NULL but the original pointer used in the calling function remains. Therefore, one needs to dereference the pointer and set that value to null instead of just assigning the copy pointer to NULL.



## Testing the hashmap

* does each method handle NULL and invalid parameters properly?
* does each method perform as intended? 
* are there any memory leaks?
* does the test suite work on the SEAS shell?

### struct hashmap* hm_create(int num_buckets);
* input of negative or zero buckets must return NULL pointer

### int hash(struct hashmap* hm, char* word, char* document_id);  
* input of null pointer must print warning message and return -1

### int hm_get(struct hashmap* hm, char* word, char* document_id);
* input of NULL pointer must return -1

Five get cases 
1. list not initialized 
2. list initialized but item not present (return -1)
3. list initialized and item at front of list 
4. list initialized and item in between two nodes
5. list initialized and item at rear of list

### void hm_put(struct hashmap* hm, char* word, char* document_id, int num_occurrences);
* input of NULL pointer must return with a warning message
* input of negative num_occurences must return with a warning message 

Three put cases:
1. list not initialized 
2. adding item to rear of existing list
3. overwriting num occurences in an existing node

### void hm_remove(struct hashmap* hm, char* word, char* document_id);
* input of null pointer must return with a warning message 

Six remove cases:
1. List uninitialized
2. Target node is not found (list is present).
3. Target node is the only node in the list.
4. Target node is the first node but has nodes after it.
5. Target node is not first but has no nodes after it.
6. Target node is in between two nodes.

### void hm_destroy(struct hashmap* hm);
* input of null pointer should print warning message and return
* input of valid pointer should free all associated memory 

1. linked lists uninitialized
2. one or more linked lists initialized 

///////////////////////////////////////////////////////////////////////

A formal description of the search problem:

### Input: 
* search query string consisting of a number of words entered into command line (standard in) 
* Set of documents labelled D1.txt, D2.txt,...D_i.txt etc. in a subdirectory titled p5docs

### Task: 
1. Training phase
    A. Create a hashmap where:
        * Each bucket contains a linked list
        * Each linked list node is a struct containing a single word and the DF of that word
        * each word struct contains a pointer to a linked 
        * each node in this linked list is a struct containing a single document ID and the num occurences of the word in that document
    B. Remove stop words from hashmap 

2. Search phase 
    A. compute DF-IDF?

    B. create a file called search_scores.txt
    C. Save search query and list of documents by their DF-IDF into search_scores.txt in format filename:score for your query on each document in descending order (delimited by new lines)
    C. Display contents of the most relevant document to the terminal 


### Assumptions and additional specifications
* *each document contains several words (how would you make sure empty docs don't crash your program?)
* no word is longer than 20 characters (it is possible to design a solution without this assumptions).
* the document only contains words from the English alphabet (no digits or special characters from the keyboard)
* all words are in lower case (see if you can write a program that is case insensitive) – if you implement this option, then please indicate this clearly in your documentation (code comments).
* the search query phrase can be of an arbitrary length as long as each word is no longer than 20 characters
* the search query phrase is entered by the user at run-time after the training phase (when all the documents have been read)
* The program must prompt the user for the query keywords and then return the result of the search
* After returning the results the program will return to prompt for the next query set or for special symbol # to exit the program. 
* The number of buckets in the hash table is specified at run-time by the user.
* You should also implement the option for the number of buckets to be computed statically during the training phase
* You should not make any assumptions on the contents of the documents or the query words
* create a documentation where you specify the assumptions you made and what hash function you used etc

#### Necessary functions
    int hash(char* word){
        // hashes word to a bucket
    }

    void hash_table_insert(char* word, char* docID){
        // hashes word and creates new node for the word or updates existing document frequency for that word and document combo
    }

    void training(set of documents){
        returns the populated hash table as output
    }

    void read_query() {
        read the search query from the command line
    }

    void rank() {
        // computes the score for each document based on DF-IDF rank of search query
        // must also determine if there is no document with a match (if none of the words in the search query appear in any of the documents)
    }

    void stop_word(){
        // identifies and removes stop words from hashmap
    } 

    int main(){
        // first prompts user for number of hashtable buckets 
        // calls the training method to create and fill hashtable 

        // next prompt user for search query of x for exit 
        // “Enter Search String or X to Exit”
        // if X exit program
        // if not X call read_query function 
        // compute ranking and print outputs
        // return back to prompt “Enter Search String or X to Exit”
    }
  
makefile
* make sure that everything compiles correctly on the SEAS shell by evoking "make" with no arguments
* the executable should be named “search”
* use gcc to compile

The term frequency-inverse document frequency (TF-IDF) page rank method

Bag of words (BOW) model = a table with occurrence counts of each word in the query for each document is created

#### Term Frequency (TF)
I will be using the raw frequency of words: term frequency(word, docID) = TF(word, docID) = the number of times the word appears in the document.

There are variations of term frequency that are used in different search algorithms. Since raw frequency may not always relate to relevance they divide the frequency by the number of words in the document to get a normalized raw frequency. 

#### Document Frequency (DF)
A rare term/word is often more informative than frequent terms. For example, stop words such as “the” “for” etc. have a high term frequency (they are repeated many times in each document) but are also probably present in most if not all documents (high document frqeuncy) so they are not helpful in choosing a relevant document.

document frequency(word) = DF(word) = number of documents that contain a word

inverse document frequency(word) = IDF(word) = log(N/DF) where N is the total number of documents in the directory, log is the natural log function inC, and one is added to DF when DF is zero to avoid division by zero. The logarithm is used to lessen the effect of the IDF on the overall ranking.

The tf-idf score gives us a measure of how important is a word to a document among a set of documents. It uses local (term frequency) and global (inverse document frequency) to scale down the frequency of common terms and scale up the frequency/score of rare terms.

The document rank for a single word of the search query = TF*IDF
The overall document rank for all words in the search query is the sum of ranks for individual words

Jonathan's office hours to do list
* figure out how to read hardcoded documents
* figure out glob function for reading n documents 
* figure out makefile 


    To do 
    * create flowchart
    * figure out how to open each file and call printf on each word
    * test old hashmap to figure out what's wrong with it 
    * reread all of specifications to figure out exact structure of new hashmap and DF-IDF calculation 
    * figure out how to make new hashmap structure 
    
    * worry about implementing glob after you get the rest of the thing working
    * I'd like to call the function on a subdirectory of files instead of having the code in the same directory as the text files - figure out how to open p5docs as a subdirectory

    * make a hashing function where num buckets is always odd and explain why in readMe

What to submit
* the source code files on github with function header documentation
* the makefile, and (3) 
* documentation 

Documentation includes 
* description of your implementation 
* a flowchart
* explanation of algorithms and how each function works together
* name documentation H-Becker.pdf.
* be sure everything works on SEAS shell if it doesn't compile you get a zero


References: Some references for more information on tf-idf method for document retrieval.
● H. Wu and R. Luk and K. Wong and K. Kwok. "Interpreting TF-IDF term weights as making relevance
decisions". ACM Transactions on Information Systems, 26 (3). 2008.
● J. Ramos, “Using TF-IDF to determine word relevance in document queries”.