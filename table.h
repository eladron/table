#ifndef TABLE_H
#define TABLE_H

#include "entry_key.h"
#include <stdint.h>

// Define the TableEntry struct
typedef struct table_entry {
    entry_key_t *key;
    void *value;
    struct table_entry *prev;
    struct table_entry *next;
} table_entry_t;

// Define the Table struct
typedef struct table {
    table_entry_t* entries;
    uint32_t count;
} table_t;

// Function declarations
table_t* create_table();
table_entry_t* add_to_table(table_t* table, entry_key_t *key, void *value);
void remove_from_table(table_t* table, entry_key_t *key);
table_entry_t* find_entry(table_t* table, entry_key_t *key);
void destroy_table(table_t* table);

#endif // TABLE_H