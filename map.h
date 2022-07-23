/**
    @file map.h
    @author Ramon Mayo (rmmayo@ncsu.edu) & CSC 230
    Header for the map component, a hash map.
*/

#ifndef MAP_H
#define MAP_H

#include "vtype.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/** Incomplete type for the Map representation. */
typedef struct MapStruct Map;

/** Make an empty map.
    @param len Initial length of the hash table.
    @return pointer to a new map.
*/
Map *makeMap(int len);

/** Get the size of the given map.
    @param m Pointer to the map.
    @return Number of key/value pairs in the map. */
int mapSize(Map *m);

/** Return the value associated with the given key. The returned VType
    is still owned by the map.
    @param m Map to query.
    @param k Key to look for in the map.
    @return Value associated with the given key, or NULL if the key
    isn't in the map.
*/
VType *mapGet(Map *m, VType *key);

/** Free all the memory used to store a map, including all the
    memory in its key/value pairs.
    @param m The map to free.
*/
void freeMap(Map *m);

/**
 * Either adds a new entry to the given Hash Map, or replaces the value of an entry with a matching key.
 * This function is responsible for destroying keys and values as needed, the caller should not destroy the parameter key or value.
 * @param m a hash map to modify.
 * @param key a key to search for or add to the map.
 * @param val a value to add to the map or is used to replace an already present key.
 */
void mapSet(Map *m, VType *key, VType *val);

/**
 * Removes the map entry with a matching key.
 * The caller is responsible for destroying the key parameter.
 * @param m the map with the needed key.
 * @param key the key of the value to be removed.
 * @return true if the entry is removed.
 * @return false if the entry is not removed, because a matching key was not founds.
 */
bool mapRemove(Map *m, VType *key);

#endif
