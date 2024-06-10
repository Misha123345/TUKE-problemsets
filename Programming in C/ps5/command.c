#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "command.h"

struct command* create_command(char* name, char* description, char* pattern, size_t nmatch) {
    if (name == NULL || description == NULL || !strcmp("", name) || !strcmp("", description)) return NULL;

    struct command* result = calloc(1, sizeof(struct command));
    result->name = calloc(strlen(name) + 1, sizeof(char));
    result->description = calloc(strlen(description) + 1, sizeof(char));
    strcpy(result->name, name);
    strcpy(result->description, description);
    result->nmatch = nmatch;
    if (pattern != NULL) 
        regcomp(&result->preg, pattern, REG_EXTENDED); 

    return result;
}

struct command* destroy_command(struct command* command) {
    if (command != NULL) {
        if (command->name != NULL) free(command->name);
        if (command->description != NULL) free(command->description);
        if (command->groups != NULL) free(command->groups);
        regfree(&command->preg);
        free(command);
    }
    return NULL;
}
