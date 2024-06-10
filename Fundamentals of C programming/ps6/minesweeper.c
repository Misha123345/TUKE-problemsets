#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "minesweeper.h"

struct cell
{ 
    int y; 
    int x; 
    bool is_bomb;  
    bool is_opened; 
    bool is_flaged; 
};

void minesweeper(int rows, int cols);
static void initialize_field(int rows, int cols, struct cell field[rows][cols]);
static void draw_field(WINDOW * game_field, int rows, int cols, struct cell field[rows][cols], struct cell* current_cell);
static int find_bombs_around(int rows, int cols, struct cell field[rows][cols], int y, int x);
static int add_bombs (int rows, int cols, struct cell field[rows][cols], int y, int x);
static void open_empty_field(int rows, int cols, struct cell field[rows][cols], int y, int x, int* opened_cells);
static int set_record_time(int rows, int cols, int seconds);
static int get_record_time(int rows, int cols);

static void init_colorpairs();

void minesweeper(int rows, int cols) { 
    int button;
    int opened_cells_number = 0;
    struct cell field[rows][cols];
    int bombs_number;
    int flags;
    int max_y, max_x;
    int row = 0, col = 0;
    bool is_initialized = false;
    int record_time = get_record_time(rows, cols);
    struct cell *current_cell = &(field[row][col]);
    int start_time, minutes = 0, seconds = 0;
    int is_win = 0;
    init_colorpairs();
 
    initscr();
    getmaxyx(stdscr, max_y, max_x);
    curs_set(0);
    keypad(stdscr, TRUE);
    noecho();
    raw();
    nodelay(stdscr, TRUE);

    WINDOW * game_field = newwin(rows + 2, (cols * 2) + 3, (max_y - rows - 2) / 2, (max_x - (cols * 2) - 5) / 2);
    refresh();
    initialize_field(rows, cols, field);

    draw_field(game_field, rows, cols, field, current_cell);
    
    mvprintw(0, 0, "Press F1 to exit");
    mvprintw(max_y - 1, 0, "Arrows - Move Cursor; Z - Open Cell; X - Place Flag;");
    mvprintw(0, (max_x - 5) / 2, "%d : %d", minutes, seconds);
    mvprintw(0, max_x - 22, "Best time is: %d : %d", record_time / 60, record_time % 60);
    
    while ((button = getch()) != KEY_F(1)) {
        if (button == KEY_RIGHT && current_cell->x < cols - 1) {
            current_cell = &(field[row][++col]);
        } else if (button == KEY_LEFT && current_cell->x > 0) {
            current_cell = &(field[row][--col]);
        } else if (button == KEY_DOWN && current_cell->y < rows - 1) {
            current_cell = &(field[++row][col]);
        } else if (button == KEY_UP && current_cell->y > 0) {
            current_cell = &(field[--row][col]);
        } else if (button == 122 && current_cell->is_flaged == false && current_cell->is_opened == false) {
            current_cell->is_opened = true;
            opened_cells_number++;

            if (!is_initialized) {
                start_time = time(NULL);
                bombs_number = add_bombs(rows, cols, field, current_cell->y, current_cell->x);
                flags = bombs_number;
                is_initialized = true;
            }

            if (find_bombs_around(rows, cols, field, current_cell->y, current_cell->x) == 0) {
                open_empty_field(rows, cols, field, current_cell->y, current_cell->x, &opened_cells_number); 
            }

            if (current_cell->is_bomb == true) {
                is_win = 2;
                break;
            }
        } else if (button == 120 && current_cell->is_opened == false) {
            if (!current_cell->is_flaged && flags > 0) {
                flags--;
                current_cell->is_flaged = true;
            } else if (current_cell->is_flaged) {
                flags++;
                current_cell->is_flaged = false;
            }
        }

        if (is_initialized) {
            seconds = time(NULL) - start_time;
            if (seconds % 61 == 60) {
                minutes++;
                start_time = time(NULL);
            }
            move(0, 18);
            clrtoeol();
            mvprintw(0, (max_x - 5) / 2, "%d : %d", minutes, seconds);
            mvprintw(0, max_x - 22, "Best time is: %d : %d", record_time / 60, record_time % 60);
            move(1, 0);
            clrtoeol();
            mvprintw(1, max_x - 22, "Amount of flags: %d", flags);
        }

        if (opened_cells_number == (rows * cols) - bombs_number) {
            is_win = 1;
            break;
        }

        draw_field(game_field, rows, cols, field, current_cell);
    }

    if (is_win) {
        nodelay(stdscr, FALSE);
        draw_field(game_field, rows, cols, field, current_cell);
        attron(COLOR_PAIR(9) | A_BOLD);
        mvprintw(((max_y - rows - 2) / 2) - 2, (max_x - 9) / 2, (is_win == 1) ? "You Win!" : "You Lose!");
        attroff(COLOR_PAIR(9) | A_BOLD);
        if ((record_time > minutes * 60 + seconds || record_time == 0) && is_win == 1) {
            if(set_record_time(rows, cols, minutes * 60 + seconds) == -1) printf("File records.txt is missing");    
        }
        getch();
    }

    endwin();
}

static int find_bombs_around(int rows, int cols, struct cell field[rows][cols], int y, int x) {
    int count = 0;

    if (y - 1 >= 0) {
        if (x - 1 >= 0 && field[y - 1][x - 1].is_bomb) count++;
        if (field[y - 1][x].is_bomb) count++;
        if (x + 1 < cols && field[y - 1][x + 1].is_bomb) count++;
    }
   
    if (x - 1 >= 0 && field[y][x - 1].is_bomb) count++;
    if (x + 1 < cols && field[y][x + 1].is_bomb) count++;

    if (y + 1 < rows) {
        if (x - 1 >= 0 && field[y + 1][x - 1].is_bomb) count++;
        if (field[y + 1][x].is_bomb) count++;
        if (x + 1 < cols && field[y + 1][x + 1].is_bomb) count++;
    }
    
    return count;
}

static void initialize_field(int rows, int cols, struct cell field[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            struct cell temp = {i, j, false, false, false};
            field[i][j] = temp;
        }
    }
}

static int add_bombs (int rows, int cols, struct cell field[rows][cols], int y, int x) {
    bool is_bomb = false;
    int bombs_number = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i > y + 1 || i < y - 1 || j > x + 1 || j < x - 1) {
                is_bomb = rand() % (cols / (cols / 4)) == 0;
            }
            if (is_bomb) bombs_number++; 
            field[i][j].is_bomb = is_bomb;
            is_bomb = false;
        }
    }
    return bombs_number;  
}

static void draw_field(WINDOW * game_field ,int rows, int cols, struct cell field[rows][cols], struct cell* current_cell) {
    int bombs_around = 0;
    init_colorpairs();

    for (int i = 0; i < rows; i++) {
        wmove(game_field, i + 1, 2);
        for (int j = 0; j < cols; j++) {

            if (i == current_cell->y && j == current_cell->x) {
                wattron(game_field, COLOR_PAIR(10) | A_BOLD);
            } else {
                wattron(game_field, COLOR_PAIR(8));
            }

            if (field[i][j].is_flaged == true){
                if (i != current_cell->y || j != current_cell->x) wattron(game_field, COLOR_PAIR(7) | A_BOLD);
                wprintw(game_field, "P");
                if (i != current_cell->y || j != current_cell->x) wattroff(game_field, COLOR_PAIR(7) | A_BOLD);
            } else if (field[i][j].is_opened == false) {
                wprintw(game_field, "#");
            } else if(field[i][j].is_bomb == true) {
                wprintw(game_field, "X");
            } else {
                bombs_around = find_bombs_around(rows, cols, field, i, j);
                if (bombs_around == 0) {
                    wprintw(game_field, " ");
                }

                if (!(i == current_cell->y) || !(j == current_cell->x)) { 
                    wattroff(game_field, COLOR_PAIR(8));
                    wattron(game_field, COLOR_PAIR(bombs_around) | A_BOLD);
                }

                if (bombs_around != 0) wprintw(game_field, "%d", bombs_around);
                
                if (i != current_cell->y || j != current_cell->x) {
                    wattroff(game_field, COLOR_PAIR(bombs_around) | A_BOLD); 
                }
            }
            if (i == current_cell->y && j == current_cell->x) {
                wattroff(game_field, COLOR_PAIR(10) | A_BOLD);
            }
            wattron(game_field, COLOR_PAIR(8));
            wprintw(game_field, " ");
            wattroff(game_field, COLOR_PAIR(8));
        }
    }

    wattron(game_field, COLOR_PAIR(8) | A_DIM);
    box(game_field, 0, 0);
    for (int i = 1; i < rows + 1; i++) {
        wmove(game_field, i, 1);
        wprintw(game_field, " ");
    }
    wattroff(game_field, COLOR_PAIR(8) | A_DIM);
    wrefresh(game_field);
    refresh();
}

static void open_empty_field(int rows, int cols, struct cell field[rows][cols], int y, int x, int* opened_cells) {
    bool is_exist_check;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            is_exist_check = (y + i >= 0 && y + i < rows && x + j >= 0 && x + j < cols);
            if ((i != 0 || j != 0) && is_exist_check && !field[y + i][x + j].is_opened && !field[y][x].is_bomb && find_bombs_around(rows, cols, field, y, x) == 0) {
                field[y + i][x + j].is_opened = true;
                *opened_cells += 1;
                if (find_bombs_around(rows, cols, field, y + i, x + j) == 0) {
                    open_empty_field(rows, cols, field, y + i, x + j, opened_cells);
                }
            }
        }
    }
}

static int set_record_time(int rows, int cols, int seconds) {
    int numbers[3];
    int current_pos;
    bool is_found = false;

    FILE* records = fopen("records.txt", "r+");
    if (records == NULL) {
        return -1;
    } else {
        current_pos = ftell(records);
        while (fscanf(records, "%d %d %d\n", &numbers[0], &numbers[1], &numbers[2]) == 3) {
            if (numbers[0] == rows && numbers[1] == cols) {
                fseek(records, current_pos, SEEK_SET);
                fprintf(records, "%d %d %d\n", rows, cols, seconds);
                is_found = true;
                break;
            }
            current_pos = ftell(records);
        }
    }

    if (!is_found) {
        fseek(records, 0, SEEK_END);
        fprintf(records, "%d %d %d\n", rows, cols, seconds);
    }   

    fclose(records);
    return 0;
}

static int get_record_time(int rows, int cols) {
    int numbers[3];

    FILE* records = fopen("records.txt", "r");
    if (records == NULL) {
        return -1;
    } else {
        while (fscanf(records, "%d %d %d\n", &numbers[0], &numbers[1], &numbers[2]) == 3) {
            if (numbers[0] == rows && numbers[1] == cols) {
                fclose(records);
                return numbers[2];
            }
        }
    }
    fclose(records);
    return 0;
}

static void init_colorpairs() {
    use_default_colors();
    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_WHITE);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_YELLOW, COLOR_WHITE);
    init_pair(5, COLOR_CYAN, COLOR_WHITE);
    init_pair(6, COLOR_GREEN, COLOR_WHITE);
    init_pair(7, COLOR_RED, COLOR_WHITE);
    init_pair(8, COLOR_BLACK, COLOR_WHITE);
    init_pair(9, COLOR_RED, COLOR_BLACK);
    init_pair(10, COLOR_WHITE, COLOR_GREEN);
}
