//
// Created by danie on 11/11/2023.
//

#include <stdlib.h>

typedef enum NodeResult_t {
    NODE_SUCCESS,
    NODE_OUT_OF_MEMORY,
    NODE_NULL_ARGUMENT,
    NODE_ITEM_ALREADY_EXISTS,
    NODE_ITEM_DOES_NOT_EXIST
} NodeResult;

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

/**
*	nodegetkey: Gives a given node's key.
*
* @param node - The node we want the key from.
* @return
* 	NULL if null argument was passed
* 	key otherwise
*/
KeyElement nodegetkey(Node node)
{
    if(!node)
    {
        return NULL;
    }
    return node->key;
}

/**
*	nodegetdata: Gives a given node's data.
*
* @param node - The node we want the key from.
* @return
* 	NULL if null argument was passed
* 	data otherwise
*/
DataElement nodegetdata(Node node)
{
    if(!node)
    {
        return NULL;
    }
    return node->data;
}

/**
*	nodegetnext: Gives a given node's next element.
*
* @param node - The node we want the key from.
* @return
* 	NULL if null argument was passed
* 	node otherwise
*/
Node nodegetnext(Node node)
{
    if(!node)
    {
        return NULL;
    }
    return node->next;
}

/**
*	nodechangenext: Changes a given node's next node.
* @param node - The node for which to reassign the next element
*      A copy of the element will be inserted as supplied by the copying function
*      which is given at initialization and old data memory would be
*      deleted using the free function given at initialization.
* @param nodenext -the node we want to be the next element.
* @param copyDataElement
* @param copyKeyElement
* @param freeDataElement
* @param freeKeyElement
* @return
* 	NODE_NULL_ARGUMENT if a NULL was sent as node
* 	NODE_OUT_OF_MEMORY if the action was a failure
* 	NODE_SUCCESS the paired elements had been inserted successfully
*/
NodeResult nodechangenext(Node node, Node nodenext,copyKeyElements copyKeyElement, copyDataElements copyDataElement,
                          freeKeyElements freeKeyElement,freeDataElements freeDataElement)
{
    if(!node||!nodenext||!copyKeyElement||!copyDataElement||!freeKeyElement||
    !freeDataElement)
    {
        return NODE_NULL_ARGUMENT;
    }
    Node todestroy= nodegetnext(node);
    node->next= copynode(nodenext,copyKeyElement,copyDataElement,freeKeyElement);
    if(!node->next)
    {
        node->next=todestroy;
        return NODE_OUT_OF_MEMORY;
    }
    node->next->next=todestroy->next;
    todestroy->next=NULL;
    destroynode(todestroy,freeKeyElement,freeDataElement);
    return NODE_SUCCESS;
}

/**
*	nodechangedata: Changes a given node's data.
* @param node - The node for which to reassign the data element
*      A copy of the element will be inserted as supplied by the copying function
*      which is given at initialization and old data memory would be
*      deleted using the free function given at initialization.
* @param data -the data we want to be the new data element.
* @param copyDataElement
* @param freeDataElement
* @return
* 	NODE_NULL_ARGUMENT if a NULL was sent as node
* 	NODE_OUT_OF_MEMORY if the action was a failure
* 	NODE_SUCCESS the paired elements had been inserted successfully
*/
NodeResult nodechangedata(Node node, DataElement data, copyDataElements copyDataElement,
                          freeDataElements freeDataElement)
{
    if(!node||!data||!copyDataElement||!freeDataElement)
    {
        return NODE_NULL_ARGUMENT;
    }
    DataElement tmp=node->data;
    node->data=copyDataElement(data);
    if(!node->data)
    {
        node->data=tmp;
        return NODE_OUT_OF_MEMORY;
    }
    freeDataElement(tmp);
    return NODE_SUCCESS;
}

struct map_t{
    int size;
    Node head;
    Node iterator;
    copyDataElements copyDataFunc;
    copyKeyElements copykeyfunc;
    freeDataElements freedata;
    freeKeyElements fereekey;
    compareKeyElements comparisonfunc;
};

Map mapCreate(copyDataElements copyDataElement, copyKeyElements copyKeyElement, freeDataElements freeDataElement,
              freeKeyElements freeKeyElement, compareKeyElements compareKeyElements)
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
    mapnew->size=0;
    mapnew->iterator=NULL;
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

Map mapCopy(Map map)
{
    if(!map)
    {
        return NULL;
    }
    Map copy= mapCreate(map->copyDataFunc,map->copykeyfunc,map->freedata,
                        map->fereekey,map->comparisonfunc);
    if(!copy)
    {
        return NULL;
    }
    Node original=map->head;
    Node ncopy= copynode(original,map->copykeyfunc,map->copyDataFunc,
                         map->fereekey);
    copy->head= ncopy;
    while (!original)
    {
        ncopy->next= copynode(original->next,map->copykeyfunc,map->copyDataFunc,
                              map->fereekey);
        if(!nodegetnext(ncopy))
        {
            mapDestroy(copy);
            return NULL;
        }
        original=original->next;
        ncopy= nodegetnext(ncopy);
    }
    return copy;
}

int mapGetSize(Map map)
{
    if(!map)
    {
        return -1;
    }
    return map->size;
}

bool mapContains(Map map, KeyElement element)
{
    if(!map||!element)
    {
        return false;
    }
    Node iteration=map->head;
    while(!iteration)
    {
        if(map->comparisonfunc(nodegetkey(iteration),element)==0)
        {
            map->iterator=iteration;
            return true;
        }
        iteration= nodegetnext(iteration);
    }
    return false;
}

MapResult mapPut(Map map, KeyElement keyElement, DataElement dataElement)
{
    if(!map||!keyElement||!dataElement)
    {
        return MAP_NULL_ARGUMENT;
    }
    if(mapContains(map,keyElement))
    {
        if(nodechangedata(map->iterator,dataElement,
                          map->copyDataFunc,map->freedata)!=NODE_SUCCESS)
        {
            return MAP_OUT_OF_MEMORY;
        }
        return MAP_SUCCESS;
    }
    Node tmp= createnode(map->copyDataFunc,map->copykeyfunc,
                         map->fereekey,keyElement,dataElement);
    if(!tmp)
    {
        return MAP_OUT_OF_MEMORY;
    }
    if(nodechangenext(map->iterator,tmp,map->copykeyfunc,
                      map->copyDataFunc,map->fereekey,map->freedata)!=NODE_SUCCESS)
    {
        return MAP_OUT_OF_MEMORY;
    }
    map->size++;
    return MAP_SUCCESS;
}

DataElement mapGet(Map map, KeyElement keyElement)
{
    if(!map||!keyElement)
    {
        return NULL;
    }
    if(!mapContains(map,keyElement))
    {
        return NULL;
    }
    return nodegetdata(map->iterator);
}

MapResult mapRemove(Map map, KeyElement keyElement)
{
    if(!map||!keyElement)
    {
        return MAP_NULL_ARGUMENT;
    }
    if(!mapContains(map,keyElement))
    {
        return MAP_ITEM_DOES_NOT_EXIST;
    }
    Node tail=map->head;
    while(tail->next!=map->iterator)
    {
        tail=tail->next;
    }
    tail->next=map->iterator->next;
    map->iterator->next=NULL;
    destroynode(map->iterator,map->fereekey,map->freedata);
    return MAP_SUCCESS;
}

KeyElement mapGetFirst(Map map)
{
    if(!map)
    {
        return NULL;
    }
    map->iterator=map->head;
    return nodegetkey(map->iterator);
}

KeyElement mapGetNext(Map map)
{
    if(!map)
    {
        return NULL;
    }
    map->iterator= nodegetnext(map->iterator);
}

MapResult mapClear(Map map)
{
    if(!map)
    {
        return MAP_NULL_ARGUMENT;
    }
    map->iterator=NULL;
    destroynode(map->head,map->fereekey,map->freedata);
    return MAP_SUCCESS;
}
