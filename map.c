/**
    @file map.c
    @author Ramon Mayo (rmmayo@ncsu.edu) & CSC 230
    Hash table implementation of a map.
*/

#include "map.h"
#include <stdlib.h>
#include "vtype.h"

/** Node containing a key / value pair. */
typedef struct NodeStruct
{
    /** Pointer to the key part of the key / value pair. */
    VType *key;

    /** Pointer to the value part of the key / value pair. */
    VType *val;

    /** Pointer to the next node at the same element of this table. */
    struct NodeStruct *next;
} Node;

/** Representation of a hash table implementation of a map. */
struct MapStruct
{
    /** Table of key / value pairs. */
    Node **table;

    /** Current length of the table. */
    int tlen;

    /** Current size of the map (number of different keys). */
    int size;
};

/**
 * Frees a Node struct by first freeing its VType val and key, then the node iteself.
 *
 * @param n the node to be freed
 */
static void freeNode(Node *n)
{
    n->key->destroy(n->key);
    n->val->destroy(n->val);
    free(n);
}

Map *makeMap(int len)
{
    Map *m = (Map *)malloc(sizeof(Map));
    m->size = 0;

    // Complete the implementation.
    // ...
    m->table = (Node **)malloc(len * sizeof(Node *));
    m->tlen = len;

    for (int i = 0; i < len; i++) {
        m->table[i] = NULL;
    }

    return m;
}

int mapSize(Map *m)
{
    return m->size;
}

VType *mapGet(Map *m, VType *key)
{

    int index = key->hash(key) % m->tlen;
    if ((m->table[index]) == NULL) {

        return NULL;
    }

    else
    {
        Node **scan = &(m->table[index]);

        while (*scan) {
            if ((*scan)->key == NULL) {
                printf("here\n");
            }
            if ((*scan)->key->equals((*scan)->key, key)) {
                return (*scan)->val;
            }

            scan = &((*scan)->next);
        }

        return NULL;
    }
}
/**
 * Frees a chain of nodes.
 *
 * @param n The head of the chain of nodes
 * @param size The size of the overall hashmap, to be decremented as the nodes are freed.
 */
static void freeChain(Node *n, int *size)
{

    while (n) {
        (*size)--;
        Node *next = n->next;
        n->key->destroy(n->key);
        n->val->destroy(n->val);

        free(n);
        n = next;
    }
}

void freeMap(Map *m)
{
    // Complete the implementation
    // ...
    // printf("The list has %d entries in it.\n", m->size);
    int tableSize = m->tlen;
    for (int i = 0; i < tableSize; i++) {

        freeChain(m->table[i], &(m->size));
    }

    // printf(" remaining in the list is %d\n", (m->size));
    free(m->table);
    free(m);
}

void mapSet(Map *m, VType *key, VType *val)
{
    int index = key->hash(key) % m->tlen;

    bool added = false;

    if (m->table[index] == NULL) {
        Node *new = (Node *)malloc(sizeof(Node));
        new->val = val;
        new->key = key;
        new->next = NULL;
        m->table[index] = new;
        m->size += 1;
    }
    else {

        Node *cur = m->table[index];

        Node **scan = &(cur);
        while (*scan) {

            if ((*scan)->key->equals((*scan)->key, key)) {
                key->destroy(key);
                (*scan)->val->destroy((*scan)->val);
                (*scan)->val = val;
                added = true;
                break;
            }

            scan = &((*scan)->next);
        }

        if (!added) {
            Node *new = (Node *)malloc(sizeof(Node));
            new->val = val;
            new->key = key;
            new->next = NULL;
            *scan = new;
            m->size += 1;
        }
    }
}

bool mapRemove(Map *m, VType *key)
{
    int index = key->hash(key) % m->tlen;

    if (!m->table[index]) {
        return false;
    }

    else if (key->equals(key, m->table[index]->key)) {
        Node *rem = m->table[index];
        m->table[index] = m->table[index]->next;
        freeNode(rem);
        m->size -= 1;
        return true;
    }

    else {
        Node *cur = m->table[index];
        Node *prev = m->table[index];

        while (cur) {
            if (key->equals(key, cur->key)) {
                prev->next = cur->next;
                freeNode(cur);
                m->size -= 1;
                return true;
            }

            prev = cur;
            cur = cur->next;
        }

        return false;
    }
}
