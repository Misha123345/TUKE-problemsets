#include <stdio.h>
#include <stdlib.h>
#include "k.h"
#include "ui.h"
#include "hof.h"

int main() {
    struct game game = {
        .score=8886,
        .board={
            {'B', 'C', 'C', ' '},
	        {' ', 'G', ' ', ' '},
	        {'E', 'G', ' ', 'I'},
	        {'G', ' ', ' ', ' '}
        }
    };

    update(&game, 0, -1);

    /*for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (game.board[i][j] == ' ') printf("%c ", '#');
            else printf("%c ", game.board[i][j]);
        }
        printf("\n");
    }*/
    
    add_random_tile(&game);

    printf("%d\n", game.score);
    is_move_possible(game);
    is_game_won(game);

    struct player table[10];

    int score_number = load(table);
    printf("count: %d\n", score_number);
    
    /*for (int i = 0; i < score_number; i++) {
        printf("%s %i\n", table[i].name, table[i].score);
    }*/

    struct player player1 = {.name = "NieMykhailo", .score = 100};
    
    bool is_added = add_player(table, &score_number, player1);

    printf("%d\n", is_added);

    bool is_complete = save(table, score_number);
    printf("%d\n", is_complete);

    render(game);

    return 0;
}   
