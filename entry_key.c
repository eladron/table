#include "entry_key.h"
#include <stdlib.h>

//template for an example hash function
static uint32_t hash(entry_key_t *key) {
    uint32_t hash = 0;
    char *str = (char*)(key->data);
    for (uint32_t i = 0; i < key->size; i++) {
        hash = hash * 31 + str[i];
    }
    return hash;
}

entry_key_t* create_key(void *data, uint32_t size) {
    entry_key_t *key = (entry_key_t*)malloc(sizeof(entry_key_t));
    if (key == NULL) {
        return NULL; // Allocation failed
    }
    key->data = data;
    key->size = size;
    key->hash_id = hash(key);
    return key;
}

void free_key(entry_key_t *key) {
    free(key->data);
    free(key);
    key = NULL;
}