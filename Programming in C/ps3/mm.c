#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int mm(char* number);

int main() {
    char number[110000];

    fgets(number, 110000, stdin);
    number[strlen(number) - 1] = '\0';

    printf("%d\n", mm(number));
}

int mm(char* number) {
    int result = 0;
    char temp[20] = {0};

    for (int i = 0, len = strlen(number); i < len; i++) result += number[i] - '0';
    if (result < 10) return result;
    sprintf(temp, "%d", result);

    return mm(temp);
}   
