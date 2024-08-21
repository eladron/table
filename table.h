#ifndef TABLE_H
#define TABLE_H

#include "entry_key.h"
#include <stdint.h>
#include <stddef.h>

#define TABLE_LENGTH 1024
#define TABLE_ENTRY(ptr, type, member) ((type*)((char*)(ptr) - offsetof(type, member)))


// Define the TableEntry struct
typedef struct table_entry {
    uint32_t key;
    struct table_entry *ptr;
} table_entry_t;

// Define the Table struct
typedef struct table {
    table_entry_t entries[TABLE_LENGTH];
    uint32_t count;
} table_t;

// Function declarations
table_t* init_table();
void table_add(table_entry_t *entry, table_t* table, entry_key_t *key_data);
void table_del(table_t* table, uint32_t key);
table_entry_t* table_find(table_t* table, uint32_t key);
void free_table(table_t* table);

#endif // TABLE_H
