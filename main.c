#include "table.h"
#include "entries/dns_entry.h"
#include <stdio.h>

#define TEST_DOMAIN "example.com"
#define TEST_ADDRESS "192.168.0.1"

// Tests
int test_create_table() {
    table_t* table = create_table();
    if (table == NULL) {
        return 0;
    }
    for (uint32_t i = 0; i < TABLE_LENGTH; i++) {
        if (table->entries[i] != NULL) {
            return 0;
        }
    }
    if (table->count != 0) {
        return 0;
    }
    destroy_table(table);
    return 1;
}

int test_add_to_table() {
    table_t* table = create_table();
    if (table == NULL) {
        return 0;
    }
    entry_key_t *key = create_key(create_dns_key(TEST_DOMAIN), sizeof(dns_key_data_t));
    if (key == NULL) {
        return 0;
    }
    table_entry_t *te = add_to_table(table, key, create_dns_data_entry(TEST_ADDRESS));
    if (te == NULL) {
        return 0;
    }
    if (table->count != 1) {
        return 0;
    }
    destroy_table(table);
    return 1;
}

int test_remove_from_table() {
    table_t* table = create_table();
    if (table == NULL) {
        return 0;
    }
    entry_key_t *key = create_key(create_dns_key(TEST_DOMAIN), sizeof(dns_key_data_t));
    if (key == NULL) {
        return 0;
    }
    table_entry_t *te = add_to_table(table, key, create_dns_data_entry(TEST_ADDRESS));
    if (te == NULL) {
        return 0;
    }
    remove_from_table(table, key);
    if (table->count != 0) {
        return 0;
    }
    destroy_table(table);
    return 1;
}

int test_find_entry() {
    table_t* table = create_table();
    if (table == NULL) {
        return 0;
    }
    entry_key_t *key = NULL;
    key = create_key(create_dns_key(TEST_DOMAIN), sizeof(dns_key_data_t));
    if (key == NULL) {
        return 0;
    }
    table_entry_t *te = add_to_table(table, key, create_dns_data_entry(TEST_ADDRESS));
    if (te == NULL) {
        return 0;
    }
    table_entry_t *found = find_entry(table, key);
    if (found == NULL) {
        return 0;
    }
    if (found->key->hash_id != te->key->hash_id) {
        return 0;
    }
    destroy_table(table);
    return 1;
}

int test_find_entry_not_found() {
    table_t* table = create_table();
    if (table == NULL) {
        return 0;
    }
    entry_key_t *key = create_key(create_dns_key(TEST_DOMAIN), sizeof(dns_key_data_t));
    if (key == NULL) {
        return 0;
    }
    table_entry_t *te = add_to_table(table, key, create_dns_data_entry(TEST_ADDRESS));
    if (te == NULL) {
        return 0;
    }
    key = create_key(create_dns_key("exampleeee.com"), sizeof(dns_key_data_t));
    if (key == NULL) {
        return 0;
    }
    table_entry_t *found = find_entry(table, key);
    if (found != NULL) {
        return 0;
    }
    destroy_table(table);
    free_key(key);
    return 1;
}

int test_destroy_table() {
    table_t* table = create_table();
    if (table == NULL) {
        return 0;
    }
    entry_key_t *key = create_key(create_dns_key(TEST_DOMAIN), sizeof(dns_key_data_t));
    if (key == NULL) {
        return 0;
    }
    table_entry_t *te = add_to_table(table, key, create_dns_data_entry(TEST_ADDRESS));
    destroy_table(table);
    return 1;
}

int test_add_remove_find() {
    table_t* table = create_table();
    if (table == NULL) {
        return 0;
    }
    entry_key_t *key = create_key(create_dns_key(TEST_DOMAIN), sizeof(dns_key_data_t));
    if (key == NULL) {
        return 0;
    }
    table_entry_t *te = add_to_table(table, key, create_dns_data_entry(TEST_ADDRESS));
    if (te == NULL) {
        return 0;
    }
    table_entry_t *found = find_entry(table, key);
    if (found == NULL) {
        return 0;
    }
    remove_from_table(table, key);
    key = create_key(create_dns_key(TEST_DOMAIN), sizeof(dns_key_data_t));
    if (key == NULL) {
        return 0;
    }
    found = find_entry(table, key);
    if (found != NULL) {
        return 0;
    }
    destroy_table(table);
    free_key(key);
    return 1;
}

int test_add_already_exists() {
    table_t *table = create_table();
    if (table == NULL) {
        return 0;
    }
    entry_key_t *key = create_key(create_dns_key(TEST_DOMAIN), sizeof(dns_key_data_t));
    entry_key_t *key2 = create_key(create_dns_key(TEST_DOMAIN), sizeof(dns_key_data_t));
    if (key == NULL) {
        return 0;
    }
    table_entry_t *te = add_to_table(table, key, create_dns_data_entry(TEST_ADDRESS));
    if (te == NULL) {
        return 0;
    }
    dns_data_entry_t *data = create_dns_data_entry(TEST_ADDRESS);
    table_entry_t *te2 = add_to_table(table, key2, data);
    if (te2 != NULL) {
        return 0;
    }
    destroy_table(table);
    free_key(key2);
    free(data);
    return 1;
    
}

int main() {
    int tests_passed = 0;
    int num_tests = 8;
    tests_passed += test_create_table();
    tests_passed += test_add_to_table();
    tests_passed += test_remove_from_table();
    tests_passed += test_find_entry();
    tests_passed += test_find_entry_not_found();
    tests_passed += test_destroy_table();
    tests_passed += test_add_remove_find();
    tests_passed += test_add_already_exists();
    printf("Tests passed: %d/%d\n", tests_passed, num_tests);
    return 0;
}
