#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static char **itemOwners;
static int ownersCount;
static char **itemModifiers;
static int modifiersCount;
static char **itemTypes;
static int typesCount;
static char **itemEnchantments;
static int enchantmentsCount;

static int lastItemIndex = -1;

char **ReadFileToArray(char* fileName, int* count)
{
    char line[1024];
    *count = 0;


    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("ERROR: Failed to open itemNames.txt\n" );
        exit(1);
    }
    while(fgets(line, sizeof(line), fp) != NULL)
    {
        char* newLinePointer = strchr(line, '\n');
        if(newLinePointer != NULL) { *newLinePointer = '\0'; }
        if(strlen(line) > 0)
        {
            (*count)++;
        }
    }
    fclose(fp);
    
    char **result = malloc((*count) * sizeof *result);
    
    fp = fopen(fileName, "r");
    int index = 0;
    while(fgets(line, sizeof(line), fp) != NULL)
    {
        char* newLinePointer = strchr(line, '\n');
        if(newLinePointer != NULL) { *newLinePointer = '\0'; }
        if(strlen(line) > 0)
        {
            result[index] = strdup(line);
            index++;
        }
    }
    fclose(fp);
    
    return result;
}

void initializeItemNames() {
    itemOwners = ReadFileToArray("itemOwners.txt", &ownersCount);
    itemModifiers = ReadFileToArray("itemModifiers.txt", &modifiersCount);
    itemTypes = ReadFileToArray("itemTypes.txt", &typesCount);
    itemEnchantments = ReadFileToArray("itemEnchantments.txt", &enchantmentsCount);
}

char* getItemName(int itemIndex)
{
    int totalPossibleNames = ownersCount * modifiersCount * typesCount * enchantmentsCount;

    if(itemIndex >= totalPossibleNames)
    {
        // beginning string
        // 10 max 32bit int to string
        // 1 null
        char *itemName = malloc(19 + 10 + 1);
        sprintf(itemName, "Unique item name #%i", itemIndex - totalPossibleNames);

        return itemName;
    }
    else
    {
        int ownerIndex = itemIndex % ownersCount;
        int workingIndex = itemIndex / ownersCount;

        int modifierIndex = workingIndex % modifiersCount;
        workingIndex = workingIndex / modifiersCount;

        int typeIndex = workingIndex % typesCount;
        workingIndex = workingIndex / typesCount;

        int enchantmentIndex = workingIndex % enchantmentsCount;

        char temp[1024];
        sprintf(temp, "%s %s %s of %s", itemOwners[ownerIndex], itemModifiers[modifierIndex], itemTypes[typeIndex], itemEnchantments[enchantmentIndex]);

        char *itemName = malloc(strlen(temp) + 1);
        strcpy(itemName, temp);

        return itemName;
    }
}

char* getNextItemName() {
    lastItemIndex++;
    char* itemName = getItemName(lastItemIndex);
    return itemName;
}
