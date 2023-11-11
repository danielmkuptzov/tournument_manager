//
// Created by danie on 11/11/2023.
//

#ifndef QUEENS_GAMBIT_THE_FIX_MAP_SPACE_MANAGER_H
#define QUEENS_GAMBIT_THE_FIX_MAP_SPACE_MANAGER_H

/**
 * map  adt
 *
 * Implements a sorted list by a user
 *
 *
 * The following functions are available:
 *   mapCreate            - Creates a new and empty map
 *   mapDestroy           - Deletes an existing and frees all resources
 *   mapCopy              - Copies an existing map
 *   mapGetSize           – returns the size of the dictionary
 *   mapContains          – serches for an element in the dictionary
 *   mapPut               – changes a value in the dictionary or creating new if the key doesn't exist
 *   mapGet               - given a key, returns a value
 *   mapRemove            – remove a given key
 *   mapGetFirst          – restore the iterator to the first entry in the dictionary and returnes the value of the
 *                          first key
 *   mapGetNext           – ascending the iterator and returning a copy of the value
 *   mapClear             – remove all data from the dictionary
 */


typedef void* Key;

typedef void* Data;

typedef void(*KeyCompare)(Key,Key);

typedef struct Map_t* Map;
/*
 *   mapCreate            - Creates a new and empty map
 *   @param- KeyCompare
 *   @return
 *    empty map
 *    NULL otherwise
 */
Map mapCreate(KeyCompare compare);

/*
 *   mapDestroy           - Deletes an existing and frees all resources
 *   @param- map
 */
void mapDestroy(Map map);

/*
 *   mapCopy              - Copies an existing map
 *   @param- map
 *   @return-
 *            map if the copy process was sucsessful
 *            NULL otherwise
 */
Map mapCopy(Map map);

/*
 *   mapGetSize           – returns the size of the dictionary
 *   @param-  map
 *   @return-
 *            -1 if the param was NULL
 *            positive number or 0 otherwise
 */
int mapGetSize(Map map);

/*
 *   mapContains          – serches for an element in the dictionary
 *   @param- Key  -the element we are serching
 *           Map  -the place where we want to serch
 *   @return-TRUE if the key is in the map
 *           FALSE otherwise
 */
bool mapContains(Map map, Key key);

/*
 *   mapPut               – changes a value in the dictionary or creating new if the key doesn't exist
 *   @param-    Map
 *              Key  -the key we want to change or add
 *              Data -the data we want to enter
 *   @return-   MAP_SUCSESS        -the operation was a sucsess
 *              MAP_NULL_ARGUMENT  -a NULL argument was passed
 *              MAP_ERROR          -otherwise
 *   mapGet               - given a key, returns a value
 *   mapRemove            – remove a given key
 *   mapGetFirst          – restore the iterator to the first entry in the dictionary and returnes the value of the
 *                          first key
 *   mapGetNext           – ascending the iterator and returning a copy of the value
 *   mapClear             – remove all data from the dictionary
 */

#endif //QUEENS_GAMBIT_THE_FIX_MAP_SPACE_MANAGER_H