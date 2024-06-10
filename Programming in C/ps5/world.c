#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "container.h"
#include "item.h"
#include "world.h"
#include "room.h"

struct container* create_world() {
    struct room* start_room = create_room("Dungeon", "This is start of your jorney!");
    struct container* world = create_container(NULL, ROOM, start_room);

    struct room* temp_room;
    struct item* temp_item;
    char name[3];
    char dangeon_name[50] = "Dungeon";
    char dangeon_desc[50] = "This is dungeon";
    char item_name[50] = "Item";
    char item_desc[50] = "This is Description";
    
    for (int i = 0; i < 15; i++) {
        sprintf(name, "%d", i);
        temp_room = create_room(strcat(dangeon_name, name), strcat(dangeon_desc, name));
        temp_item = create_item(strcat(item_name, name), strcat(item_desc, name), MOVABLE);
        dangeon_name[7] = '\0'; dangeon_desc[15] = '\0'; item_name[4] = '\0'; item_desc[19] = '\0';
        add_item_to_room(temp_room, temp_item);
        create_container(world, ROOM, temp_room);
    }

    return world;
}

struct container* add_room_to_world(struct container* world, struct room* room) {
    if (room == NULL) return NULL;
    if (world != NULL && get_from_container_by_name(world, room->name) != NULL) return NULL;
    struct container* new_room = create_container(world, ROOM, room);
    return new_room;
}

struct container* destroy_world(struct container* world) {
    //if (world != NULL) {
      //  destroy_containers(world);
    //}

    return NULL;
}

struct room* get_room(struct container* world, char* name) {
    return get_from_container_by_name(world, name);
}
