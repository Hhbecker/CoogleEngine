# CoogleEngine
Meet Coogle: Henry's very own C implementation of a search engine backend.

Hashmap vs Hashtable
https://www.geeksforgeeks.org/differences-between-hashmap-and-hashtable-in-java/

How I'll handle collisions: chaining

Key = word+documentID asccii sum
Value = number of occurences of the word in that document

This hashmap will free memory automatically when nodes are removed to prevent memory leaks and maintain performance over time.


To Do 
* answer question at bottom of specs
* ask how to run it on seas shell
* improve lucid chart memory diagram

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
* input of word and docID not in hashmap must return -1
* input of word and docID found in hashmap must return 1 or greater

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


    // Testing hm_create
    // •does it return the correct structure with the correct number of buckets 

    // Testing hash
    // •

    // Testing put
    // •can you add a node to an empty list and to a not empty list
    // •can you overwrite the num_occurences if the key is already present

    // Testing get 
    // •can you can find node in beginning, middle, and end of a list
    // •will get return -1 if its not present

    // Testing remove

    // Testing destroy