#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "room.h"
#include "container.h"
#include "item.h"

struct room* create_room(char *name, char *description) {
    if (name == NULL || description == NULL || !strcmp("", name) || !strcmp("", description)) return NULL;
    struct room* new_room = calloc(1, sizeof(struct room));
    new_room->name = calloc(strlen(name) + 1, sizeof(char));
    new_room->description = calloc(strlen(description) + 1, sizeof(char));
    strcpy(new_room->description, description);
    strcpy(new_room->name, name);
    return new_room;
}

struct room* destroy_room(struct room* room) {
    if (room != NULL) {
        if (room->name != NULL) free(room->name);
        if (room->description != NULL) free(room->description);
        if (room->items != NULL) destroy_containers(room->items);
        free(room);
    }
    return NULL;
}

void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west) {
    if (room == NULL) return;
    room->north = north;
    room->south = south;
    room->east = east;
    room->west = west;
}

void show_room(const struct room* room) {
    if (room == NULL) return;
    puts(room->description);    
    if (room->east == NULL && room->west == NULL && room->south == NULL && room->north == NULL) puts("There is no exit >:)");
    else puts("Výstupy:");
    if (room->north != NULL) puts("    Sever");
    if (room->south != NULL) puts("    Juh");
    if (room->east != NULL) puts("    Zapad");
    if (room->west != NULL) puts("    Vychod");
    if (room->items == NULL) puts("V miestnosti sa nenachadza nic zaujimave");
    else {
        puts("V miestnosti sa nachádzajú tieto predmety:");
        struct container* temp = room->items;
        while (temp != NULL) {
            printf("    %s\n", temp->item->name);
            temp = temp->next;
        }
    }
}

void delete_item_from_room(struct room* room, struct item* item) {
    if (room == NULL || item == NULL) return;
    room->items =  remove_container(room->items, item);
}

void add_item_to_room(struct room* room, struct item* item) {
    if (room == NULL || item == NULL) return;
    room->items = create_container(room->items, ITEM, item); 
}

struct item* get_item_from_room(const struct room* room, const char* name) {
    if (room == NULL || name == NULL) return NULL;
    return get_from_container_by_name(room->items, name);
}

