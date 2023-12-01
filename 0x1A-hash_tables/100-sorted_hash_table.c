#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct shash_node {
    char *key;
    char *value;
    struct shash_node *next;
    struct shash_node *sprev;
    struct shash_node *snext;
} shash_node_t;

typedef struct shash_table {
    unsigned long int size;
    shash_node_t **array;
    shash_node_t *shead;
    shash_node_t *stail;
} shash_table_t;

shash_table_t *shash_table_create(unsigned long int size) {
    shash_table_t *ht = malloc(sizeof(shash_table_t));
    if (ht == NULL) {
        return NULL;
    }

    ht->size = size;
    ht->array = malloc(sizeof(shash_node_t *) * size);
    if (ht->array == NULL) {
        free(ht);
        return NULL;
    }

    memset(ht->array, 0, sizeof(shash_node_t *) * size);
    ht->shead = NULL;
    ht->stail = NULL;

    return ht;
}

unsigned long int hash(const char *key, unsigned long int size) {
    unsigned long int hashval = 0;
    unsigned long int i = 0;

    while (hashval < ULONG_MAX && i < strlen(key)) {
        hashval = hashval << 8;
        hashval += key[i];
        i++;
    }

    return hashval % size;
}

int shash_table_set(shash_table_t *ht, const char *key, const char *value) {
    if (ht == NULL || key == NULL || value == NULL) {
        return 0;
    }

    unsigned long int index = hash(key, ht->size);

    shash_node_t *new_node = malloc(sizeof(shash_node_t));
    if (new_node == NULL) {
        return 0;
    }

    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = NULL;

    if (ht->array[index] == NULL) {
        ht->array[index] = new_node;
    } else {
        shash_node_t *current = ht->array[index];
        while (current->next != NULL) {
            if (strcmp(current->key, key) == 0) {
                free(current->value);
                current->value = strdup(value);
                free(new_node->key);
                free(new_node->value);
                free(new_node);
                return 1;
            }
            current = current->next;
        }
        current->next = new_node;
    }

    if (ht->shead == NULL) {
        ht->shead = new_node;
    } else {
        shash_node_t *current = ht->shead;
        while (current->snext != NULL) {
            current = current->snext;
        }
        current->snext = new_node;
        new_node->sprev = current;
        ht->stail = new_node;
    }

    return 1;
}

char *shash_table_get(shash_table_t *ht, const char *key) {
    if (ht == NULL || key == NULL) {
        return NULL;
    }

    unsigned long int index = hash(key, ht->size);

    shash_node_t *current = ht->array[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return NULL;
}

void shash_table_print(shash_table_t *ht) {
    if (ht == NULL) {
        return;
    }

    shash_node_t *current = ht->shead;
    while (current != NULL) {
        printf("%s:%s\n", current->key, current->value);
        current = current->snext;
    }
}

void shash_table_print_rev(shash_table_t *ht) {
    if (ht == NULL) {
        return;
    }

    shash_node_t *current = ht->stail;
    while (current != NULL) {
        printf("%s:%s\n", current->key, current->value);
        current = current->sprev;
    }
}

void shash_table_delete(shash_table_t *ht) {
    if (ht == NULL) {
        return;
    }

    for (unsigned long int i = 0; i < ht->size; i++) {
        shash_node_t *current = ht->array[i];
        while (current != NULL) {
            shash_node_t *temp = current;
            current = current->next;
            free(temp->key);
            free(temp->value);
            free(tempApologies for the incomplete code in my previous response. Here's the complete code with the remaining part:

```c
            if (current->sprev != NULL) {
                current->sprev->snext = current->snext;
            } else {
                ht->shead = current->snext;
            }

            if (current->snext != NULL) {
                current->snext->sprev = current->sprev;
            } else {
                ht->stail = current->sprev;
            }

            free(current->key);
            free(current->value);
            free(current);
        }
    }

    free(ht->array);
    free(ht);
}

int main() {
    shash_table_t *ht = shash_table_create(10);

    shash_table_set(ht, "key1", "value1");
    shash_table_set(ht, "key2", "value2");
    shash_table_set(ht, "key3", "value3");

    printf("Get 'key1': %s\n", shash_table_get(ht, "key1"));
    printf("Get 'key2': %s\n", shash_table_get(ht, "key2"));
    printf("Get 'key3': %s\n", shash_table_get(ht, "key3"));

    printf("Printing hash table:\n");
    shash_table_print(ht);

    printf("Printing hash table in reverse:\n");
    shash_table_print_rev(ht);

    shash_table_delete(ht);

    return 0;
}
