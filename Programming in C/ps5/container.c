#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "container.h"
#include "item.h"

struct container* create_container(struct container* first, enum container_type type, void* entry) {
    if (entry == NULL || (first != NULL && first->type != type)) return NULL;
    
    if (first != NULL) {    
        if (type == ROOM && first->room == NULL) { first->room = (struct room*)entry; return first; }
        else if (type == ITEM && first->item == NULL) { first->item = (struct item*)entry; return first; }
        else if (type == COMMAND && first->command == NULL) { first->command = (struct command*)entry; return first; }
        else if (type == TEXT && first->text == NULL) { first->text = (char*)entry; return first; }
    }

    struct container* new_container = calloc(1, sizeof(struct container));
    new_container->type = type;
    if (type == ROOM) new_container->room = (struct room*)entry;
    else if (type == ITEM) new_container->item = (struct item*)entry;
    else if (type == COMMAND) new_container->command = (struct command*)entry;
    else if (type == TEXT) new_container->text = (char*)entry;
    
    if (first != NULL) {
        struct container* temp = first;
        while(temp->next != NULL) temp = temp->next;
        temp->next = new_container;
    } else {
        first = new_container;
    }
    return new_container;
}

struct container* destroy_containers(struct container* first) {
    if (first != NULL) {
        destroy_containers(first->next);
        if (first->type == ROOM) destroy_room(first->room);
        if (first->type == ITEM) destroy_item(first->item);
        if (first->type == COMMAND) destroy_command(first->command);
        if (first->type == TEXT) free(first->text);
        free(first);
    }
    return NULL;
}
 
void* get_from_container_by_name(struct container *first, const char *name) {
    if (first == NULL || name == NULL) return NULL;

    struct container* temp = first;
    while (temp != NULL) {
        if (temp->type == ROOM && temp->room != NULL && !strcmp(temp->room->name, name)) return temp->room;
        else if (temp->type == ITEM && temp->item != NULL &&!strcmp(temp->item->name, name)) return temp->item;
        else if (temp->type == COMMAND && temp->command != NULL && !strcmp(temp->command->name, name)) return temp->command;
        else if (temp->type == TEXT && temp->text != NULL && !strcmp(temp->text, name)) return temp->text;
        else temp = temp->next;
    }

    return NULL;
}

int compare_container(struct container* container, enum container_type type, void* entry) {
    switch (type) {
        case ROOM:
            return (entry != NULL) ? !strcmp(container->room->name, ((struct room*)entry)->name) : container->room == NULL;
        case ITEM:
            return (entry != NULL) ? !strcmp(container->item->name, ((struct item*)entry)->name) : container->item == NULL;
        case COMMAND:
            return (entry != NULL) ? !strcmp(container->command->name, ((struct command*)entry)->name) : container->command == NULL;
        case TEXT:
            return (entry != NULL) ? !strcmp(container->text, (char*)entry) : container->text == NULL;
    }
    return 0;
}

struct container* remove_container(struct container *first, void *entry) {
    if (first == NULL) return NULL;
    
    struct container* current = first;
    if (compare_container(first, first->type, entry)) {
        current = first->next;
        free(first);
        return current;
    }
    
    struct container* temp;
    while (current->next != NULL) {
        if (compare_container(current->next, current->type, entry)) {
            temp = current->next->next;
            free(current->next);
            current->next = temp;
        }
    }

    return first;
}
