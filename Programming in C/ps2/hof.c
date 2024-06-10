#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hof.h"

int compare_fun(const void * a, const void * b) {
    const struct player *player1 = (const struct player *)a;
    const struct player *player2 = (const struct player *)b;
    return player2->score - player1->score;
}

int load(struct player list[]) {
    FILE* score_list = fopen(HOF_FILE, "r");
    if (score_list == NULL) return -1;
    int count = 0;
    struct player player;

    for (int i = 0; i < 10; i++) {
        if (fscanf(score_list, "%s %d", player.name, &player.score) == 2) {
            list[i] = player;
            count++;
        } else break;
    } 

    qsort(list, (unsigned long)count, sizeof(struct player), compare_fun);

    fclose(score_list);

    return count;
}

bool save(const struct player list[], const int size) {
    if (size == 0) return true;
    if (size <= 0 || size > 10) return false;

    FILE* score_file = fopen(HOF_FILE, "w");
    if (score_file == NULL) return false;

    struct player copy[10];

    for (size_t i = 0; i < size; i++) {
        copy[i] = list[i];
    }

    qsort(copy, (unsigned long)size, sizeof(struct player), compare_fun);

    for (int i = 0; i < size; i++) {
       if (fprintf(score_file, "%s %d\n", copy[i].name, copy[i].score) < 0) return false;
    }

    fclose(score_file);

    return true;
}

bool add_player(struct player list[], int* size, const struct player player) { 
    if (*size > 10 || *size < 0) return false;
    bool is_pasted = false;
    
    struct player temp;
    int i = 0;

    for (; i < *size; i++) {
        if (list[i].score <= player.score) {
            if (*size < 10) (*size)++;
            temp = list[i];
            list[i++] = player;
            is_pasted = true;
            break;
        }
    }

    if (i == *size && *size < 10) {
        (*size)++;
        list[i] = player;
        return true;
    }

    struct player second_temp;

    if (i <= *size) {
        for ( ; i < *size; i++) {
            second_temp = list[i];
            list[i] = temp;
            temp = second_temp;
        }
    }   

    return is_pasted;
}
