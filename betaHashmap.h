#ifndef HASHMAP_H
#define HASHMAP_H
// prevent body of this file from being included more than once by linker

// defines linked list struct
struct llnode {
        char* word;
        char* document_id;
        int num_occurrences;
        struct llnode* next;
};

// defines hashmap struct
struct hashmap {
        struct llnode** map;
        int num_buckets;
        int num_elements;
};

// defines each function performed by a hashmap instance 
// this acts as an interface that is then implemented in another file
struct hashmap* hm_create(int num_buckets);
int hm_get(struct hashmap* hm, char* word, char* document_id);
void hm_put(struct hashmap* hm, char* word, char* document_id, int num_occurrences);
void hm_remove(struct hashmap* hm, char* word, char* document_id);
void hm_destroy(struct hashmap* hm);
int hash(struct hashmap* hm, char* word, char* document_id);

#endif
