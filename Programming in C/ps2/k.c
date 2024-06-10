#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "k.h"

bool move_up(struct game *game);
bool move_down(struct game *game);
bool move_left(struct game *game);
bool move_right(struct game *game);
void add_score(char letter, struct game *game);

void add_random_tile(struct game *game){
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}

bool is_game_won(const struct game game) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (game.board[i][j] == 'K') return true;
        }
    }
    return false;
}

bool is_move_possible(const struct game game) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (game.board[i][j] == ' ') return true;
        }
    }


    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i + 1 != SIZE && game.board[i][j] == game.board[i + 1][j]) return true;
            else if (j + 1 != SIZE && game.board[i][j] == game.board[i][j + 1]) return true;
        }
    }

    return false;
}

bool update(struct game *game, int dy, int dx) {
    if ((dy != 0 && dx != 0) || (dy == 0 && dx == 0)) return false;

    bool is_changed = false;

    if (dy == -1) {
        is_changed = move_up(game);
    } else if (dy == 1) {
        is_changed = move_down(game);
    } else if (dx == -1) {
        is_changed = move_left(game);
    } else if (dx == 1) {
        is_changed = move_right(game);
    }
            
    return is_changed;
}

bool move_up(struct game *game) {
    bool is_changed = false;
    int offset = -1;

    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE; i++) {
            if (game->board[i][j] != ' ') {
                for (int k = i; k > 0; k--) {
                    if (game->board[k - 1][j] == ' ') {
                        game->board[k - 1][j] = game->board[k][j];
                        game->board[k][j] = ' ';
                        is_changed = true;
                    } else if (game->board[k - 1][j] == game->board[k][j] && k + 1 != offset) {
                        game->board[k - 1][j] += 1;
                        game->board[k][j] = ' ';
                        offset = k + 1;
                        add_score(game->board[k - 1][j], game);
                        is_changed = true;
                        break;
                    }
                }
            }
        }
        offset = 0;
    }

    return is_changed;
}

bool move_down(struct game *game){ 
    bool is_changed = false;
    int offset = -1;
        
    for (int j = 0; j < SIZE; j++) {
        for (int i = SIZE - 1; i >= 0; i--) {
            if (game->board[i][j] != ' ') {
                for (int k = i; k < SIZE - 1; k++) {
                    if (game->board[k + 1][j] == ' ') {
                        game->board[k + 1][j] = game->board[k][j];
                        game->board[k][j] = ' ';
                        is_changed = true;
                    } else if (game->board[k + 1][j] == game->board[k][j] && k+1 != offset) {
                        game->board[k + 1][j] += 1;
                        game->board[k][j] = ' ';
                        offset = k + 1;
                        add_score(game->board[k + 1][j], game);
                        is_changed = true;
                        break;
                    }
                }
            }
        }
        offset = 0;
    }

    return is_changed; 
}

bool move_left(struct game *game) {
    bool is_changed = false;
    int offset = -1;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (game->board[i][j] != ' ') {
                for (int k = j; k > 0; k--) {
                    if (game->board[i][k - 1] == ' ') {
                        game->board[i][k - 1] = game->board[i][k];
                        game->board[i][k] = ' ';
                        is_changed = true;
                    } else if (game->board[i][k - 1] == game->board[i][k] && k+1 != offset) {
                        game->board[i][k - 1] += 1;
                        game->board[i][k] = ' ';
                        offset = k+1;
                        add_score(game->board[i][k - 1], game);
                        is_changed = true;
                        break;
                    }
                }
            }
        }
        offset = 0;
    }

    return is_changed;
}

bool move_right(struct game *game) {
    bool is_changed = false;
    int offset = -1;

    for (int i = 0; i < SIZE; i++) {
        for (int j = SIZE - 1; j >= 0; j--) {
            if (game->board[i][j] != ' ') {
                for (int k = j; k < SIZE - 1; k++) {
                    if (game->board[i][k + 1] == ' ') {
                        game->board[i][k + 1] = game->board[i][k];
                        game->board[i][k] = ' ';
                        is_changed = true;
                    } else if (game->board[i][k + 1] == game->board[i][k] && k + 1 != offset) {
                        game->board[i][k + 1] += 1;
                        game->board[i][k] = ' ';
                        offset = k + 1;
                        add_score(game->board[i][k + 1], game);
                        is_changed = true;
                        break;
                    }
                }
            }
        }
        offset = 0;
    }

    return is_changed;
}

void add_score(char letter, struct game *game) {
    int amount = 2;
    char symbol = 'A';
    for (int i = 0; i < 11; i++) {
        if (letter == symbol) {
            game->score += amount;
            return;
        } else {
            amount*=2;
            symbol+=1;
        }
    }
}
