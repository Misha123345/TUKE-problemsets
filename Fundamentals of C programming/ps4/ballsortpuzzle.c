#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include <string.h>
#include <math.h>
#include <time.h>

void generator(const int rows, const int columns, char field[rows][columns]); //42
void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y); //100
bool check(const int rows, const int columns, char field[rows][columns]); //135
void game_field(const int rows, const int columns, char field[rows][columns]); //152
void ball_sort_puzzle();

void generator(const int rows, const int columns, char field[rows][columns]) {
    srand(time(NULL));
    int kostyl = 0;

    int empty_fields[2]; 
    empty_fields[0] = rand() % rows;
    do {
        int temp = rand() % columns;
        if (temp == empty_fields[0]) {
            continue;
        } else {
            empty_fields[1] = temp;
            break;
        }
    } while (1);

    char symbols[][2] = {{'+', 0}, {'@', 0}, {'$', 0}, {'O', 0}, {'D', 0}, {'q', 0}, {'U', 0}, {'P', 0}, {'a', 0}};
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (j == empty_fields[0] || j == empty_fields[1]) {
                field [i][j] = ' ';
            } else {
                kostyl = 0;
                int symbol_number = rand() % (columns - 2);
                while (kostyl < 2000) {
                    if (symbols[symbol_number][1] < rows) {
                        symbols[symbol_number][1] += 1;
                        break;
                    }
                    symbol_number = rand() % (columns - 2);
                    kostyl++;
                }
                field[i][j] = symbols[symbol_number][0];
            }
        }
    }
}

int get_movable_symbol_row(const int rows, const int columns, int x, char field[rows][columns]) {
    for (int i = 0; i < rows; i++) {                                                                             
        if (field[i][x] != ' ') {                                                                                
            return i;                                                                                               
        }
    }
    return -1; 
}

int get_row_with_free_space(const int rows, const int columns, int y, int movable_symbol ,char field[rows][columns]) {    
    if (field[rows - 1][y] == ' ') {
        return rows - 1;
    }
    for (int i = 0; i < rows - 1; i++) {
        if (field[i][y] == ' ' && field[i + 1][y] == movable_symbol) {
            return i;
        } else if (field[i][y] == ' ' && field[i + 1][y] != ' ' && field[i + 1][y] != movable_symbol) {
            return -1;
        } 
    }
    return -2;
}

int find_center_for_text(char text[], int max_width) {
    return ((max_width - strlen(text)) / 2);
}

void print_error(char text[], int center_text_y, int max_width) {
    int center_text_x = find_center_for_text(text, max_width);
    move(center_text_y, 0);
    clrtoeol();
    move(center_text_y, center_text_x);
    addstr(text);
}

void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y) {
    int max_height, max_width;
    getmaxyx(stdscr, max_height, max_width);
    int center_text_y = ((max_height / 2) + rows / 2 + 3);
    
    if (x == y) {
        print_error("You can't move ball to the same column!", center_text_y, max_width);
        return;
    }

    if (x < 1 || x > columns || y < 1 || y > columns) {
        print_error("You must enter correct numbers!", center_text_y, max_width);
        return;
    }

    int column_from = x - 1;
    int column_to = y - 1;

    int movable_symbol_row = get_movable_symbol_row(rows, columns, column_from, field);
    if (movable_symbol_row == -1) {
        print_error("You can't move balls from empty columns!", center_text_y, max_width);
        return;
    }

    char movable_symbol = field[movable_symbol_row][column_from];
    int free_space_in_row = get_row_with_free_space(rows, columns, column_to, movable_symbol, field);

    if (free_space_in_row == -1) {
        print_error("Symbols must be same!", center_text_y, max_width);
        return;
    } else if (free_space_in_row == -2) {
        print_error("This column is full!", center_text_y, max_width);
        return;
    } else {
        field[movable_symbol_row][column_from] = ' ';
        field[free_space_in_row][column_to] = movable_symbol;
    }
}

bool check(const int rows, const int columns, char field[rows][columns]) {
    bool not_complete = false;
    for (int i = 0; i < columns; i++) {
        char start_symbol = field[0][i];
        for (int j = 1; j < rows; j++) {
            if (field[j][i] != start_symbol) {
                not_complete = true;
                break;
            }
        }
        if (not_complete) {
            return false;    
        }
    }
    return true;
}

void game_field(const int rows, const int columns, char field[rows][columns]) {
    int max_height, max_width;
    getmaxyx(stdscr, max_height, max_width);
    WINDOW *game_win = newwin(rows + 2, (columns * 4) + 3, (max_height - (rows + 2)) / 2, (max_width - (columns * 4) - 3) / 2);
    refresh();
    int drawable_column = 0;
    
    for (int i = 0; i < rows; i++) {
        mvwprintw(game_win, i, drawable_column, "%d", (i + 1));
    }
    drawable_column += 2;
    for (int i = 0; i < (columns * 4) + 1; i++) {
        for (int j = 0; j < rows; j++) {
            if (i % 4  == 0) {
                mvwaddch(game_win, j, drawable_column, '|');
            } else if (i % 2 == 0) {
                mvwaddch(game_win, j, drawable_column, field[j][(i - 1) / 4]);
            } else {
                mvwaddch(game_win, j, drawable_column, ' ');
            }
        }
        if (i % 4 != 0) {
            mvwprintw(game_win, rows, drawable_column, "-");
        }
        if (i % 4 != 0 && i % 2 == 0) {
            mvwprintw(game_win, rows + 1, drawable_column, "%d", (i / 4) + 1);
        }

        drawable_column++;
    }


    wrefresh(game_win);
    refresh();
}

int get_number(int center_text_y, int center_text_x, char var_name[], int max_width, int columns) {
    int number;
    do {
        mvprintw(center_text_y, center_text_x , "Enter %s: ", var_name);
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
}

void ball_sort_puzzle() {  
    srand(time(NULL));  
    
    int max_height, max_width;
    int rows = (rand() % 3) + 4;
    int columns = (rand() % 3) + 6;
    char field[rows][columns];
    int from = 0, to = 0;
    int center_text_y, center_text_x;
    int is_exit = 0;

    generator(rows, columns, field);
    
    initscr();
    curs_set(0);
    start_color();
    keypad(stdscr, TRUE);
    
    getmaxyx(stdscr, max_height, max_width);
    center_text_y = ((max_height / 2) + ceil((float)rows / 2) + 2);
    center_text_x = ((max_width - 13) / 2);
    
    init_pair(1, COLOR_RED, COLOR_BLACK);
    attron(A_BOLD | COLOR_PAIR(1));
    mvaddstr((max_height - (rows + 2) - 5) / 2, (max_width - 16) / 2, "Ball Sort Puzzle");
    attroff(A_BOLD | COLOR_PAIR(1)); 
    
    mvaddstr(0, 0, "Press F1 to exit");  
    
    while (!check(rows, columns, field)) {
        game_field(rows, columns, field);
        from = get_number(center_text_y, center_text_x, "from", max_width, columns);
        if (from == -1) {
            is_exit = 1;
            break;
        }
        to = get_number(center_text_y, center_text_x, "to", max_width, columns);
        if (to == -1) {
            is_exit = 1;
            break;
        }
        down_possible(rows, columns, field, from, to);
    }
    if (!is_exit) {
        game_field(rows, columns, field);
        move(center_text_y, 0);
        clrtoeol();
        attron(COLOR_PAIR(1) | A_BOLD);
        mvaddstr(center_text_y, find_center_for_text("You Won!", max_width), "You Won!");
        attroff(COLOR_PAIR(1) | A_BOLD);
        getch();
    }

    if (3 > 10) ball_sort_puzzle();

    endwin();
}



