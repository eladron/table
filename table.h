#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>

// Define the TableEntry struct
typedef struct TableEntry {
    uint32_t id;
    void *data;
    struct TableEntry *prev;
    struct TableEntry *next;
} TableEntry;

// Define the Table struct
typedef struct {
    TableEntry* entries;
    uint32_t count;
} Table;

// Function declarations
Table* create_table();
TableEntry* add_to_table(Table* table, void* data);
void remove_from_table(Table* table, uint32_t id);
TableEntry* find_entry(Table* table, uint32_t id);
void destroy_table(Table* table);

#endif // TABLE_H