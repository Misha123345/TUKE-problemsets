#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "transformations.h"

int main(int argc, char* argv[]) {
    FILE* temp_file = fopen("./assets/lenna.bmp", "rb");
    FILE* write_to_h = fopen("./result_h.bmp", "w");
    FILE* write_to_v = fopen("./result_v.bmp", "w");
    FILE* write_to_l = fopen("./result_l.bmp", "w");
    FILE* write_to_r = fopen("./result_r.bmp", "w");
    FILE* write_to_c = fopen("./result_c.bmp", "w");
    FILE* write_to_e = fopen("./result_e.bmp", "w");
    FILE* write_to_s = fopen("./result_s.bmp", "w");
    struct bmp_image* image_bmp_test = read_bmp(temp_file);     


    struct bmp_image* croped = crop(image_bmp_test, 2, 0, 1, 1);
    struct bmp_image* scaled = scale(image_bmp_test, 0.01);
    struct bmp_image* extracted = extract(image_bmp_test, "rb");
    struct bmp_image* fliped_v = flip_vertically(image_bmp_test);
    struct bmp_image* fliped_h = flip_horizontally(image_bmp_test);
    struct bmp_image* turned_l = rotate_left(image_bmp_test);
    struct bmp_image* turned_r = rotate_right(image_bmp_test);
    write_bmp(write_to_h, fliped_h);
    write_bmp(write_to_v, fliped_v);
    write_bmp(write_to_l, turned_l);
    write_bmp(write_to_r, turned_r);
    write_bmp(write_to_c, croped);
    write_bmp(write_to_e, extracted);
    write_bmp(write_to_s, scaled);
    free_bmp_image(image_bmp_test);
    free_bmp_image(fliped_h);
    free_bmp_image(fliped_v);
    free_bmp_image(turned_l);
    free_bmp_image(turned_r);
    free_bmp_image(croped);
    free_bmp_image(extracted);
    free_bmp_image(scaled);
    fclose(write_to_v);
    fclose(write_to_h);
    fclose(write_to_l);
    fclose(write_to_r);
    fclose(write_to_c);
    fclose(write_to_e);
    fclose(write_to_s);
    fclose(temp_file);
    return 0;
}
