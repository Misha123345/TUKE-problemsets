#include <stdio.h>

char to_small(char letter) {
    if (letter < 65 || letter > 90) return letter;
    return letter + 32;
}

int to_pow(int number, int pow) {
    int res = 1;
    for (int i = 0; i  < pow; i++) res *= number;
    return res;
}

int compare_words(FILE* text ,char* first_word, char* symbol, int words_length) {
    for (int i = 0; i < words_length; i++) {
        if (to_small(first_word[i]) != to_small(*symbol)) {
            *symbol = (*symbol == 'a' || *symbol == 'A') ? *symbol : fgetc(text);
            return 0;
        }
        *symbol = fgetc(text);
    }
    return 1;
}

int find_number_size(int number) {
    int size = 0;
    for (int i = 0; i < 10; i++) {
        if (number / to_pow(10, i) != 0) size++;
    }
    return (size == 0) ? 1 : size;
}

void write_number_to_file(FILE* text, int number) {
    int size = find_number_size(number);
    char numbers[size];
    for (int i = 0; i < size - 1; i++) {
        numbers[i] = '0' + (number / to_pow(10, (size - i - 1)));
    }
    numbers[size - 1] = '0' + number % 10;

    for (int i = 0; i < size; i++) {
        fputc(numbers[i], text);
    }
}

int main (int argc, char* argv[]) {
    int count = 0;
    int word_length = 6;
    char symbol;
    char searched_word[] = "ananas";

    if (argv[1] == 0) {
        return 1;
    }

    FILE* text = fopen(argv[1], "r");


    if (text == NULL) {
        return 1;
    }

    symbol = fgetc(text);

    while (symbol != EOF) {
        count += compare_words(text, searched_word, &symbol, word_length);
    }

    fclose(text);

    text = fopen(argv[1], "w");
    write_number_to_file(text, count);
    fclose(text);
}
