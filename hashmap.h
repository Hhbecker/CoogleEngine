#ifndef HASHMAP_H
#define HASHMAP_H

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
struct hashmap* hm_create(int num_buckets);
//int hm_get(struct hashmap* hm, char* word, char* document_id);
//void hm_put(struct hashmap* hm, char* word, char* document_id, int num_occurrences);
//void hm_remove(struct hashmap* hm, char* word, char* document_id);
//void hm_destroy(struct hashmap* hm);
//int hash(struct hashmap* hm, char* word, char* document_id);

#endif
