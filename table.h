#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>

// Define the TableEntry struct
typedef struct TableEntry {
    uint32_t id;
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
<<<<<<< HEAD
void add_to_table(Table* table, uint32_t id);
=======
TableEntry* add_to_table(Table* table, void* data);
>>>>>>> c7f2857 (Nothing)
void remove_from_table(Table* table, uint32_t id);
TableEntry* find_entry(Table* table, uint32_t id);

#endif // TABLE_H