#include "common.h"
#include "hashMap.h"

#include <stdbool.h>
#include <stdlib.h> 
#include <string.h> 

#include <stdio.h>

static Item *items = NULL;
static int itemsLength = 0;
static bool stringBased = false;

void hashMapInit(int length, bool isStringBased) {
    stringBased = isStringBased;

    items = malloc(length * sizeof(Item));
    itemsLength = length;

    for(int i = 0; i < itemsLength; i++)
    {
        Item item = EMPTY_ITEM;
        items[i] = item;
    }
}

void hashMapFree() {
    for(int i = 0; i < itemsLength; i++) {
    }
    free(items);
}

static int FNV_1a_32(char* data, int length) {
    int FNV_prime = 16777619;
    int FNV_offset_basis = 2166136261;
    int hash = FNV_offset_basis;
    for(int index = 0; index < length; index++)
    {
        hash = hash ^ data[index];
        hash = hash * FNV_prime;
    }
    return hash;
}

static int getIndex(int id) {
    int index = (FNV_1a_32((char*)&id, sizeof id) % itemsLength);
    if (index < 0) {
        index += itemsLength;
    }
    return index;
}

static int getIndexByName(char* name) {
    int index = (FNV_1a_32(name, strlen(name)) % itemsLength);
    if (index < 0) {
        index += itemsLength;
    }
    return index;
}

static void makeArrayBigger() {
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
            hashMapInsert(oldItems[i]);
        }
    }
    
    free(oldItems);
}

void hashMapInsert(Item item) {
    int itemIndex = 0;
    if(stringBased)
    {
        itemIndex = getIndexByName(item.name);
    }
    else
    {
        itemIndex = getIndex(item.id);
    }
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
        hashMapInsert(item);
    }
}

void hashMapDelete(int id) {
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

Item hashMapGet(int id) {
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

Item hashMapGetByName(char *itemName) {
    if(stringBased)
    {
        int itemIndex = getIndexByName(itemName);
        int index = itemIndex;
        bool found = false;
        do
        {
            if(items[index].id == EMPTY_ITEM_ID)
            {
                break; 
            }
            else if(strcmp(items[index].name, itemName) == 0)
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
    else
    {
        for(int index = 0; index < itemsLength; index++)
        {
            if(items[index].id != EMPTY_ITEM_ID && strcmp(items[index].name, itemName) == 0)
            {
                return(items[index]);
            }
        }
    }
}