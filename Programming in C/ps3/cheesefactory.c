#include <stdio.h>
#include <math.h>

int main() {
    int holes, slices;
    scanf("%d %d", &holes, &slices);

    double spheres[holes][4];
    for (int i = 0; i < holes; i++) {
        for (int j = 0; j < 4; j++) {
            scanf("%lf", &spheres[i][j]);
        }
    }

    if (holes == 0) {
        double slice = 100. / (double)slices;
        for (int i = 0; i < slices; i++) {
            printf("%lf\n", slice);
        }
    }
    
}
