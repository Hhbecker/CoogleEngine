# CoogleEngine
Meet Coogle: Henry's very own C implementation of a search engine backend.

Hashmap vs Hashtable
https://www.geeksforgeeks.org/differences-between-hashmap-and-hashtable-in-java/

How I'll handle collisions: chaining

Key = word+documentID asccii sum
Value = number of occurences of the word in that document


To do 
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

Questions
* why would the number of occurences passed into hm_put ever be more than one?
* what's the deal with this chaining thing - why wouldn't I just increment the num_occurences of the llnode struct?
* what is the point of the #define HASHMAP_H command at the top of the header file? It's a compiler thing - find out more 

Each value is assigned a key
The key is input into a hashing function which places the key in a bucket out of N buckets
The key value pair is then added to the end of the linked list at that bucket

A collision, or more specifically, a hash code collision in a HashMap, is a situation where two or more key objects produce the same final hash value and hence point to the same bucket location or array index.
