#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backpack.h"
#include "command.h"
#include "container.h"
#include "game.h"
#include "item.h"
#include "parser.h"
#include "room.h"
#include "world.h"

struct game* create_game(){
    struct game* game = calloc(1, sizeof(struct game));
    if (game == NULL) return NULL;
    game->state = PLAYING;
    game->parser = create_parser();
    game->world = create_world();
    game->current_room = game->world->room;
    game->backpack = create_backpack(10);
    return game;
}

struct game* destroy_game(struct game* game) {
    if (game != NULL) {
        destroy_parser(game->parser);
        destroy_world(game->world);
        destroy_backpack(game->backpack);
        free(game);
    }
    return NULL;
}

void print_all_commands() {
    puts("All Commands:/n");
}

void print_credits() {
    printf("Mykhailo Kaniuka, 2024, version: 0.1 alpha build\n All rights reserved\n mykhailo.kaniuka@student.tuke.sk\n");
}   

void print_inventar() {
    puts("There is no itema in your backpack/n");
}

void execute_command(struct game* game, struct command* command) {
    if (game == NULL || command == NULL) return;
    if (!strcmp(command->name, "KONIEC")) game->state = GAMEOVER;
    else if (!strcmp(command->name, "SEVER") && game->current_room->north != NULL) game->current_room = game->current_room->north;
    else if (!strcmp(command->name, "JUH") && game->current_room->south != NULL) game->current_room = game->current_room->south;
    else if (!strcmp(command->name, "ZAPAD") && game->current_room->west != NULL) game->current_room = game->current_room->west;
    else if (!strcmp(command->name, "VYCHOD") && game->current_room->east != NULL) game->current_room = game->current_room->north;
    else if (!strcmp(command->name, "ROZHLIADNI SA")) show_room(game->current_room);
    else if (!strcmp(command->name, "PRIKAZY")) print_all_commands();
    else if (!strcmp(command->name, "VERZIA")) print_credits();
    else if (!strcmp(command->name, "RESTART")) game->state = RESTART;
    else if (!strcmp(command->name, "O HRE")) puts("Na zaciatku bolo slovo, a slovo toto Boh.\n");
    else if (!strcmp(command->name, "VEZMI")) puts("Beries nieco");
    else if (!strcmp(command->name, "INVENTAR")) print_inventar();
    else if (!strcmp(command->name, "POUZI")) puts("Neviem co chces pouzit");
    else if (!strcmp(command->name, "PRESKUMAJ")) puts("Neviem co chces preskumat");
    else if (!strcmp(command->name, "NAHRAJ")) printf("Nahram...");
    else if (!strcmp(command->name, "ULOZ")) printf("Uozim...");
}
