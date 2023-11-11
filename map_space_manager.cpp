//
// Created by danie on 11/11/2023.
//

#include <stdlib.h>

#include "map_space_manager.h"
typedef struct Node_t {
    KeyElement key;
    DataElement data;
    Node_t* next;
}* Node;

/**
 * createnode -   allocates a node with data
 * @param keyElement
 * @param dataElement
 * @param copyKeyElement
 * @param copyDataElement
 * @param freeKeyElement
 * @return
 *   NULL if any problem accured
 *   Node otherwise
 */
Node createnode(copyDataElements copyDataElement, copyKeyElements copyKeyElement,freeKeyElements freeKeyElement,
                KeyElement keyElement, DataElement dataElement)
{
    if(!copyDataElement||!copyKeyElement||!keyElement||!dataElement
       ||!freeKeyElement)
    {
        return NULL;
    }
    Node nodenew = static_cast<Node>(malloc(sizeof(struct Node_t)));
    if(!nodenew)
    {
        return NULL;
    }
    nodenew->key=copyKeyElement(keyElement);
    if(!nodenew->key)
    {
        free(nodenew);
    }
    nodenew->data=copyDataElement(dataElement);
    if(!nodenew->data)
    {
        freeKeyElement(nodenew->key);
        free(nodenew);
    }
    nodenew->next=NULL;
    return nodenew;
}

/**
* mapDestroy: Deallocates an existing map. Clears all elements by using the
* stored free functions.
*
* @param node - Target node to be deallocated. If map is NULL nothing will be
* 		done
* @param freeKeyElement
* @param freeDataElement
 */
void destroynode(Node node,freeKeyElements freeKeyElements,freeDataElements freeDataElements)
{
    if(!node||!freeKeyElements||!freeDataElements)
    {
        return;
    }
    if(node->next)
    {
        destroynode(node->next,freeKeyElements,freeDataElements);
    }
    freeDataElements(node->data);
    freeKeyElements(node->key);
    free(node);
}

/**
* copynode: Creates a copy of target node.
*
* @param node - Target node.
* @param copyKeyElement
* @param copyDataElement
* @param freeKeyElement
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A Node containing the same elements as map otherwise.
*/
Node copynode(Node node,copyKeyElements copyKeyElement, copyDataElements copyDataElement,
              freeKeyElements freeKeyElement)
{
    if(!node||!copyKeyElement||!copyDataElement||!freeKeyElement)
    {
        return NULL;
    }
    Node copy= createnode(copyDataElement, copyKeyElement,freeKeyElement,node->key, node->data);
    if(!copy)
    {
        return NULL;
    }
    return copy;
}

struct map_t{
    Node head;
    copyDataElements copyDataFunc;
    copyKeyElements copykeyfunc;
    freeDataElements freedata;
    freeKeyElements fereekey;
    compareKeyElements comparisonfunc;
};

Map mapCreate(copyDataElements copyDataElement,
              copyKeyElements copyKeyElement,
              freeDataElements freeDataElement,
              freeKeyElements freeKeyElement,
              compareKeyElements compareKeyElements)
{
    if(!copyDataElement||!copyKeyElement||!freeDataElement||
       !freeKeyElement||!compareKeyElements)
    {
        return NULL;
    }
    Map mapnew = static_cast<Map>(malloc(sizeof(struct map_t)));
    if(!mapnew)
    {
        return NULL;
    }
    mapnew->comparisonfunc=compareKeyElements;
    mapnew->copyDataFunc=copyDataElement;
    mapnew->copykeyfunc=copyKeyElement;
    mapnew->fereekey=freeKeyElement;
    mapnew->freedata=freeDataElement;
    mapnew->head=NULL;
    return mapnew;
}


void mapDestroy(Map map)
{
    if(!map)
    {
        return;
    }
    destroynode(map->head,map->fereekey,map->freedata);
    free(map);
}

/**
* mapCopy: Creates a copy of target map.
* Iterator values for both maps is undefined after this operation.
*
* @param map - Target map.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A Map containing the same elements as map otherwise.
*/
Map mapCopy(Map map)
{}

/**
* mapGetSize: Returns the number of elements in a map
* @param map - The map which size is requested
* @return
* 	-1 if a NULL pointer was sent.
* 	Otherwise the number of elements in the map.
*/
int mapGetSize(Map map){}

/**
* mapContains: Checks if a key element exists in the map. The key element will be
* considered in the map if one of the key elements in the map it determined equal
* using the comparison function used to initialize the map.
*
* @param map - The map to search in
* @param element - The element to look for. Will be compared using the
* 		comparison function.
* @return
* 	false - if one or more of the inputs is null, or if the key element was not found.
* 	true - if the key element was found in the map.
*/
bool mapContains(Map map, KeyElement element){}

/**
*	mapPut: Gives a specified key a specific value.
*  Iterator's value is undefined after this operation.
*
* @param map - The map for which to reassign the data element
* @param keyElement - The key element which need to be reassigned
* @param dataElement - The new data element to associate with the given key.
*      A copy of the element will be inserted as supplied by the copying function
*      which is given at initialization and old data memory would be
*      deleted using the free function given at initialization.
* @return
* 	MAP_NULL_ARGUMENT if a NULL was sent as map
* 	MAP_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
* 	an element failed)
* 	MAP_SUCCESS the paired elements had been inserted successfully
*/
MapResult mapPut(Map map, KeyElement keyElement, DataElement dataElement){}

/**
*	mapGet: Returns the data associated with a specific key in the map.
*			Iterator status unchanged
*
* @param map - The map for which to get the data element from.
* @param keyElement - The key element which need to be found and whos data
we want to get.
* @return
*  NULL if a NULL pointer was sent or if the map does not contain the requested key.
* 	The data element associated with the key otherwise.
*/
DataElement mapGet(Map map, KeyElement keyElement){}

/**
* 	mapRemove: Removes a pair of key and data elements from the map. The elements
*  are found using the comparison function given at initialization. Once found,
*  the elements are removed and deallocated using the free functions
*  supplied at initialization.
*  Iterator's value is undefined after this operation.
*
* @param map -
* 	The map to remove the elements from.
* @param keyElement
* 	The key element to find and remove from the map. The element will be freed using the
* 	free function given at initialization. The data element associated with this key
*  will also be freed using the free function given at initialization.
* @return
* 	MAP_NULL_ARGUMENT if a NULL was sent to the function
*  MAP_ITEM_DOES_NOT_EXIST if an equal key item does not already exists in the map
* 	MAP_SUCCESS the paired elements had been removed successfully
*/
MapResult mapRemove(Map map, KeyElement keyElement){}

/**
*	mapGetFirst: Sets the internal iterator (also called current key element) to
*	the first key element in the map. There doesn't need to be an internal order
*  of the keys so the "first" key element is any key element.
*	Use this to start iterating over the map.
*	To continue iteration use mapGetNext
*
* @param map - The map for which to set the iterator and return the first
* 		key element.
* @return
* 	NULL if a NULL pointer was sent or the map is empty.
* 	The first key element of the map otherwise
*/
KeyElement mapGetFirst(Map map){}

/**
*	mapGetNext: Advances the map iterator to the next key element and returns it.
*	The next key element is any key element not previously returned by the iterator.
* @param map - The map for which to advance the iterator
* @return
* 	NULL if reached the end of the map, or the iterator is at an invalid state
* 	or a NULL sent as argument
* 	The next key element on the map in case of success
*/
KeyElement mapGetNext(Map map){}


/**
* mapClear: Removes all key and data elements from target map.
* The elements are deallocated using the stored free functions.
* @param map
* 	Target map to remove all element from.
* @return
* 	MAP_NULL_ARGUMENT - if a NULL pointer was sent.
* 	MAP_SUCCESS - Otherwise.
*/
MapResult mapClear(Map map){}
