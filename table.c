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
    memset(table, 0, sizeof(table_t));
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
    uint32_t index = key->hash_id % TABLE_LENGTH;
    new_entry->next = table->entries[index];
    new_entry->prev = NULL;
    if (table->entries[index] != NULL) {
        table->entries[index]->prev = new_entry;
    }
    table->entries[index] = new_entry;
    table->count++;

    return new_entry;
}

// Function to pop an entry from the table
static void pop_from_table(table_t *table, table_entry_t *entry) {
    if (entry->prev != NULL) {
        entry->prev->next = entry->next;
    } else {
        table->entries[entry->key->hash_id % TABLE_LENGTH] = entry->next;
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

static table_entry_t* get_entry_by_id(table_t* table, uint32_t id) {
    uint32_t index = id % TABLE_LENGTH;
    table_entry_t* current = table->entries[index];
    while (current != NULL) {
        if (current->key->hash_id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to remove an entry from the table
void remove_from_table(table_t* table, entry_key_t *key) {
    if (table == NULL || table->count == 0) {
        return; // table_t is NULL or empty
    }
    uint32_t id = key->hash_id;
    table_entry_t *entry = get_entry_by_id(table, id);
    if (entry != NULL) {
        pop_from_table(table, entry);
        free_entry(entry);
        table->count--;
    }
}

// Function to find an entry in the table
table_entry_t* find_entry(table_t* table, entry_key_t *key) {
    if (table == NULL || table->count == 0) {
        return NULL; // table_t is NULL or empty
    }
    uint32_t id = key->hash_id;
    uint32_t index = id % TABLE_LENGTH;
    table_entry_t* entry = get_entry_by_id(table, id);
    if (entry != NULL) {
        pop_from_table(table, entry);
        if (entry != table->entries[index]) {
            entry->next = table->entries[index];
            if (table->entries[index] != NULL) {
                table->entries[index]->prev = entry;
            }
            table->entries[index] = entry;
            entry->prev = NULL;
        }
    }

    return entry; 
}

// Function to destroy the table and free all entries
void destroy_table(table_t* table) {
    if (table == NULL) {
        return; // table_t is NULL
    }
    for (uint32_t i = 0; i < TABLE_LENGTH; i++) {
        table_entry_t* current = table->entries[i];
        while (current != NULL) {
            table_entry_t* next = current->next;
            free_entry(current);
            current = next;
        }
    }
    free(table);
}