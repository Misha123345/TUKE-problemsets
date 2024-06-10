#include <stdio.h>
#include <math.h>

double find_k(int count, int time, int data[][2]) {
    double K = 2500;

    for (int i = 0; i < 5000; i++) {
        double sum = 0;
        int finded = 0;

        for (int j = 0; j < count; j++) {
            if (data[j][1] + K == 0) { finded = 1; break; }
            else sum += data[j][0] / (data[j][1] + K);
        }

        if (finded == 1 || sum >= time) break;
        else K--;
    }
    return K;
}

void read_data(int measurements_count, int data[][2]) {
    for (int i = 0; i < measurements_count; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%d", &data[i][j]);
        }
    }
}

double increase_precision(double K, int count, int time, int data[][2]) {
    double precision_mod = 0.1;
    double sum;

    for (int precision = 0; precision < 9; precision++) {
        for (int i = 0; i < 30; i++) {
            sum = 0;
            for (int j = 0; j < count; j++) sum += data[j][0] / (data[j][1] + K);

            if (sum <= time) break;
            else K += precision_mod;
        }

        if (sum < time) K -= precision_mod;
        else if (sum == time) break;
        else if (sum > time - precision_mod) K += precision_mod;

        precision_mod /= 10;
    }

    return K;
}

int main() {
    int count, time;
    int data[1000][2];

    scanf("%d %d", &count, &time);
    read_data(count, data);
    double K = find_k(count, time, data);
    K = increase_precision(K, count, time, data);

    printf("%0.9f\n", K);

    return 0;
}
