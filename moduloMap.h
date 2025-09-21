#include "common.h"

void moduloMapInit(int length);

void moduloMapFree();

void moduloMapInsert(Item item);

void moduloMapDelete(int id);

Item moduloMapGet(int id);

Item moduloMapGetByName(char *itemName);