#include <ctype.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "command.h"
#include "container.h"
#include "parser.h"

struct parser* create_parser() {
    struct parser* parser = calloc(1, sizeof(struct parser));
    parser->history = calloc(1, sizeof(struct container));
    parser->history->type = COMMAND;
    struct command* temp = create_command("KONIEC", "Príkaz ukončí rozohratú hru", "(KONIEC|QUIT|EXIT)", 3);
    parser->commands = create_container(parser->commands, COMMAND, temp);
    temp = create_command("SEVER", "Presunutie na Sever", "(SEVER|\bS\b|^S\b|\bS$|^S$)", 2);
    create_container(parser->commands, COMMAND, temp);
    temp = create_command("JUH", "Presunutie na Juh", "(JUH|\bJ\b|^J\b|\bJ$|^J$)", 2);
    create_container(parser->commands, COMMAND, temp);
    temp = create_command("VYCHOD", "Presunutie na Vychod", "(VYCHOD|\bV\b|^V\b|\bV$|^V$)",2);
    create_container(parser->commands, COMMAND, temp);
    temp = create_command("ZAPAD", "Presunutie na Zapad", "(ZAPAD|\bZ\b|^Z\b|\bZ$|^Z$)", 2);
    create_container(parser->commands, COMMAND, temp);
    temp = create_command("ROZHLIADNI SA", "Pozriet sa dovkola", "(ROZHLIADNI SA)", 1);
    create_container(parser->commands, COMMAND, temp);
    temp = create_command("PRIKAZY", "Spomenust si prikazy", "(PRIKAZY|HELP|POMOC)", 3);
    create_container(parser->commands, COMMAND, temp);
    temp = create_command("VERZIA", "Pozriet sa verziu hry", "(VERZIA)", 1);
    create_container(parser->commands, COMMAND, temp);
    temp = create_command("RESTART", "Restartnut hru", "(RESTART)", 1);
    create_container(parser->commands, COMMAND, temp);
    temp = create_command("O HRE", "Co to je za hra", "(O HRE|ABOUT)", 2);
    create_container(parser->commands, COMMAND, temp);
    temp = create_command("VEZMI", "Vziat nieco do plecniaka", "(VEZMI)", 1);
    create_container(parser->commands, COMMAND, temp);
    temp = create_command("POLOZ", "Polozit nieco z plecniaka", "(POLOZ)", 1);
    create_container(parser->commands, COMMAND, temp);
    temp = create_command("INVENTAR", "Pozriet sa u plecniak", "(INVENTAR|\bI\b|^I\b|\bI$|^I$)", 2);
    create_container(parser->commands, COMMAND, temp);
    temp = create_command("POUZI", "Pouzit nieco", "(POUZI)", 1);
    create_container(parser->commands, COMMAND, temp);
    temp = create_command("PRESKUMAJ", "Preskumat nejaky predmet", "(PRESKUMAJ)", 1);
    create_container(parser->commands, COMMAND, temp);
    temp = create_command("NAHRAJ", "Nahrat poslednu scranku", "(NAHRAJ|LOAD)", 2);
    create_container(parser->commands, COMMAND, temp);
    temp = create_command("ULOZ", "Ulozit stav hry", "(ULOZ|SAVE)", 2);
    create_container(parser->commands, COMMAND, temp);
    
    struct container* temp_container = parser->commands;
    while (temp_container != NULL) {
        temp_container->type = COMMAND;
        temp_container = temp_container->next;
    }

    return parser;
}

struct parser* destroy_parser(struct parser* parser) {
    if (parser != NULL) {
        destroy_containers(parser->commands);
        destroy_containers(parser->history);
        free(parser);
    }
    return NULL;
}

char* string_to_upper(char* str) {
    if (str == NULL) return NULL;
    size_t len = strlen(str);
    char* copy = calloc(len + 1, sizeof(char));
    for(int i = 0; i < len; i++) copy[i] = (char)toupper(str[i]);
    return copy;
}

struct command* parse_input(struct parser* parser, char* input) {
    if (parser == NULL || input == NULL || !strcmp("", input)) return NULL;

    char* input_copy = string_to_upper(input);

    struct container* current = parser->commands;
    while (current != NULL) {
        struct command* command = current->command;
        regmatch_t pmatch[command->nmatch];
        if (regexec(&(command->preg), input_copy, command->nmatch, pmatch, 0) == 0) {
            free(input_copy);
            return command;
        }
        current = current->next;
    }

    free(input_copy);
    
    return NULL;
}
