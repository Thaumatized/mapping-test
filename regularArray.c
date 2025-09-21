#include "common.h"
#include "regularArray.h"

#include <stdlib.h> 
#include <string.h>

#include <stdio.h>

static Item *items = NULL;
static int itemsLength = 0;

void regularArrayInit(int length) {
    items = malloc(length * sizeof(Item));
    itemsLength = length;
    for(int index = 0; index < itemsLength; index++)
    {
        Item item = EMPTY_ITEM;
        items[index] = item;
    }
}

void regularArrayFree() {
    free(items);
}

void regularArrayInsert(Item item) {
    if(item.id >= itemsLength)
    {
        int oldItemsLength = itemsLength;
        printf("RESIZE FROM %i ", itemsLength);
        while (item.id >= itemsLength) {
            itemsLength *= 2;
        }
        printf("TO %i\n", itemsLength);
        Item *tempPointer = realloc(items, itemsLength*sizeof(Item));
        if(tempPointer != NULL) {
            items = tempPointer;
            
            for(int index = oldItemsLength; index < itemsLength; index++)
            {
                Item emptyItem = EMPTY_ITEM;
                items[index] = emptyItem;
            }

            items[item.id] = item;
        }
        else {
            printf("FAILED TO ALLOCATE MEMORY!");
        }
    }
    else
    {
        items[item.id] = item;
    }
}

void regularArrayDelete(int id) {
    Item item = EMPTY_ITEM;
    items[id] = item;
}

Item regularArrayGet(int id) {
    return items[id];
}

Item regularArrayGetByName(char *itemName)
{
    for(int index = 0; index < itemsLength; index++)
    {
        if(items[index].id != EMPTY_ITEM_ID && strcmp(items[index].name, itemName) == 0)
        {
            return(items[index]);
        }
    }
}