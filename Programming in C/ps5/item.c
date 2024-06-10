#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "item.h"

struct item* create_item(char* name, char* description, unsigned int properties) {
    if (name == NULL || !strcmp("", name) || description == NULL || !strcmp("", description)) return NULL;
    struct item* item = calloc(1, sizeof(struct item));
    item->description = calloc(strlen(description) + 1, sizeof(char));
    strcpy(item->description, description);
    item->name = calloc(strlen(name) + 1, sizeof(char));
    strcpy(item->name, name);
    item->properties = properties;
    return item;
}

struct item* destroy_item(struct item* item) {
    if (item != NULL) {
        if (item->name != NULL) free(item->name);
        if (item->description != NULL) free(item->description);
        free(item);
    }  
    return NULL;
}

