#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "playfair.h"

char* playfair_encrypt(const char* key, const char* text);
void str_to_upper(char* string);
void delete_repeatings(char* string);
void init_matrix(char matrix[5][5], char* key);
char* prepare_alphabet(const char* alpha, const char* key);
char* init_text(const char* text);
void find_in_matrix(const char matrix[5][5], char symbol, int* x, int* y);
void insert(char* array, int pos);
void delete_w(char* text);
char* playfair_decrypt(const char* key, const char* text);
int check_w(const char* text);
void delete_spaces(char* text);
int check_arguments(const char* text, const int check_spaces);
int make_pairs(char* text);

/*int main () {
    char* encrypted = playfair_encrypt("Potom vzala svoj prsten na dvoje ho rozlomila a jednu polovicu jemu dala", "Ako lev zbadal ze pan zle chodi a len tak sa potkyna volkynevolky prevalil pana na zem hlavu panovi odtrhol zelinkou potrel a teraz ju uz dobre postavil ktora sa hned prirastla");
    puts(encrypted);
    char* decrypted = playfair_decrypt("Potom vzala svoj prsten na dvoje ho rozlomila a jednu polovicu jemu dala", encrypted);
    puts(decrypted);

    if (encrypted != NULL) free(encrypted);
    else puts("Pica encrypted");
    
    if (decrypted != NULL) free(decrypted);
    else puts("Pica decrypted");
}*/

char* playfair_encrypt(const char* key, const char* text) {
    if (key == NULL || text == NULL || !strcmp(key, "") || !strcmp(text, "")) return NULL;
    char* prepared_alpha = prepare_alphabet(ALPHA, key);
    if (prepared_alpha == NULL) return NULL;
    char* container = init_text(text);
    if (container == NULL) return NULL;
    
    char matrix[5][5] = {0};

    
    init_matrix(matrix, prepared_alpha);
    free(prepared_alpha);
    
    /*for (int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }*/

    int first_x, first_y, second_x, second_y;

    char* result = (char*) calloc(strlen(container) + (strlen(container) / 2) + 2, sizeof(char));
  
    int count = 0;
    for (int i = 0; container[i]; i+=2) {
        find_in_matrix(matrix, container[i], &first_x, &first_y);
        find_in_matrix(matrix, container[i+1], &second_x, &second_y);

        if (first_y == second_y) {
            result[count++] = matrix[(first_x + 1 == 5) ? 0 : first_x + 1][first_y];
            result[count++] =matrix[(second_x + 1 == 5) ? 0 : second_x + 1][second_y]; 
        } else if (first_x == second_x) {
            result[count++] = matrix[first_x][(first_y + 1 == 5) ? 0 : first_y + 1];
            result[count++] = matrix[second_x][(second_y + 1 == 5) ? 0 : second_y + 1]; 
        } else {
            result[count++] = matrix[first_x][second_y];
            result[count++] = matrix[second_x][first_y]; 
        }
        
        if (container[i + 2] != '\0') result[count++] = ' ';
    }
    result[count] = '\0';

    free(container);

    return result;
}

void str_to_upper(char* string) {
    for (int i = 0; string[i]; i++) {
        string[i] = toupper(string[i]);
    }
}

void delete_repeatings(char* string) {
    int count = 0;
    int str_len = strlen(string);
    char result[str_len + 1];
    memset(result, 0, str_len * sizeof(char));
    int flag = 1;

    for (int i = 0; i < str_len; i++) {
        for (int j = 0; j < str_len; j++) {
            if (string[i] == result[j]) { flag = 0; break; }
        }
        if (flag) result[count++] = string[i];
        flag = 1;
    }
    result[count] = '\0';

    strcpy(string, result);
}

void init_matrix(char matrix[5][5], char* prepared_alpha) {
    int count = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = prepared_alpha[count++];
        }
    }
}

char* prepare_alphabet(const char* alpha, const char* key) {
    int len = strlen(key);
    char key_copy[len + 1]; 
    strcpy(key_copy, key);
    str_to_upper(key_copy);
    delete_spaces(key_copy);
    if (!strcmp("", key_copy)) return NULL;
    delete_repeatings(key_copy);
    delete_w(key_copy);
    if (check_arguments(key_copy, 0)) return NULL;

    char* prepared = (char*) calloc(26 + len + 1, sizeof(char));
    strcpy(prepared, key_copy);

    int i = 0;
    while(prepared[i] != '\0') i++;

    for (int j = 0; ALPHA[j]; j++) {
        prepared[i++] = ALPHA[j];
    }
    prepared[i] = '\0';

    delete_repeatings(prepared);

    return prepared;
}

char* init_text(const char* text) { 
    int res_len = strlen(text);
    char* result = (char*) calloc(res_len + 2, sizeof(char));
    char temp_check[res_len+1]; strcpy(temp_check, text); delete_spaces(temp_check);
    if (!strcmp("", temp_check)) { free(result); return NULL; }
    strcpy(result, text);
    str_to_upper(result);
    delete_w(result);
    //printf("unprepared res: %s\n", result);

    if (check_arguments(result, 0)) {
        free(result);    
        return NULL;
    }

    delete_spaces(result);
    
    char* temp;
    for (int i = 0; result[i]; ) {
        if (result[i] == result[i+1] && result[i] != 'X') {
            temp = (char*) realloc(result, strlen(result) + 2);
            if (temp != NULL) { result = temp; }
            insert(result, i+1);
        }

        if (result[i + 1] != '\0') i+=2;
        else break;
    }

    res_len = strlen(result);
    if (strlen(result) % 2 != 0) {
        temp = (char*) realloc(result, strlen(result) + 3);
        if (temp != NULL) result = temp;
        result[res_len] = 'X';
        result[res_len + 1] = '\0';
    }     

    return result;
}

void find_in_matrix(const char matrix[5][5], char symbol, int* x, int* y){
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == symbol) { *x = i, *y = j; return; }
        }
    }
}

void insert(char* array, int pos) {
    char temp, current = 'X';
    
    int i = pos, len = strlen(array) + 1;

    for (; i < len; i++) {
        temp = array[i];
        array[i] = current;
        current = temp;
    }
    array[i] = '\0';
}

void delete_w(char* text){
    for (int i = 0; text[i]; i++) {
        if (text[i] == 'W') text[i] = 'V';
    }
}

char* playfair_decrypt(const char* key, const char* text) {
    if (key == NULL || text == NULL || !strcmp(key, "") || !strcmp(text, "")) return NULL;
    if (check_w(text)) return NULL;
    if (check_arguments(text, 0)) return NULL;
    
    char* decrypted = (char*) calloc(strlen(text) + 2, sizeof(char));
    strcpy(decrypted, text);

    delete_spaces(decrypted);

    char* prepared_alpha = prepare_alphabet(ALPHA, key);
    if (prepared_alpha == NULL) {
        free(decrypted);
        return NULL;
    }

    char matrix[5][5] = {0};
    
    init_matrix(matrix, prepared_alpha);
    free(prepared_alpha);

    int first_x, first_y, second_x, second_y;
    
    for (int i = 0; decrypted[i]; i+=2) {
        find_in_matrix(matrix, decrypted[i], &first_x, &first_y);
        find_in_matrix(matrix, decrypted[i+1], &second_x, &second_y);

        if (first_y == second_y) {
            decrypted[i] = matrix[(first_x - 1 == -1) ? 4 : first_x - 1][first_y];
            decrypted[i+1] =matrix[(second_x - 1 == -1) ? 4 : second_x - 1][second_y]; 
        } else if (first_x == second_x) {
            decrypted[i] = matrix[first_x][(first_y - 1 == -1) ? 4 : first_y - 1];
            decrypted[i+1] = matrix[second_x][(second_y - 1 == -1) ? 4 : second_y - 1]; 
        } else{
            decrypted[i] = matrix[first_x][second_y];
            if (i+1 != 0)
            decrypted[i+1] = matrix[second_x][first_y]; 
        }   
    }


    return decrypted;
}

int check_w(const char* text) {
    for (int i = 0; text[i]; i++) if (text[i] == 'W') return 1;
    return 0;
}

void delete_spaces(char* text) {
    int count = 0;
    for (int i = 0; text[i]; i++) {
        if (text[i] != ' ') text[count++] = text[i];
    }
    text[count] = '\0';
}

int check_arguments(const char* text, const int check_spaces) {
    for (int i = 0; text[i]; i++) { 
        if (text[i] == ' ' && check_spaces) return 1;
        if ((text[i] < 'A' || text[i] > 'Z') && text[i] != ' ') return 1;
    }
    return 0;
}
