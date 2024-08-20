#include "table.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

//template for an example hash function
static uint32_t hash(void *data) {
    uint32_t hash = 0;
    char *str = (char*)data;
    while (*str) {
        hash = hash * 31 + *str++;
    }
    return hash;
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
    new_entry->id = hash(data);
    new_entry->data = data;
    new_entry->next = table->entries;
    new_entry->prev = NULL;
    if (table->entries != NULL) {
        table->entries->prev = new_entry;
    }
    table->entries = new_entry;
    table->count++;

    return new_entry;
}

static void pop_from_table(Table *table, TableEntry *entry) {
    if (entry->prev != NULL) {
        entry->prev->next = entry->next;
    } else {
        table->entries = entry->next;
    }
    if (entry->next != NULL) {
        entry->next->prev = entry->prev;
    }
}

// Function to remove an entry from the table
void remove_from_table(Table* table, uint32_t id) {
    TableEntry* current = table->entries;
    while (current != NULL) {
        if (current->id == id) {
            pop_from_table(table, current);
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
            // Move the found entry to the front of the table
            pop_from_table(table, current);
            if (current != table->entries) {
                current->next = table->entries;
                if (table->entries != NULL) {
                    table->entries->prev = current;
                }
                table->entries = current;
                current->prev = NULL;
            }
            return current;
        }
        current = current->next;
    }
    return NULL; // Entry not found
}