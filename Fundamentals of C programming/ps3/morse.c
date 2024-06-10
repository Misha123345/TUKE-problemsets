#include <string.h>
#include <ctype.h>
#include "morse.h"

void all_leters_to_small(char input[]) {
    for (int i = 0, len = strlen(input) + 1; i < len; i++) {
        input[i] = tolower(input[i]);
    }
}

void delete_white_symbols(char input[]) {
    int count = 0;
    for (int i = 0, len = strlen(input); i < len; i++) {
        if (input[i] != '\t' && input[i] != '\n' && input[i] != '!' && input[i] != '.' && input[i] != ',' && input[i] != ' ')
        {
            input[count++] = input[i];
        }
    }
    input[count] = '\0';
}

void text_to_morse(const char text[], char output[]) {
    char morse_map[][7] = {
        {'a', '.', '-'}, {'b', '-', '.', '.', '.'}, {'c', '-','.','-','.'}, {'d', '-','.','.'}, {'e', '.'},
        {'f', '.','.','-','.'}, {'g', '-','-','.'}, {'h', '.','.','.','.'}, {'i', '.','.'}, {'j', '.','-','-','-'},
        {'k', '-','.','-'}, {'l', '.','-','.','.'}, {'m', '-', '-'}, {'n', '-', '.'}, {'o', '-', '-', '-'},
        {'p', '.','-','-','.'}, {'q', '-','-','.','-'}, {'r', '.','-','.'}, {'s', '.','.','.'}, {'t', '-'},
        {'u', '.','.','-'}, {'v', '.','.','.','-'}, {'w', '.','-','-'}, {'x', '-','.','.','-'}, {'y', '-','.','-','-'}, {'z', '-','-','.','.'},
        {'0', '-', '-', '-', '-', '-'}, {'1', '.', '-', '-', '-', '-'}, {'2', '.', '.', '-', '-', '-'}, {'3', '.', '.', '.', '-', '-'}, {'4', '.', '.', '.', '.', '-'},
        {'5', '.', '.', '.', '.', '.'}, {'6', '-', '.', '.', '.', '.'}, {'7', '-', '-', '.', '.', '.'}, {'8', '-', '-', '-', '.', '.'}, {'9', '-', '-', '-', '-', '.'}
    };
    char tmp[strlen(text) * 5];
    strcpy(tmp, text);
    all_leters_to_small(tmp);
    delete_white_symbols(tmp);
    int count = 0;
    for (int i = 0, len = strlen(tmp); i < len; i++) {
        for (int j = 0; j < 36; j++) {
            if (tmp[i] == morse_map[j][0]) {
                for (int k = 1, morse_len = strlen(morse_map[j]); k < morse_len; k++) {
                    output[count++] = morse_map[j][k];
                }
            }
        }
        output[count++] = ' ';
    }
    output[count - 1] = '\0';
}

void morse_to_text(const char morse[], char output[]) {
    char morse_text_letters[][36][7] = {
        {".-", "A"}, {"-...", "B"}, {"-.-.", "C"}, { "-..", "D" }, { ".", "E" },
        { "..-.", "F" }, { "--.", "G" }, { "....", "H" }, { "..", "I" }, { ".---", "J" },
        { "-.-", "K" }, { ".-..", "L" }, { "--", "M" }, { "-.", "N" }, { "---", "O" },
        { ".--.", "P" }, { "--.-", "Q" }, { ".-.", "R" }, { "...", "S" }, { "-", "T" },
        { "..-", "U" }, { "...-", "V" }, { ".--", "W" }, { "-..-", "X" }, { "-.--", "Y" }, { "--..", "Z" },
        { "-----", "0" }, { ".----", "1" }, { "..---", "2" }, { "...--", "3" }, { "....-", "4" },
        { ".....", "5" }, { "-....", "6" }, { "--...", "7" }, { "---..", "8" }, { "----.", "9" }
    };

    char morse_copy[200];
    strcpy(morse_copy, morse);
    char* morse_letter = strtok(morse_copy, " ");
    int count = 0;
    while (morse_letter != NULL) {
        for (int i = 0; i < 36; i++) {
            if (strcmp(morse_letter, morse_text_letters[i][0]) == 0) {
                output[count++] = morse_text_letters[i][1][0];
                break;
            }
        }
        morse_letter = strtok(NULL, " ");
    }
    output[count] = '\0';
}

int is_morse_code_valid(const char morse[]) {
    char morse_text_letters[][6] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.",
        "--.", "....", "..", ".---", "-.-", ".-..",
        "--", "-.", "---", ".--.", "--.-", ".-.",
        "...", "-", "..-", "...-", ".--", "-..-", "-.--",
        "--..", "-----", ".----", "..---", "...--", "....-",
        ".....", "-....", "--...", "---..", "----."
    };

    char morse_copy[200];
    strcpy(morse_copy, morse);
    char* morse_letter = strtok(morse_copy, " ");
    int is_letter_exist = 0;
    while (morse_letter != NULL) {
        for (int i = 0; i < 36; i++) {
            if (strcmp(morse_letter, morse_text_letters[i]) == 0) {
                is_letter_exist = 1;
                break;
            }
        }
        if (!is_letter_exist) {
            return 0;
        }
        is_letter_exist = 0;

        morse_letter = strtok(NULL, " ");
    }
    return 1;
}


