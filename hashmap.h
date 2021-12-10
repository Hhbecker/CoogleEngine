#ifndef HASHMAP_H
#define HASHMAP_H
// prevent body of this file from being included more than once by linker

// defines document linked list struct
struct docNode {
        int docID;
        int numOccurences;
        struct docNode* nextDoc; 
};

// defines word linked list struct
struct wordNode {
        char* word;
        int df;
        struct wordNode* nextWord;
        struct docNode* docs;
};

// defines hashmap struct
struct hashmap {
        struct wordNode** pointerArray;
        int num_buckets;
        int num_elements;
};

// defines each function performed by a hashmap instance 
// this acts as an interface that is then implemented in another file
struct hashmap* training(char* directory, char* charBuckets );
void hash_table_insert(struct hashmap* hashmapPtr, char* word, int docID);
struct hashmap* hm_create(int num_buckets);
int hm_get(struct hashmap* hm, char* word, char* document_id);
void hm_put(struct hashmap* hm, char* word, char* document_id, int num_occurrences);
void hm_remove(struct hashmap* hm, char* word, char* document_id);
void hm_destroy(struct hashmap* hm);
int hash(struct hashmap* hm, char* word, char* document_id);

#endif
