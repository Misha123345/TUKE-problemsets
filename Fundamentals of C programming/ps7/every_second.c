#include <stdio.h>
#include <string.h>

int compare_words(char* first_word, char* second_word, int words_length) {
    for (int i = 0; i < words_length; i++) {
        if (first_word[i] != second_word[i]) return 0;
    }
    return 1;
}

void copy_word(char* to, char* from) {
    while (*from) *to++ = *from++;
    *to = '\0';
}

void get_word(FILE* text, char* word) {
    char symbol = fgetc(text);
    while (symbol == ' ') symbol = fgetc(text);

    do {
        if (symbol != EOF) *word++ = symbol;
        else break;
    } while ((symbol = fgetc(text)) != ' ');

    *word = '\0';
}

void append_str_to_file(char* output_name, char* current_word, char* next_word, char* next_next_word) {
    FILE* output = fopen(output_name, "a");
    while (*current_word) {
        fputc(*current_word++, output);
    }
    if (!compare_words("STOP", next_word, 4) && !compare_words("STOP", next_next_word, 4)) {
        fputc(' ', output);
    }
    fclose(output);
}


void find_every_second_word(FILE* text, char* output_name) {
    char current_word[30];
    char next_word[30];
    char next_next_word[30];
    int is_second = 0;

    get_word(text, current_word);
    get_word(text, next_word);
    get_word(text, next_next_word);

    while (*current_word != '\0') {
        if (compare_words("STOP", current_word, 4)) break;

        if (is_second == 0) {
            is_second = 1;
        } else {
            append_str_to_file(output_name, current_word, next_word, next_next_word);
            is_second = 0;
        }
        copy_word(current_word, next_word);
        copy_word(next_word, next_next_word);
        get_word(text, next_next_word);
    }
}

int main (int argc, char* argv[]) {
    char word[30];
    if (argv[1] == 0|| argv[2] == 0) return -1;

    FILE* output = fopen(argv[2], "w");
    fclose(output);

    FILE* text = fopen(argv[1], "r");
    if (text == NULL) return -1;

    while (1) {
        get_word(text, word);
        if (compare_words("START", word, 5)) {
            find_every_second_word(text, argv[2]);
            break;
        }
        if (!(*word)) break;
    }

    fclose(text);

    return 0;
}
