#include "table.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to create a new table
table_t* create_table() {
    table_t* table = (table_t*)malloc(sizeof(table_t));
    if (table == NULL) {
        return NULL; // Allocation failed
    }
    table->entries = NULL;
    table->count = 0;
    return table;
}


// Function to add an entry to the table
table_entry_t* add_to_table(table_t* table, entry_key_t *key, void *value) {
    if (table == NULL || key == NULL) {
        return NULL; // table_t or key is NULL
    }

    if (find_entry(table, key) != NULL) {
        return NULL; // Entry already exists
    }

    table_entry_t* new_entry = (table_entry_t*)malloc(sizeof(table_entry_t));
    if (new_entry == NULL) {
        return NULL; // Allocation failed
    }
    new_entry->key = key;
    new_entry->value = value;
    new_entry->next = table->entries;
    new_entry->prev = NULL;
    if (table->entries != NULL) {
        table->entries->prev = new_entry;
    }
    table->entries = new_entry;
    table->count++;

    return new_entry;
}

// Function to pop an entry from the table
static void pop_from_table(table_t *table, table_entry_t *entry) {
    if (entry->prev != NULL) {
        entry->prev->next = entry->next;
    } else {
        table->entries = entry->next;
    }
    if (entry->next != NULL) {
        entry->next->prev = entry->prev;
    }
}

// Function to free an entry
static void free_entry(table_entry_t *entry) {
    free_key(entry->key);
    free(entry->value);
    free(entry);
}

// Function to remove an entry from the table
void remove_from_table(table_t* table, entry_key_t *key) {
    if (table == NULL || table->count == 0) {
        return; // table_t is NULL or empty
    }
    uint32_t id = key->hash_id;
    table_entry_t* current = table->entries;
    while (current != NULL) {
        if (current->key->hash_id == id) {
            pop_from_table(table, current);
            free_entry(current);
            table->count--;
            return;
        }
        current = current->next;
    }
}

// Function to find an entry in the table
table_entry_t* find_entry(table_t* table, entry_key_t *key) {
    if (table == NULL || table->count == 0) {
        return NULL; // table_t is NULL or empty
    }
    uint32_t id = key->hash_id;
    table_entry_t* current = table->entries;
    while (current != NULL) {
        if (current->key->hash_id == id) {
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

// Function to destroy the table and free all entries
void destroy_table(table_t* table) {
    if (table == NULL) {
        return; // table_t is NULL
    }
    table_entry_t* current = table->entries;
    while (current != NULL) {
        table_entry_t* next = current->next;
        free_entry(current);
        current = next;
    }
    free(table);
}