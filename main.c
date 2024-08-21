#include "table.h"
#include "entries/dns_entry.h"
#include <stdio.h>

#define TEST_DOMAIN ("example.com")
#define TEST_DOMAIN2 ("example2.com")
#define TEST_DOMAIN3 ("example3.com")
#define TEST_ADDRESS ("192.168.0.1")

// Tests
static int test_init_table() {
    table_t* table = init_table();
    int res = 0;
    if (table == NULL) {
        return 0;
    }
    for (uint32_t i = 0; i < TABLE_LENGTH; i++) {
        if (table->entries[i].ptr != NULL || table->entries[i].key != 0) {
            goto end;
        }
    }
    if (table->count != 0) {
        goto end;
    }
    res = 1;
end:
    free_table(table);
    return res;
}

static int test_add_to_table() {
    table_t* table = init_table();
    int res = 0;
    if (table == NULL) {
        goto end;
    }
    dns_entry_t *entry = create_dns_entry(TEST_DOMAIN, TEST_ADDRESS);
    if (entry == NULL) {
        goto end;
    }
    table_add(&entry->entry, table, &entry->key_data);

    if (entry->entry.ptr == NULL) {
        goto end;
    }
    if (table->count != 1) {
        goto end;
    }
    res = 1;
end:
    free_table(table);
    free_dns_entry(entry);
    return res;
}

static int test_remove_from_table() {
    table_t* table = init_table();
    int res = 0;
    if (table == NULL) {
        goto end;
    }
    dns_entry_t *entry = create_dns_entry(TEST_DOMAIN, TEST_ADDRESS);
    if (entry == NULL) {
        goto end;
    }
    table_add(&entry->entry, table, &entry->key_data);

    if (entry->entry.ptr == NULL) {
        goto end;
    }

    table_del(table, entry->entry.key);
    if (table->count != 0) {
        goto end;
    }
    res = 1;

end:
    free_table(table);
    free_dns_entry(entry);
    return res;
}

static int test_find_entry() {
    table_t* table = init_table();
    int res = 0;
    if (table == NULL) {
        goto end;
    }
    dns_entry_t *entry = create_dns_entry(TEST_DOMAIN, TEST_ADDRESS);
    if (entry == NULL) {
        goto end;
    }
    table_add(&entry->entry, table, &entry->key_data);

    if (entry->entry.ptr == NULL) {
        goto end;
    }
    table_entry_t *found = table_find(table, entry->entry.key);
    if (found == NULL) {
        goto end;
    }
    if (found->key != entry->entry.key) {
        goto end;
    }
    res = 1;

end:
    free_table(table);
    free_dns_entry(entry);
    return res;
}

static int test_destroy_table() {
    table_t* table = init_table();
    int res = 0;
    if (table == NULL) {
        goto end;
    }

    dns_entry_t *entry = create_dns_entry(TEST_DOMAIN, TEST_ADDRESS);
    if (entry == NULL) {
        goto end;
    }
    table_add(&entry->entry, table, &entry->key_data);
    res = 1;
end:
    free_dns_entry(entry);
    free_table(table);
    return res;
}

static int test_add_remove_find() {
    table_t* table = init_table();
    int res = 0;
    if (table == NULL) {
        goto end;
    }

    dns_entry_t *entry = create_dns_entry(TEST_DOMAIN, TEST_ADDRESS);
    if (entry == NULL) {
        goto end;
    }
    table_add(&entry->entry, table, &entry->key_data);
    table_del(table, entry->entry.key);
    table_entry_t *found = table_find(table, entry->entry.key);
    if (found != NULL) {
        goto end;
    }
    res = 1;

end:
    free_table(table);
    free_dns_entry(entry);
    return res;
}

static int test_add_already_exists() {
    table_t* table = init_table();
    int res = 0;
    if (table == NULL) {
        goto end;
    }

    dns_entry_t *entry = create_dns_entry(TEST_DOMAIN, TEST_ADDRESS);
    if (entry == NULL) {
        goto end;
    }
    table_add(&entry->entry, table, &entry->key_data);
    table_add(&entry->entry, table, &entry->key_data);
    if (table->count != 1 || entry->entry.ptr != NULL || entry->entry.key != 0) {
        goto end;
    }
    res = 1;
end:
    free_table(table);
    free_dns_entry(entry);
    return res;
}

static int test_find_entry_not_found() {
    table_t* table = init_table();
    int res = 0;
    if (table == NULL) {
        printf("Table is NULL\n");
        goto end;
    }
    dns_entry_t *entry = create_dns_entry(TEST_DOMAIN, TEST_ADDRESS);
    if (entry == NULL) {
        printf("Entry is NULL\n");
        goto end;
    }

    table_entry_t *te = table_find(table, entry->entry.key);
    if (te != NULL) {
        printf("Entry found\n");
        goto end;
    }

    table_add(&entry->entry, table, &entry->key_data);
    dns_entry_t *entry2 = create_dns_entry(TEST_DOMAIN2, TEST_ADDRESS);
    if (entry2 == NULL) {
        printf("Entry2 is NULL\n");
        goto end;
    }
    table_add(&entry2->entry, table, &entry2->key_data);
    table_del(table, entry2->entry.key);
    table_entry_t *te2 = table_find(table, entry2->entry.key);
    if (te2 != NULL) {
        printf("Entry2 found\n");
        goto end;
    }
    res = 1;
    
end:
    free_table(table);
    free_dns_entry(entry);
    free_dns_entry(entry2);
    return res;
}

static int test_table_entry()
{
    int res = 0;
    table_t *table = init_table();
    if (table == NULL) {
        goto end;
    }
    dns_entry_t *entry = create_dns_entry(TEST_DOMAIN, TEST_ADDRESS);
    if (entry == NULL) {
        goto end;
    }
    table_add(&entry->entry, table, &entry->key_data);
    table_entry_t *te = table_find(table, entry->entry.key);
    if (te == NULL) {
        goto end;
    }
    dns_entry_t *found = TABLE_ENTRY(te, dns_entry_t, entry);
    if (found == NULL) {
        goto end;
    }

    if (strcmp(found->key_data.data, entry->key_data.data) != 0) {
        goto end;
    }
    if (strcmp(found->address, entry->address) != 0) {
        goto end;
    }
    res = 1;

end:
    free_table(table);
    free_dns_entry(entry);
    return res;
}

static int test_collision()
{
    int res = 0;
    table_t *table = init_table();
    if (table == NULL) {
        goto end;
    }
    dns_entry_t *entry = create_dns_entry(TEST_DOMAIN, TEST_ADDRESS);
    if (entry == NULL) {
        goto end;
    }
    table_add(&entry->entry, table, &entry->key_data);
    dns_entry_t *entry2 = create_dns_entry(TEST_DOMAIN2, TEST_ADDRESS);
    if (entry2 == NULL) {
        goto end;
    }
    table_add(&entry2->entry, table, &entry2->key_data);
    if (entry->entry.ptr == NULL || entry2->entry.ptr == NULL) {
        goto end;
    }
    if (table->count != 2) {
        goto end;
    }
    res = 1;

end:
    free_table(table);
    free_dns_entry(entry);
    free_dns_entry(entry2);
    return res;
}

static int test_cache()
{
    if (TABLE_LENGTH != 2) {
        printf("This test is designed for a table length of 2\n");
        printf("Changed TABLE_LENGTH to 2 in table.h only for this test\n");
        return 0;
    }
    int res = 0;
    table_t *table = init_table();
    if (table == NULL) {
        goto end;
    }
    dns_entry_t *entry = create_dns_entry(TEST_DOMAIN, TEST_ADDRESS);
    if (entry == NULL) {
        goto end;
    }
    table_add(&entry->entry, table, &entry->key_data);
    int index = entry->entry.key % TABLE_LENGTH;
    int index2 = (entry->entry.key + 1) % TABLE_LENGTH;
    dns_entry_t *entry2 = create_dns_entry(TEST_DOMAIN2, TEST_ADDRESS);
    if (entry2 == NULL) {
        goto end;
    }
    table_add(&entry2->entry, table, &entry2->key_data);
    dns_entry_t *entry_found = TABLE_ENTRY(table_find(table, entry2->entry.key), dns_entry_t, entry);
    if (table->entries[index].key != entry_found->entry.key) {
        goto end;
    }
    if (table->entries[index].ptr != &entry_found->entry) {
        goto end;
    }
    if (table->entries[index2].key != entry->entry.key) {
        goto end;
    }
    if (table->entries[index2].ptr != &entry->entry) {
        goto end;
    }
    res = 1;

end:
    free_table(table);
    free_dns_entry(entry);
    free_dns_entry(entry2);
    return res;
}

int main() {
    int tests_passed = 0;
    int num_tests = 11;
    tests_passed += test_init_table();
    tests_passed += test_add_to_table();
    tests_passed += test_destroy_table();
    tests_passed += test_remove_from_table();
    tests_passed += test_find_entry();
    tests_passed += test_add_remove_find();
    tests_passed += test_add_already_exists();
    tests_passed += test_find_entry_not_found();
    tests_passed += test_table_entry();
    tests_passed += test_collision();
    tests_passed += test_cache();
    printf("Tests passed: %d/%d\n", tests_passed, num_tests);
    return 0;
}
