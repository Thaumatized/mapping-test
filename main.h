#pragma once

#include "common.h"

int main(int argc, char *argv[]);

void waitForInput(char *currentStatus);

void printTime(char *category, clock_t startClock, clock_t endClock, int count);

void regularArrayInserts(Item *items, int count);

void regularArrayGets(Item *items, int count);

void moduloMapInserts(Item *items, int count);

void moduloMapGets(Item *items, int count);

void hashMapInserts(Item *items, int count);

void hashMapGets(Item *items, int count);
