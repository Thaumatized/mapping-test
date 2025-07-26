#pragma once

#include <stddef.h>

struct Item {
    int id;
    char *name;
    int value;
    int weight;
} typedef Item;

#define EMPTY_ITEM_ID -1

#define DELETED_ITEM_ID -2

#define EMPTY_ITEM {EMPTY_ITEM_ID, NULL, -1, -1};
