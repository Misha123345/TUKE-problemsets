#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "backpack.h"
#include "container.h"
#include "parser.h"
#include "room.h"
#include "game.h"
#include "command.h"
#include "world.h"
#include "item.h"


int main() {
    struct room* izba = create_room("room", "Some description");  
    
    struct container* first = create_container(NULL, ROOM, &izba);

    get_from_container_by_name(first, izba->name);
    first = remove_container(first, &izba);
    
    struct command* command = create_command("command", "this is command", "(COMMAND)", 1);
    
    create_game();
    destroy_game(NULL);
   
    struct item* item = create_item("buisness", "some desc0", NONE);
    
    struct room* room = create_room("izbababa", "desk uhuhd");
    set_exits_from_room(room, NULL, NULL, NULL, NULL);
    show_room(room);
    puts("========================================================");
    add_item_to_room(room, item);
    get_item_from_room(room, item->name);
    delete_item_from_room(room, item);

    struct backpack* backpack = create_backpack(10);
    add_item_to_backpack(backpack, item);
    get_item_from_backpack(backpack, "");
    delete_item_from_backpack(backpack, item);
    
    struct container* world = create_world();
    add_room_to_world(world, room);
    get_room(world, room->name);
    printf("here\n");

    struct backpack* backpack2 = create_backpack(2);
    char* name = "LANO";
    char* description = "Pouzitelne na dostanie sa von z hradu.";
    unsigned int properties = MOVABLE | USABLE;
    struct item* item2 = create_item(name, description, properties);
    printf("{{%d}}\n", add_item_to_backpack(backpack2, item2) == true);

    char* name2 = "LANO";
    char* description2 = "Pouzitelne na dostanie sa von z hradu.";
    unsigned int properties2 = MOVABLE | USABLE;
    struct item* item3 = create_item(name2, description2, properties2);
    printf("{{%d}}\n", add_item_to_backpack(backpack2, item3) == true);
    printf("%d\n", backpack2->size);

    struct game* game = create_game();
    struct parser* parser = create_parser();
    printf("success\n");
    struct command* test_command = parse_input(parser, "JUH");
    printf("success2\n");

    execute_command(game, test_command);

    destroy_command(command);
    destroy_backpack(backpack);
    //destroy_containers(first);
    destroy_room(room);
    destroy_world(world);
    destroy_parser(parser);
    destroy_game(game);

    return 0;
}
