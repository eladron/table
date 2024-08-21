#ifndef KEY_H
#define KEY_H

#include <stdint.h>

typedef struct entry_key {
    void *data;
    uint32_t size;
} entry_key_t;

entry_key_t* create_key(void *data, uint32_t size);
void free_key(entry_key_t *key);

#endif // KEY_H
