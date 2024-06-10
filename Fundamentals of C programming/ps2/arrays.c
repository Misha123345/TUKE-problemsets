#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float lift_a_car(const int stick_length, const int human_weight, const int car_weight) {
    return round(((float)(stick_length * human_weight) / ((float)human_weight + (float)car_weight)) * 100) / 100;
}

float unit_price(const float pack_price, const int rolls_count, const int pieces_count) {
    return round(((pack_price / (float)(rolls_count * pieces_count)) * 100) * 100) / 100;
}

int bank_notes(const int price) {
    return (price % 10 > 0) ? -1 : (price / 200) + ((price % 200) / 100) + ((price % 100) / 50) + ((price % 50) / 20) + (((price % 50) % 20) / 10);
}

int euler(const int n) {
    unsigned int result = n, i = 2, temp = n;
    if (n <= 2) {
        return 1;
    }
    while (n >= i) {
        if (temp % i == 0) {
            while (temp % i == 0) {
                temp /= i;
            }
            result = round(result * (1 - 1/(float)i));
            i++;
        } else {
            i++;
        }
    }
    return result;
}

int find_missing_number(const int n, const int arr[]){
    int temp = 0;
    int missing_number = 0;
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            if (arr[k] == i) {
                missing_number++;
                break;
            }
        }
        if (temp == missing_number) {
            return missing_number;
        } else {
            temp = missing_number;
        }
    }
    return temp;
}

unsigned long long int find_factorial(int x) {
    if (x == 0) return 1;
    return x * find_factorial(x - 1);
}

unsigned long long sum_squared(const int line) {
    unsigned long long int triangle_line[line + 1];
    unsigned long long int result = 0;
    for (int i = 0; i < line + 1; i++) {
        unsigned long long int line_factorial = find_factorial(line);
        unsigned long long int line_i_factorial = find_factorial(line - i);
        unsigned long long int i_factorial = find_factorial(i);

        triangle_line[i] = (line_factorial) / (i_factorial * line_i_factorial);
    }

    for (int i = 0; i < line + 1; i++) {
        result += triangle_line[i] * triangle_line[i];
    }

    return result;
}

int array_min(const int input_array[], const int array_size) {
    if (input_array == NULL) {
        return -1;
    }
    int min = input_array[0];
    for (int i = 1; i < array_size; i++) {
        if (input_array[i] < min) {
            min = input_array[i];
        }
    }
    return min;
}

int array_max(const int input_array[], const int array_size) {
    if (input_array == NULL) {
        return -1;
    }
    int max = input_array[0];
    for (int i = 1; i < array_size; i++) {
        if (input_array[i] > max) {
            max = input_array[i];
        }
    }
    return max;
}

int factorize_count(const int n) {
    int i = 2, temp = n, count = 0;
    while (n > i) {
        if (temp % i == 0) {
            while (temp % i == 0) {
                temp /= i;
            }
            i++;
            count++;
        } else {
            i++;
        }
    }
    if (count == 0) {
        count = 1;
    }
    return count;
}


void podium(const int n, int arr[]) {
        arr[1] = (n - (n % 3)) / 3 + ((n % 3 != 0) ? 2 : 1);
        arr[0] = (n - (n % 3)) / 3 + ((n % 3 != 0) ? 1 : 0);
        arr[2] = (n - (n % 3)) / 3 - ((n % 3 == 1) ? 2 : 1);
}

int main() {
    return 0;
}
