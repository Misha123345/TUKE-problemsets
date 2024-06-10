#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bmp.h"

char* reverse(const char* string);
void str_to_up(char* text);
char* vigenere_encrypt(const char* key, const char* text);
char* vigenere_decrypt(const char* key, const char* text);
int check_key(const char* key);
unsigned char* bit_encrypt(const char* text);
char* bit_decrypt(const unsigned char* text);
void find_bits(char symbol, char* byts);
char get_symbol(char bits[8]);
unsigned char* bmp_encrypt(const char* key, const char* text);
char* bmp_decrypt(const char* key, const unsigned char* text);

/*int main() {
    
    unsigned char* bmp_encrypted = bmp_encrypt("iuoafaee", "jjjaaa");
    printf("|%s|\n", bmp_encrypted);
    char* bmp_decrypted = bmp_decrypt("iuoafaee", bmp_encrypted);
    printf("|%s|\n", bmp_decrypted);

    char bits[9];
    find_bits('N', bits);
    printf("|%c|\n", get_symbol("01001101"));


    char* reversed = reverse("");
    free(reversed);

    char* vigenere_encrypted = vigenere_encrypt("CoMPuTeR", "Hello World!");
    char* vigenere_decrypted = vigenere_decrypt("CoMPuTeR", vigenere_encrypted);
    free(vigenere_decrypted);
    free(vigenere_encrypted);
}*/

unsigned char* bmp_encrypt(const char* key, const char* text){
    char* result = reverse(text);
    if (result == NULL) return NULL;

    char* temp = vigenere_encrypt(key, result);
    free(result);
    if (temp == NULL) return NULL;

    unsigned char* bit_temp = bit_encrypt(temp);
    free(temp);
    if (bit_temp == NULL) return NULL;

    return bit_temp;
}

char* bmp_decrypt(const char* key, const unsigned char* text){
    char* result = bit_decrypt(text);
    if (result == NULL) return NULL;

    char* temp = vigenere_decrypt(key, result);
    free(result);
    if (temp == NULL) return NULL;

    char* reverse_temp = reverse(temp);
    free(temp);
    if (reverse_temp == NULL) return NULL;
    
    return reverse_temp;
}

char* reverse(const char* string) {
    if (string == NULL) return NULL;
    size_t len = strlen(string);
    char* result = (char*) calloc(len + 1, sizeof(char));

    int i = 0;
    for ( ; string[i]; i++) result[i] = string[len - 1 - i];
    result[i] = '\0';

    str_to_up(result);

    return result;
}

void str_to_up(char* text) {
    for (int i = 0; text[i]; i++) text[i] = toupper(text[i]);
}

char* vigenere_encrypt(const char* key, const char* text) {
    if (key == NULL || text == NULL || !strcmp("", key) || !strcmp("", text)) return NULL;
    size_t len = strlen(text), key_len = strlen(key);
    char* result = (char*) calloc(len + 1, sizeof(char));
    strcpy(result, text);
    str_to_up(result);

    //prepare key
    char key_copy[key_len + 1]; strcpy(key_copy, key); str_to_up(key_copy);
    if (check_key(key_copy)) {
        free(result);
        return NULL;
    }

    char letter;
    for (int i = 0, count = 0; result[i]; i++) {
        if (result[i] >= 65 && result[i] <= 90) { 
            letter = result[i] + (key_copy[count++] - 'A');
            if (count == key_len) count = 0;
            if (letter > 90) letter = 'A' + (letter - 91);
            result[i] = letter;
        }
    }
    
    return result;
}

int check_key(const char* key) {
    for (int i = 0; key[i]; i++) if (key[i] < 'A' || key[i] > 'Z') return 1;
    return 0;
}

char* vigenere_decrypt(const char* key, const char* text) {
    if (key == NULL || text == NULL || !strcmp("", key) || !strcmp("", text)) return NULL;
    size_t len = strlen(text), key_len = strlen(key);
    char* result = (char*) calloc(len + 1, sizeof(char));
    strcpy(result, text);
    str_to_up(result);

    //prepare key
    char key_copy[key_len + 1]; strcpy(key_copy, key); str_to_up(key_copy);
    if (check_key(key_copy)) {
        free(result);
        return NULL;
    }
    
    char letter;
    for (int i = 0, count = 0; result[i]; i++) {
        if (result[i] >= 65 && result[i] <= 90) { 
            letter = result[i] - (key_copy[count++] - 'A');
            if (count == key_len) count = 0;
            if (letter < 65) letter = 'Z' - (abs(letter - 64));
            result[i] = letter;
        }
    }
    
    return result;
}
    
unsigned char* bit_encrypt(const char* text) {
    if (text == NULL || !strcmp(text, "")) return NULL;
    unsigned char* result = (unsigned char*) calloc(strlen(text) + 1, sizeof(char));

    char bits[9];
    int i = 0;
    
    char temp;
    for ( ; text[i]; i++) {
        find_bits(text[i], bits);
        temp = bits[0]; bits[0] = bits[1]; bits[1] = temp;
        temp = bits[2]; bits[2] = bits[3]; bits[3] = temp;
        for (int j = 4; j < 8; j++) {
            bits[j] = (bits[j - 4] == bits[j]) ? '0' : '1';
        }
        
        result[i] = get_symbol(bits);
    }

    return result;
}

char* bit_decrypt(const unsigned char* text) {
    if (text == NULL || !strcmp((char*)text, "")) return NULL;
    char* result = (char*) calloc(strlen((char*)text) + 1, sizeof(char));

    char bits[9];
    int i = 0;
    
    char temp;
    for ( ; text[i]; i++) {
        find_bits(text[i], bits);
        for (int j = 4; j < 8; j++) {
            bits[j] = (bits[j - 4] == bits[j]) ? '0' : '1';
        }

        temp = bits[0]; bits[0] = bits[1]; bits[1] = temp;
        temp = bits[2]; bits[2] = bits[3]; bits[3] = temp;
        
        result[i] = get_symbol(bits);
    }

    return result;
}

void find_bits(char symbol, char* bits) {
    for (int i = 0; i < 8; i++) {
        bits[i] = '0' + ((symbol >> (7 - i)) & 1);
    }
    bits[8] = '\0';
}

char get_symbol(char bits[8]) {
    char result = '\0';
    for (int i = 0; i < 8; i++) {
        result += (bits[7 - i] - '0') * (1 << i); 
    }
    return result;
}


