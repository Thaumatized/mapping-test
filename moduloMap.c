#include "common.h"
#include "moduloMap.h"

#include <stdbool.h>
#include <stdlib.h> 

#include <stdio.h>

static Item *items = NULL;
static int itemsLength = 0;

void moduloMapInit(int length) {
    items = malloc(length * sizeof(Item));
    itemsLength = length;

    for(int i = 0; i < itemsLength; i++)
    {
        Item item = EMPTY_ITEM;
        items[i] = item;
    }
}

void moduloMapFree() {
    for(int i = 0; i < itemsLength; i++) {
    }
    free(items);
}

int getIndex(int id) {
    return id % itemsLength;
}

void makeArrayBigger() {
    int oldItemsLength = itemsLength;

    printf("RESIZE FROM %i ", itemsLength);
    itemsLength *= 2;
    printf("TO %i\n", itemsLength);
    Item *oldItems = items;
    items = malloc(itemsLength*sizeof(Item));

    for(int i = 0; i < itemsLength; i++)
    {
        Item item = EMPTY_ITEM;
        items[i] = item;
    }

    for(int i = 0; i < oldItemsLength; i++)
    {
        if(oldItems[i].id != DELETED_ITEM_ID && oldItems[i].id != EMPTY_ITEM_ID)
        {
            moduloMapInsert(oldItems[i]);
        }
    }
    
    free(oldItems);
}

void moduloMapInsert(Item item) {
    int itemIndex = getIndex(item.id);
    int index = itemIndex;
    bool found = false;
    do
    {
        if(items[index].id == EMPTY_ITEM_ID || items[index].id == DELETED_ITEM_ID)
        {
            found = true;
        }
        else
        {
            index = (index + 1) % itemsLength;
        }
    } while (!found && index != itemIndex);
    
    if(found)
    {
        items[index] = item;
    }
    else
    {
        makeArrayBigger();
        moduloMapInsert(item);
    }
}

void moduloMapDelete(int id) {
    int itemIndex = getIndex(id);
    int index = itemIndex;
    bool found = false;
    do
    {
        if(items[index].id == EMPTY_ITEM_ID)
        {
            found = true;
        }
        else if(items[index].id == id)
        {
            break; 
        }
        else
        {
            index = (index + 1) % itemsLength;
        }
    } while (!found && index != itemIndex);

    if(found)
    {
        Item item = EMPTY_ITEM;
        item.id = DELETED_ITEM_ID;
        items[id] = item;
    }
}

Item moduloMapGet(int id) {
    int itemIndex = getIndex(id);
    int index = itemIndex;
    bool found = false;
    do
    {
        if(items[index].id == EMPTY_ITEM_ID)
        {
            break; 
        }
        else if(items[index].id == id)
        {
            found = true;
            break; 
        }
        else
        {
            index = (index + 1) % itemsLength;
        }
    } while (!found && index != itemIndex);

    if(found)
    {
        return items[index];
    }
    else
    {
        Item item = EMPTY_ITEM;
        return item;
    }
}