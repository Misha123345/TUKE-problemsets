#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <math.h>
#include "c4.h"

void initialize_board(int rows, int cols, char board[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            board[i][j] = '.';
        }
    }
}


/*void print_board(int rows, int cols, const char board[rows][cols]) {
    int max_height, max_width;
    getmaxyx(stdscr, max_height, max_width);
    WINDOW *game_win = newwin(rows + 2, (cols * 4) + 1, (max_height - (rows + 2)) / 2, (max_width - (cols * 4) - 1) / 2);
    start_color();
    refresh();
    init_pair(1, COLOR_BLUE, COLOR_BLACK); 
    init_pair(2, COLOR_RED, COLOR_BLACK);

    for (int i = 0; i < (cols * 4) + 1; i++) {                                                               
         for (int j = 0; j < rows; j++) {                                                                        
             if (i % 4  == 0) {                                                                                  
                 mvwaddch(game_win, j, i, '|');                                                    
             } else if (i % 2 == 0) {
                 if (board[j][(i - 1) / 4] == 'O')wattron(game_win, COLOR_PAIR(1));
                 if (board[j][(i - 1) / 4] == 'Q')wattron(game_win, COLOR_PAIR(2));               
                 mvwaddch(game_win, j, i, board[j][(i - 1) / 4]);                 
                 if (board[j][(i - 1) / 4] == 'O')wattroff(game_win, COLOR_PAIR(1));
                 if (board[j][(i - 1) / 4] == 'Q')wattroff(game_win, COLOR_PAIR(2));              
             } else {                                                                                            
                 mvwaddch(game_win, j, i, ' ');                                                    
             }                                                                                                   
         }                                                                                                      
                                                                     
         mvwprintw(game_win, rows, i, "-");

         if (i % 4 != 0 && i % 2 == 0) {                                                                         
             mvwprintw(game_win, rows + 1, i, "%d", (i / 4) + 1);                                  
         }                                                                                                                                                                                       
     }         

     wrefresh(game_win);                                                                                         
     refresh();        
}*/

int is_valid_move(int rows, int cols, const char board[rows][cols], int col) {
    if (board[0][col - 1] != '.') return 0; 
    return 1;
}

int drop_piece(int rows, int cols, char board[rows][cols], int col, char player_piece) {
    if (is_valid_move(rows, cols, board, col)) {
        if (board[rows - 1][col - 1] == '.') {
            board[rows - 1][col - 1] = player_piece;
            return rows - 1;
        } else {
            for (int i = 0; i < rows - 1; i++) {
                if (board[i][col - 1] == '.' && board[i + 1][col - 1] != '.') {
                    board[i][col - 1] = player_piece;
                    return i;
                }   
            }
        }
    } 

    return -1;
}

int check_win(int rows, int cols, const char board[rows][cols], int row, int col, char player_piece) {
    int count;

    for (int i = 0; i <= rows - 4; i++) {
        if(board[i][col] == player_piece && board[i + 1][col] == player_piece && board[i + 2][col] == player_piece && board[i + 3][col] == player_piece) {
            return 1;
        }
    } 
    
    for (int i = 0; i <= cols - 4; i++) {
        if(board[row][i] == player_piece && board[row][i + 1] == player_piece && board[row][i + 2] == player_piece && board[row][i + 3] == player_piece) {
            return 1;
        }
    } 
    
    count = 1;
    for (int i = 1; i < 4; i++) {
        if(row + i <= rows - 1 && col - i >= 0 && board[row + i][col - i] == player_piece && board[row + i - 1][col - i + 1] == player_piece) count++;
        if(row - i >= 0 && col + i <= cols - 1 && board[row - i][col + i] == player_piece && board[row - i + 1][col + i - 1] == player_piece) count++;
    } 
    if (count >= 4) {
        return 1;
    }

    count = 1;
    for (int i = 1; i < 4; i++) {
        if(row - i >= 0 && col - i >= 0 && board[row - i][col - i] == player_piece && board[row - i + 1][col - i + 1] == player_piece) count++;
        if(row + i <= rows - 1 && col + i <= cols - 1 && board[row + i][col + i] == player_piece && board[row + i - 1][col + i - 1] == player_piece) count++;
    } 
    if (count >= 4) {
        return 1;
    }

    return 0;
}

int is_board_full(int rows, int cols, const char board[rows][cols]) {
    for (int i = 0; i < cols; i++) {
        if (board[0][i] == '.') return 0;
    }
    return 1;
}
/*
int find_center_for_text(char text[], int max_width) {                                                          
    return (max_width - strlen(text)) / 2;                                                                    
}                      

void print_title(int max_height, int max_width, int rows) {
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    
    start_color();  
    
    attrset(COLOR_PAIR(2) | A_BOLD);
    mvaddstr((max_height - rows - 6) / 2, find_center_for_text("Connect Four", max_width), "Connect ");
    attrset(COLOR_PAIR(1) | A_BOLD);
    printw("Four");
    attroff(COLOR_PAIR(1) | A_BOLD);
    refresh();
}
*/
/*int get_number(int center_text_y, int center_text_x, int player, int max_width, int columns) {
    int number;
    do {
        mvprintw(center_text_y, center_text_x , "Player %d, make turn: ", player);
        clrtoeol();
        refresh();
        number = getch();
        if (number == KEY_F(1)) {
            return -1;
        }
        number -= 48;

        if (number > 0 && number <= columns) {
            move(center_text_y + 1, ((max_width - 41) / 2));
            clrtoeol();
            return number;
        } else {
            mvprintw(center_text_y + 1, ((max_width - 41) / 2), "You need to enter number beetwen 1 and %d!", columns);
        }
    } while(1);

    return 0;
} */

/*void connect_four() {
    int rows = 4, cols = 5;
    char board[rows][cols];
    int max_height, max_width;
    int player = 1;
    int dialog_center;
    int col, row;
    char player_piece;

    initialize_board(rows, cols, board);

    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();

    getmaxyx(stdscr, max_height, max_width);

    mvaddstr(0, 0, "Press F1 to exit");
    print_title(max_height, max_width, rows);
    dialog_center = find_center_for_text("Player 1, make turn: ", max_width);
    while (!is_board_full(rows, cols, board)) {
        print_board(rows, cols, board);
        player_piece = (player == 1) ? 'O' : 'Q';
        
        col = get_number((max_height + rows + 4) / 2, dialog_center, player, max_width, cols);
        if (col == -1) break;
        row = drop_piece(rows, cols, board, col, player_piece);

        while (row == -1) {
            mvaddstr((max_height + rows + 6) / 2,find_center_for_text("Column is full, try again!", max_width), "Column is full, try again!");
            refresh();
            col = get_number((max_height + rows + 4) / 2, dialog_center, player, max_width, cols);
            if (col == -1) break;
            row = drop_piece(rows, cols, board, col, player_piece);
        }
        if (col == -1) break;
        if (check_win(rows, cols, board, row, col - 1, player_piece)) {
            print_board(rows, cols, board);
            move((max_height + rows + 4) / 2, 0);
            clrtoeol();
            attrset(A_BOLD);
            mvprintw((max_height + rows + 4) / 2, find_center_for_text("Player 1 win!", max_width), "Player %d win!", player);
            attroff(A_BOLD);
            getch();
            break;
        }
        player = (player == 1) ? 2 : 1;
    }
    if (is_board_full(rows, cols, board)) {
        print_board(rows, cols, board);
        move((max_height + rows + 4) / 2, 0);
        clrtoeol(); 
        attrset(A_BOLD);
        mvaddstr((max_height + rows + 4) / 2, (max_width - 5) / 2, "Draw!");
        attroff(A_BOLD);
        getch();
    }

    endwin();
}*/



/*int main() {
    connect_four();
    return 0;
} */
