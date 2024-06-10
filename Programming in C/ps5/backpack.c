#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "backpack.h"
#include "container.h"
#include "item.h"

struct backpack* create_backpack(const int capacity) {
    struct backpack* new_backpack = calloc(1, sizeof(struct backpack));
    new_backpack->capacity = capacity;
    new_backpack->size = 0;
    return new_backpack;
}

struct backpack* destroy_backpack(struct backpack* backpack) {
    if (backpack != NULL) {
        if(backpack->items != NULL) destroy_containers(backpack->items);
        free(backpack);
    }
    return NULL;
}

bool add_item_to_backpack(struct backpack* backpack, struct item* item) {
    if (backpack == NULL || item == NULL) return false;
    if (backpack->size >= backpack->capacity) return false;
    if (backpack->items == NULL) backpack->items = create_container(backpack->items, ITEM, item);
    else create_container(backpack->items, ITEM, item);
    if (get_from_container_by_name(backpack->items, item->name) == NULL) return false;
    backpack->size++;
    return true;    
}

void delete_item_from_backpack(struct backpack* backpack, struct item* item) {
    if (backpack == NULL || item == NULL) return;
    if (get_from_container_by_name(backpack->items, item->name) == NULL) return;
    backpack->items = remove_container(backpack->items, item);
    backpack->size--;
}

struct item* get_item_from_backpack(const struct backpack* backpack, char* name) {
    if ((name != NULL && !strcmp("", name)) || name == NULL || backpack == NULL) return NULL;
    return get_from_container_by_name(backpack->items, name);
}
