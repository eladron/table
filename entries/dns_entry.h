#ifndef DNS_ENTRY_H
#define DNS_ENTRY_H

#include <stdlib.h>
#include <string.h>

#define MAX_DOMAIN_NAME_LENGTH 253
#define MAX_ADDRESS_LENGTH 15


typedef struct dns_key_data {
    char domain[MAX_DOMAIN_NAME_LENGTH];
} dns_key_data_t;

dns_key_data_t* create_dns_key(char *domain) {
    if (domain == NULL || strlen(domain) > MAX_DOMAIN_NAME_LENGTH) {
        return NULL; // Domain name is NULL or too long
    }
    dns_key_data_t *key_data  = (dns_key_data_t*)malloc(sizeof(dns_key_data_t));
    memset(key_data, 0, sizeof(dns_key_data_t));
    if (key_data == NULL) {
        return NULL; // Allocation failed
    }
    strcpy(key_data->domain, domain);
    return key_data;
}

typedef struct dns_data_entry {
    char address[MAX_ADDRESS_LENGTH];
} dns_data_entry_t;

dns_data_entry_t* create_dns_data_entry(char *address) {
    dns_data_entry_t *entry = (dns_data_entry_t*)malloc(sizeof(dns_data_entry_t));
    memset(entry, 0, sizeof(dns_data_entry_t));
    if (entry == NULL) {
        return NULL; // Allocation failed
    }
    strcpy(entry->address, address);
    return entry;
}

#endif // DNS_ENTRY_H