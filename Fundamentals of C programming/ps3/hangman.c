#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>
#include "hangman.h"


int get_word(char secret[]){
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);

    return 0;
}

int is_word_guessed(const char secret[], const char letters_guessed[]) {
    int len = strlen(secret);
    int there_is = 0;
    for (int i = 0; i < len; i++) {
        for (int j = 0, num_of_letters = strlen(letters_guessed); j < num_of_letters; j++) {
            if (secret[i] == letters_guessed[j]) {
                there_is = 1;
                break;
            }
        }
        if (!there_is) {
            return 0;
        }
        there_is = 0;
    }
    return 1;
}

void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]) {
    int is_guessed = 0;
    int i = 0;
    for (int secret_len = strlen(secret);i < secret_len; i++) {
        for (int j = 0, num_of_leters = strlen(letters_guessed); j < num_of_leters; j++) {
            if (secret[i] == letters_guessed[j]) {
                guessed_word[i] = letters_guessed[j];
                is_guessed = 1;
                break;
            }
        }
        if (!is_guessed) {
            guessed_word[i] = '_';
        }
        is_guessed = 0;
    }
    guessed_word[i] = '\0';
}

void make_spaces (const char* guessed_word, char* guessed_word_with_spaces) {
    int count = 0;
    for (int i = 0, len = strlen(guessed_word); i < len; i++) {
        guessed_word_with_spaces[count++] = guessed_word[i];
        if (count == (len * 2) - 1 ) {
            guessed_word_with_spaces[count] = '\0';
            break;
        }
        guessed_word_with_spaces[count++] = ' ';
    }
    guessed_word_with_spaces[count] = '\0';
}

void get_available_letters(const char letters_guessed[], char available_letters[]) {
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    int is_used = 0;
    int count = 0;
    for (int i = 0, all_letters = strlen(alphabet);i < all_letters; i++) {
        for (int j = 0, num_of_guessed = strlen(letters_guessed);j < num_of_guessed; j++) {
            if (alphabet[i] == letters_guessed[j]) {
                is_used = 1;
                break;
            }
        }
        if (!is_used) {
            available_letters[count++] = alphabet[i];
        }
        is_used = 0;
    }
    available_letters[count] = '\0';
}

void prepare_text(char* text) {
    int text_len = strlen(text);
    for (int i = 0; i < text_len; i++) {
        if (isupper(text[i])) {
            text[i] = tolower(text[i]);
        }
    }
}

void hangman(const char secret[]) {
    int word_len = strlen(secret);

    puts("Welcome to the game, Hangman!");
    printf("I am thinking of a word that is %d letters long.\n", word_len);
    printf("-------------\n");

    int guesses_left = 8;
    char avaible_leters[30];
    char players_guess[20];
    char letters_guessed[30];
    char guessed_word[16];
    char guessed_word_with_spaces[32];
    get_guessed_word(secret, letters_guessed, guessed_word);
    make_spaces(guessed_word, guessed_word_with_spaces);

    while (guesses_left > 0) {
        if (is_word_guessed(secret, letters_guessed)) {
            printf("Congratulations, you won!\n");
            break;
        }
        printf("You have %d guesses left.\n", guesses_left);
        get_available_letters(letters_guessed, avaible_leters);
        printf("Available letters: %s\n", avaible_leters);
        printf("Please guess a letter: ");
        scanf("%19s", players_guess);
        prepare_text(players_guess);
        if (strlen(players_guess) > 1) {
            if(strcmp(players_guess, secret) == 0) {
                printf("Congratulations, you won!\n");
                break;
            } else {
                printf("Sorry, bad guess. The word was %s.", secret);
                break;
            }
        } else {
            if (isalpha(players_guess[0]) == 0) {
                make_spaces(guessed_word, guessed_word_with_spaces);
                printf("Oops! '%s' is not a valid letter: %s\n", players_guess, guessed_word_with_spaces);
                printf("-------------\n");
                continue;
            }
            strncat(letters_guessed, players_guess, 1);
            if (strpbrk(avaible_leters, players_guess) == NULL) {
                make_spaces(guessed_word, guessed_word_with_spaces);
                printf("Oops! You've already guessed that letter: %s\n", guessed_word_with_spaces);
            } else if (strpbrk(secret, players_guess) != NULL) {
                get_guessed_word(secret, letters_guessed, guessed_word);
                make_spaces(guessed_word, guessed_word_with_spaces);
                printf("Good guess: %s\n",  guessed_word_with_spaces);
            } else {
                make_spaces(guessed_word, guessed_word_with_spaces);
                printf("Oops! That letter is not in my word: %s\n", guessed_word_with_spaces);
                guesses_left--;
            }
        }
        printf("-------------\n");
    }
    if (guesses_left == 0) {
        printf("Sorry, you ran out of guesses. The word was %s.\n", secret);
    }
}

//int main () {
    //char output[30];
    //get_guessed_word("bombproof", "", output);
    //char output2[100];
    //make_spaces(output, output2);
    //int len = strlen(output);
    //printf("%d\n", len);
    //printf("%s", output);
  //  hangman("hui");
//}

