#include "table.h"
#include <stdio.h>
#include <string.h>

// Function to create a new table
Table* create_table() {
    Table* table = (Table*)malloc(sizeof(Table));
    if (table == NULL) {
        return NULL; // Allocation failed
    }
    table->entries = NULL;
    table->count = 0;
    return table;
}

// Function to add an entry to the table
TableEntry* add_to_table(Table* table, void *data) {
    if (table == NULL) {
        return NULL; // Table is NULL
    }
    TableEntry* new_entry = (TableEntry*)malloc(sizeof(TableEntry));
    if (new_entry == NULL) {
        return NULL; // Allocation failed
    }
    new_entry->id = id;
    new_entry->next = table->entries;
    new_entry->prev = NULL;
    if (table->entries != NULL) {
        table->entries->prev = new_entry;
    }
    table->entries = new_entry;
    table->count++;

    return new_entry;
}

// Function to remove an entry from the table
void remove_from_table(Table* table, uint32_t id) {
    TableEntry* current = table->entries;
    while (current != NULL) {
        if (current->id == id) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                table->entries = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            free(current);
            table->count--;
            return;
        }
        current = current->next;
    }
}

// Function to find an entry in the table
TableEntry* find_entry(Table* table, uint32_t id) {
    if (table == NULL) {
        return NULL; // Table is NULL
    }
    TableEntry* current = table->entries;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL; // Entry not found
}