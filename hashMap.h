#include "common.h"
#include <stdbool.h>

void hashMapInit(int length, bool stringBased);

void hashMapFree();

void hashMapInsert(Item item);

void hashMapDelete(int id);

Item hashMapGet(int id);

Item hashMapGetByName(char *itemName);