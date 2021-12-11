#ifndef HASHMAP_H
#define HASHMAP_H
// prevent body of this file from being included more than once by linker

// defines document linked list struct
struct docNode {
        int docID;
        int termFrequency;
        double* tfidf;
        struct docNode* nextDoc; 
};

// defines word linked list struct
struct wordNode {
        char* word;
        int docFrequency;
        struct wordNode* nextWord;
        struct docNode* docList;
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
struct wordNode* findWord(struct hashmap* hm, int index, char* word, int insertMode);
void addDoc(struct wordNode* wordPtr, int docID);
void stop_word(struct hashmap* hm, int numDocs);
struct hashmap* hm_create(int num_buckets);
int hm_get(struct hashmap* hm, char* word, char* document_id);
void hm_put(struct hashmap* hm, char* word, char* document_id, int num_occurrences);
void removeWord(struct hashmap* hm, struct wordNode* trailingPtr, struct wordNode* Ptr);
void freeWord(struct wordNode* wordPtr);
void hm_destroy(struct hashmap* hm);
int hash(int numBuckets, char* word);
void rank(struct hashmap* hm, char** query);
char** read_query(void);

#endif
