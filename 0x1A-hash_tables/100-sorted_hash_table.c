#include "hash_tables.h"

/**
 * shash_table_create - creates a shash table with a given size
 *
 * @size: size of the shash table
 * Return: the created shash table, or NULL if function fails
 */
shash_table_t *shash_table_create(unsigned long int size)
{
    shash_table_t *ht = malloc(sizeof(shash_table_t));
    if (!ht)
        return NULL;

    ht->size = size;
    ht->array = calloc(size, sizeof(shash_node_t *));
    if (!ht->array)
    {
        free(ht);
        return NULL;
    }

    ht->shead = NULL;
    ht->stail = NULL;

    return ht;
}

/**
 * hash_djb2 - Hash function implementing the djb2 algorithm.
 * @str: The string to hash.
 *
 * Description:
 *   This function generates a hash value for a given string using the djb2
 *   algorithm created by Dan Bernstein. The algorithm works by initializing
 *   the hash to a magic number (5381) and then iteratively processing each
 *   character in the string. For each character, the hash is shifted left by
 *   5 bits and added to itself (equivalent to multiplying by 33) and then the
 *   character's ASCII value is added. This approach results in a fast and
 *   simple hashing algorithm with good distribution properties.
 *
 * Return: The generated hash value.
 */
unsigned long int hash_djb2(const unsigned char *str)
{
    unsigned long int hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
    return hash_djb2(key) % size;
}

/**
 * shash_table_set - adds a hash (key, value) to a given shash table
 *
 * @ht: pointer to the shash table
 * @key: key of the shash
 * @value: value to store
 * Return: 1 if successes, 0 if fails
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
    shash_node_t *new_node, *tmp;
    unsigned long int index;
    char *value_copy, *key_copy;

    if (!ht || !key || !*key || !value)
        return 0;

    value_copy = strdup(value);
    if (!value_copy)
        return 0;

    key_copy = strdup(key);
    if (!key_copy)
    {
        free(value_copy);
        return 0;
    }

    index = key_index((const unsigned char *)key, ht->size);
    tmp = ht->array[index];
    while (tmp)
    {
        if (strcmp(tmp->key, key) == 0)
        {
            free(tmp->value);
            tmp->value = value_copy;
            free(key_copy);
            return 1;
        }
        tmp = tmp->next;
    }

    new_node = malloc(sizeof(shash_node_t));
    if (!new_node)
    {
        free(value_copy);
        free(key_copy);
        return 0;
    }

    new_node->key = key_copy;
    new_node->value = value_copy;
    new_node->next = ht->array[index];
    ht->array[index] = new_node;

    // Insert into sorted linked list
    if (!ht->shead || strcmp(key, ht->shead->key) < 0)
    {
        new_node->snext = ht->shead;
        new_node->sprev = NULL;
        if (ht->shead)
            ht->shead->sprev = new_node;
        ht->shead = new_node;
        if (!ht->stail)
            ht->stail = new_node;
    }
    else
    {
        tmp = ht->shead;
        while (tmp->snext && strcmp(key, tmp->snext->key) > 0)
            tmp = tmp->snext;

        new_node->snext = tmp->snext;
        new_node->sprev = tmp;
        if (!tmp->snext)
            ht->stail = new_node;
        else
            tmp->snext->sprev = new_node;
        tmp->snext = new_node;
    }

    return 1;
}

/**
 * shash_table_get - retrieves a value associated with a key
 *
 * @ht: pointer to the shash table
 * @key: key of the shash
 * Return: value of the shash.
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
    shash_node_t *node;
    unsigned long int index;

    if (!ht || !key || !*key)
        return NULL;

    index = key_index((const unsigned char *)key, ht->size);
    node = ht->array[index];
    while (node)
    {
        if (strcmp(node->key, key) == 0)
            return node->value;
        node = node->next;
    }
    return NULL;
}

/**
 * shash_table_print - prints the keys and values of the shash table
 *
 * @ht: pointer to the shash table
 * Return: no return
 */
void shash_table_print(const shash_table_t *ht)
{
    shash_node_t *node;
    int comma = 0;

    if (!ht)
        return;

    printf("{");
    node = ht->shead;
    while (node)
    {
        if (comma)
            printf(", ");
        printf("'%s': '%s'", node->key, node->value);
        comma = 1;
        node = node->snext;
    }
    printf("}\n");
}

/**
 * shash_table_print_rev - prints the keys and values of the shash table
 * in reverse
 *
 * @ht: pointer to the shash table
 * Return: no return
 */
void shash_table_print_rev(const shash_table_t *ht)
{
    shash_node_t *node;
    int comma = 0;

    if (!ht)
        return;

    printf("{");
    node = ht->stail;
    while (node)
    {
        if (comma)
            printf(", ");
        printf("'%s': '%s'", node->key, node->value);
        comma = 1;
        node = node->sprev;
    }
    printf("}\n");
}

/**
 * shash_table_delete - deletes a shash table
 *
 * @ht: pointer to the shash table
 * Return: no return
 */
void shash_table_delete(shash_table_t *ht)
{
    shash_node_t *node, *tmp;

    if (!ht)
        return;

    node = ht->shead;
    while (node)
    {
        tmp = node->snext;
        free(node->key);
        free(node->value);
        free(node);
        node = tmp;
    }

    free(ht->array);
    free(ht);
}


