#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "common.h"
#include "itemNameGenerator.h"
#include "regularArray.h"
#include "moduloMap.h"
#include "hashMap.h"

int arrayLength = 1024;
int maxId = 1024;
int idStep = 0;
int count = 512;
bool stringBased = false;
bool stringBasedHash = false;

int main(int argc, char *argv[])
{
	// Rand init
	time_t t = time(NULL);
	srand(t);
	
    // Reading arguments
	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "-l"))
		{
            arrayLength = atoi(argv[i+1]);
			i++;
		}
		if (!strcmp(argv[i], "-m"))
		{
			maxId = atoi(argv[i+1]);
			i++;
		}
		if (!strcmp(argv[i], "-s"))
		{
			idStep = atoi(argv[i+1]);
			i++;
		}
		if (!strcmp(argv[i], "-c"))
		{
			count = atoi(argv[i+1]);
			i++;
		}
		if (!strcmp(argv[i], "-t"))
		{
			stringBased=true;
		}
		if (!strcmp(argv[i], "-h"))
		{
			stringBasedHash=true;
		}
	}

    if(count > maxId && idStep == 0)
    {
        printf("ERROR: count (%i) is larger than maxId (%i) and idStep (%i) is 0\n", count, maxId, idStep);
        return 1;
    }

    // Prepare items
    initializeItemNames();
    Item *items;
    items = malloc(count*sizeof(Item));
    for(int i = 0; i < count; i++)
    {
        int id = 0;

        if(idStep == 0)
        {
            // This id range will allow for any id only if maxId is divisible by count.
            // Otherwise the remainder is inaccessible from the top of the range.
            int idRange = (maxId / count);
            int minId = idRange * i;
            id = minId + (rand() % (idRange));
        }
        else
        {
            id = i * idStep;
        }

        items[i].id = id;
        items[i].name = getNextItemName();
        //printf("Item %i/%i is named %s\n", i, id, items[i].name);
        items[i].value = (rand() % 10) + 10;
        items[i].weight = (rand() % 10) + 10;
    }

    // Prepare clock
    clock_t startClock, stopClock;
    waitForInput("Prepared items for tests");

    // Regular Array
    /*
    regularArrayInit(arrayLength);
    waitForInput("Initialized regular array");

    startClock = clock();
    regularArrayInserts(items, count);
    stopClock = clock();
    printTime("regular array inserts", startClock, stopClock, count);
    waitForInput("Regular array inserts done");

    startClock = clock();
    regularArrayGets(items, count);
    stopClock = clock();
    printTime("regular array gets", startClock, stopClock, count);
    waitForInput("Regular array gets done");
	
    regularArrayFree(arrayLength);
    waitForInput("Freed regular array");
    */
   
    // Modulo Map
    moduloMapInit(arrayLength);
    waitForInput("Initialized modulo map");

    startClock = clock();
    moduloMapInserts(items, count);
    stopClock = clock();
    printTime("modulo map inserts", startClock, stopClock, count);
    waitForInput("modulo map inserts done");

    startClock = clock();
    moduloMapGets(items, count);
    stopClock = clock();
    printTime("modulo map gets", startClock, stopClock, count);
    waitForInput("modulo map gets done");
	
    moduloMapFree(arrayLength);
    waitForInput("Freed modulo map");

    // Hash Map
    hashMapInit(arrayLength, stringBasedHash);
    waitForInput("Initialized hash map");

    startClock = clock();
    hashMapInserts(items, count);
    stopClock = clock();
    printTime("hash map inserts", startClock, stopClock, count);
    waitForInput("hash map inserts done");

    startClock = clock();
    hashMapGets(items, count);
    stopClock = clock();
    printTime("hash map gets", startClock, stopClock, count);
    waitForInput("hash map gets done");
	
    hashMapFree(arrayLength);
    waitForInput("Freed hash map");

	return 0;
}

void waitForInput(char *currentStatus) {
    printf("Current status: %s\n", currentStatus);
    printf("Press enter to continue");
    char input[10];
    fgets(input, 10, stdin);
}

void printTime(char *category, clock_t startClock, clock_t endClock, int count) {
    printf ("Times from %s:\n", category);
    float total = (double)(endClock - startClock) / CLOCKS_PER_SEC;
    float average = total / count;
    
    printf("average time: %6.6f\n", average);
    printf("total time: %6.6f\n\n", total);
}

void regularArrayInserts(Item *items, int count) {
    for(int i = 0; i < count; i++)
    {        
        regularArrayInsert(items[i]);
    }
}

void regularArrayGets(Item *items, int count) {
    for(int i = 0; i < count; i++)
    {
        if(stringBased)
        {
            regularArrayGetByName(items[i].name);
        }
        else
        {
            regularArrayGet(items[i].id);
        }
    }
}

void moduloMapInserts(Item *items, int count) {
    for(int i = 0; i < count; i++)
    {
        moduloMapInsert(items[i]);
    }
}

void moduloMapGets(Item *items, int count) {
    for(int i = 0; i < count; i++)
    {
        if(stringBased)
        {
            moduloMapGetByName(items[i].name);
        }
        else
        {
            moduloMapGet(items[i].id);
        }
    }
}

void hashMapInserts(Item *items, int count) {
    for(int i = 0; i < count; i++)
    {
        hashMapInsert(items[i]);
    }
}

void hashMapGets(Item *items, int count) {
    for(int i = 0; i < count; i++)
    {
        if(stringBased)
        {
            hashMapGetByName(items[i].name);
        }
        else
        {
            hashMapGet(items[i].id);
        }
    }
}