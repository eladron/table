#ifndef KEY_H
#define KEY_H

#include <stdint.h>

typedef struct entry_key {
    void *data;
    uint32_t size;
    uint32_t hash_id;
} entry_key_t;

entry_key_t* create_key(void *data, uint32_t size);
void free_key(entry_key_t *key);
inline int compare_keys(entry_key_t *key1, entry_key_t *key2)
{
    return key1->hash_id == key2->hash_id;
}

#endif // KEY_H