#include "table.h"
#include <stdio.h>
#include <stdlib.h>

//template for an example hash function
static uint32_t hash(entry_key_t *key) {
    uint32_t hash = 5381;
    char *str = (char*)(key->data);
    for (uint32_t i = 0; i < key->size; i++) {
        hash = ((hash << 5) + hash) + str[i];
    }
    return hash;
}

// Function to create a new table
table_t* init_table() {
    table_t* table = (table_t*)malloc(sizeof(table_t));
    if (table == NULL) {
        return NULL; // Allocation failed
    }
    table->count = 0;
    for (uint32_t i = 0; i < TABLE_LENGTH; i++) {
        table->entries[i].ptr = NULL;
        table->entries[i].key = 0;
    }
    return table;
}

// Function to add an entry to the table
void table_add(table_entry_t *entry, table_t* table, entry_key_t *key_data) {
    if (table == NULL || key_data == NULL) {
        goto fail; // table_t or entry_key_t is NULL
    }

    uint32_t key = hash(key_data);
    if (table_find(table, key) != NULL) {
        goto fail; // Entry with the same key already exists
    }
    
    int index = key % TABLE_LENGTH;
    for (int i = index, j = index; i >= 0 || j < TABLE_LENGTH; i--, j++) {
        if (i >=0 && table->entries[i].key == 0 && table->entries[i].ptr == NULL) {
            index = i;
            break;
        }
        if (j <TABLE_LENGTH && table->entries[j].key == 0 && table->entries[j].ptr == NULL) {
            index = j;
            break;
        }
    }

    table->entries[index].key = key;
    table->entries[index].ptr = entry;
    entry->ptr = &table->entries[index];
    entry->key = key;
    table->count++;
    return;
fail:
    entry->ptr = NULL;
    entry->key = 0;
    return;
}

static int get_index_by_key(table_t* table, uint32_t key) {
    int index = key % TABLE_LENGTH;
    for(int i=index, j=index; i >= 0 || j < TABLE_LENGTH; i--, j++) {
        if (i >= 0 && table->entries[i].key == key) {
            return i;
        }
        if (j < TABLE_LENGTH && table->entries[j].key == key) {
            return j;
        }
    }
    return -1;
}

// Function to remove an entry from the table
void table_del(table_t* table, uint32_t key) {
    if (table == NULL || table->count == 0) {
        return; // table_t is NULL or empty
    }
    int index = get_index_by_key(table, key);
    table->entries[index].key = 0;
    table->entries[index].ptr = NULL;
    table->count--;
}

static void swap_entries(table_t* table, int index1, int index2) {
    table_entry_t *tmp = table->entries[index1].ptr;
    uint32_t tmp_key = table->entries[index1].key;
    table->entries[index1].key = table->entries[index2].key;
    table->entries[index2].key = tmp_key;
    table->entries[index1].ptr = table->entries[index2].ptr;
    table->entries[index2].ptr = tmp;
    table->entries[index1].ptr->ptr = &table->entries[index1];
    table->entries[index2].ptr->ptr = &table->entries[index2];
}

// Function to find an entry in the table
table_entry_t* table_find(table_t* table, uint32_t key) {
    if (table == NULL || table->count == 0) {
        return NULL; // table_t is NULL or empty
    }
    
    int supposed_index = key % TABLE_LENGTH;
    int index = get_index_by_key(table, key);
    if (index == -1) {
        return NULL;
    }
    if (table->entries[supposed_index].key != key) {
        swap_entries(table, supposed_index, index);
    }
    return table->entries[supposed_index].ptr;
}

// Function to destroy the table and free all entries
void free_table(table_t* table) {
    if (table == NULL) {
        return; // table_t is NULL
    }
    free(table);
}
