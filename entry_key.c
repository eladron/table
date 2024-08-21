#include "entry_key.h"
#include <stdlib.h>

entry_key_t* create_key(void *data, uint32_t size) {
    entry_key_t *key = (entry_key_t*)malloc(sizeof(entry_key_t));
    if (key == NULL) {
        return NULL; // Allocation failed
    }
    key->data = data;
    key->size = size;
    return key;
}

void free_key(entry_key_t *key) {
    free(key->data);
    free(key);
}
