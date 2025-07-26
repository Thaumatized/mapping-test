#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "common.h"
#include "regularArray.h"
#include "moduloMap.h"

int main(int argc, char *argv[])
{
	// Rand init
	time_t t = time(NULL);
	srand(t);
	
    // Reading arguments
	int arrayLength = 1024;
    int maxId = 1024;
	int count = 512;
    bool forceResize = false;

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
		if (!strcmp(argv[i], "-c"))
		{
			count = atoi(argv[i+1]);
			i++;
		}
		if (!strcmp(argv[i], "-r"))
		{
			forceResize = true;
		}
	}

    if(count > maxId)
    {
        printf("ERROR: count is larger than maxId.\n");
        return 1;
    }

    // Prepare items
    Item *items;
    items = malloc(count*sizeof(Item));
    FILE *fp = fopen("itemNames.txt", "r");
    if (fp == NULL) {
        printf("ERROR: Failed to open itemNames.txt\n" );
        exit(1);
    }
    char line[1024];
    for(int i = 0; i < count; i++)
    {
        if(fgets(line, sizeof(line), fp) == NULL)
        {
            // If we are out of names start from the beginning
            fclose(fp);
            FILE *fp = fopen("itemNames.txt", "r");
            fgets(line, sizeof(line), fp);
        }
        int nameLength = strlen(line)+1;
        char itemName[nameLength];
        memcpy(itemName, line, nameLength);
        // This id range will allow for any id only if maxId is divisible by count.
        // Otherwise the remainder is inaccessible from the top of the range.
        int idRange = (maxId / count);
        int minId = idRange * i;
        int id = minId + (rand() % (idRange));
        items[i].id = id;
        items[i].name = itemName;
        items[i].value = (rand() % 10) + 10;
        items[i].weight = (rand() % 10) + 10;
    }
    fclose(fp);

    // Prepare clock
    clock_t overallStartClock, overallStopClock;
    waitForInput("Prepared items for tests");

    regularArrayInit(arrayLength);
    waitForInput("Initialized regular array");

    overallStartClock = clock();
    regularArrayInserts(items, count);
    overallStopClock = clock();
    printTime("regular array inserts", overallStartClock, overallStopClock, count);
    waitForInput("Regular array inserts done");

    overallStartClock = clock();
    regularArrayGets(items, count);
    overallStopClock = clock();
    printTime("regular array gets", overallStartClock, overallStopClock, count);
    waitForInput("Regular array gets done");
	
    regularArrayFree(arrayLength);
    waitForInput("Freed regular array");

    moduloMapInit(arrayLength);
    waitForInput("Initialized modulo map");

    overallStartClock = clock();
    moduloMapInserts(items, count);
    overallStopClock = clock();
    printTime("modulo map inserts", overallStartClock, overallStopClock, count);
    waitForInput("modulo map inserts done");

    overallStartClock = clock();
    moduloMapGets(items, count);
    overallStopClock = clock();
    printTime("modulo map gets", overallStartClock, overallStopClock, count);
    waitForInput("modulo map gets done");
	
    moduloMapFree(arrayLength);
    waitForInput("Freed modulo map");

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
        regularArrayGet(items[i].id);
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
        moduloMapGet(items[i].id);
    }
}