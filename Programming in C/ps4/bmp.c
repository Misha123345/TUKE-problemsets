#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

struct bmp_header* read_bmp_header(FILE* stream) {
    if (stream == NULL) return NULL;
    rewind(stream);
    struct bmp_header* res = calloc(1, sizeof(struct bmp_header));
    fread(res, sizeof(struct bmp_header), 1, stream);
    if (res->type != 0x4d42) { free(res); return NULL; }
    return res;
}

struct pixel* read_data(FILE* stream, const struct bmp_header* header) {
    if (stream == NULL || header == NULL) return NULL;
    struct pixel* res = calloc(header->width * header->height ,sizeof(struct pixel));
    rewind(stream);
    fseek(stream, header->offset, SEEK_SET);
    int offset = (4 - ((sizeof(struct pixel) * header->width) % 4)) % 4;
    int i = 0;
    while (fread(&res[i], sizeof(res[0]), 1, stream) != 0) {
        if (i % header->width == header->width - 1) fseek(stream, offset, SEEK_CUR);
        i++;
    }
    return res;
}

struct bmp_image* read_bmp(FILE* stream) {
    if (stream == NULL) return NULL;
    
    struct bmp_header* header = read_bmp_header(stream);
    if (header == NULL) {
        fprintf(stderr, "Error: This is not a BMP file.\n");
        return NULL;
    }

    struct pixel* pixel_map = read_data(stream, header);
    if (pixel_map == NULL) {
        free(header);
        fprintf(stderr, "Error: Corrupted BMP file.\n");
        return NULL;
    }

    struct bmp_image* image = calloc(1, sizeof(struct bmp_image));
    image->header = header;
    image->data = pixel_map;

    return image;
}

bool write_bmp(FILE* stream, const struct bmp_image* image) {
    if (stream == NULL || image == NULL) return false;
    int offset = (4 - ((sizeof(struct pixel) * image->header->width) % 4)) % 4;
    
    fwrite(image->header, sizeof(struct bmp_header), 1, stream);
    for (int i = 0; i < image->header->height; i++) {
        for (int j = 0; j < image->header->width; j++) {
            fwrite(&image->data[(image->header->width * i) + j], sizeof(struct pixel), 1, stream);
        }
        fwrite("\0", offset, sizeof(char), stream);
    }   

    return true;
}

void free_bmp_image(struct bmp_image* image) {
    if (image != NULL) {
        free(image->data);
        free(image->header);
        free(image);
    }
}
