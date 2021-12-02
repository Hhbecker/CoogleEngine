# CoogleEngine
Meet Coogle: Henry's very own C implementation of a search engine.


To do 
* improve lucid chart memory diagram

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
-what is the point of the #define HASHMAP_H command at the top of the header file? It's a compiler thing - find out more 

Each value is assigned a key
The key is input into a hashing function which places the key in a bucket out of N buckets
The key value pair is then added to the end of the linked list at that bucket

A collision, or more specifically, a hash code collision in a HashMap, is a situation where two or more key objects produce the same final hash value and hence point to the same bucket location or array index.
