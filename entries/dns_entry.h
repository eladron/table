#ifndef DNS_ENTRY_H
#define DNS_ENTRY_H

#include <stdlib.h>
#include <string.h>
#include "../table.h"

#define MAX_DOMAIN_NAME_LENGTH 253
#define MAX_ADDRESS_LENGTH 15

typedef struct dns_entry{
    table_entry_t entry;
    entry_key_t key_data;
    char *address;
} dns_entry_t;

dns_entry_t* create_dns_entry(char *domain, char *address) {
    if (domain == NULL || address == NULL) {
        return NULL; // Key data or data entry is NULL
    }
    dns_entry_t *entry = (dns_entry_t*)malloc(sizeof(dns_entry_t));
    if (entry == NULL) {
        return NULL; // Allocation failed
    }
    entry->key_data.data = malloc(strlen(domain) + 1);
    if (entry->key_data.data == NULL) {
        goto key_fail; // Allocation failed
    }
    strcpy(entry->key_data.data, domain);
    entry->key_data.size = strlen(domain) + 1;
    entry->address = malloc(strlen(address) + 1);
    if (entry->address == NULL) {
        goto value_fail; // Allocation failed
    }
    strcpy(entry->address, address);
    entry->entry.ptr = NULL;
    entry->entry.key = 0;
    return entry;

value_fail:
    free(entry->key_data.data);

key_fail:
    free(entry);
    return NULL;
}

void free_dns_entry(dns_entry_t *entry) {
    if (entry == NULL) {
        return; // Entry is NULL
    }
    free(entry->key_data.data);
    free(entry->address);
    free(entry);
}

#endif // DNS_ENTRY_H
