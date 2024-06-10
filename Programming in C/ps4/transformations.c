#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transformations.h"
#include "bmp.h"

struct bmp_image* flip_horizontally(const struct bmp_image* image) {
    if (image == NULL) return NULL;
    struct bmp_image* result = calloc(1, sizeof(struct bmp_image));
    result->data = calloc(image->header->height * image->header->width, sizeof(struct pixel));
    result->header = calloc(1, sizeof(struct bmp_header));
    memcpy(result->header, image->header, sizeof(struct bmp_header));

    for (int i = 0; i < image->header->height; i++) {
        for (int j = image->header->width - 1; j >= 0; j--) {
            result->data[(image->header->width * i) + (image->header->width - 1) - j] = image->data[(image->header->width * i) + j];
        }
    }
    
    return result;
}

struct bmp_image* flip_vertically(const struct bmp_image* image){
    if (image == NULL) return NULL;
    struct bmp_image* result = calloc(1, sizeof(struct bmp_image));
    result->data = calloc(image->header->height * image->header->width, sizeof(struct pixel));
    result->header = calloc(1, sizeof(struct bmp_header));
    memcpy(result->header, image->header, sizeof(struct bmp_header));
    
    for (int i = 0; i < image->header->width; i++) {
        for (int j = 0; j < image->header->height; j++) {
            result->data[i + (image->header->width * j)] = image->data[i + (image->header->width * (image->header->height - j - 1))];
        }
    }   
   
    return result;
}


struct bmp_image* rotate_left(const struct bmp_image* image){
    if (image == NULL) return NULL;
    struct bmp_image* result = calloc(1, sizeof(struct bmp_image));
    result->data = calloc(image->header->height * image->header->width, sizeof(struct pixel));
    result->header = calloc(1, sizeof(struct bmp_header));
    memcpy(result->header, image->header, sizeof(struct bmp_header));
    result->header->width = image->header->height; 
    result->header->height = image->header->width;
    int offset = (4 - ((sizeof(struct pixel) * result->header->width) % 4)) % 4;
    result->header->size = 54 + (result->header->width * result->header->height * 3) + (offset * result->header->height);
    //printf("%d\n",54 + (result->header->width * result->header->height * 3) + (offset * result->header->height));
    result->header->image_size = result->header->size - 54;
    
    for (int i = 0; i < image->header->height; i++) {
        for (int j = 0; j < image->header->width; j++) {
            result->data[(image->header->height * (image->header->width - 1 - j)) + i] = image->data[(image->header->width * (image->header->height - 1 - i) + (image->header->width - 1 - j))];
        }
    }

    return result;
}

struct bmp_image* rotate_right(const struct bmp_image* image){
    if (image == NULL) return NULL;
    struct bmp_image* result = calloc(1, sizeof(struct bmp_image));
    result->data = calloc(image->header->height * image->header->width, sizeof(struct pixel));
    result->header = calloc(1, sizeof(struct bmp_header));
    memcpy(result->header, image->header, sizeof(struct bmp_header));
    result->header->width = image->header->height;
    result->header->height = image->header->width;
    result->header->size = image->header->size;
    int offset = (4 - ((sizeof(struct pixel) * result->header->width) % 4)) % 4;
    result->header->size = 54 + (result->header->width * result->header->height * 3) + (offset * result->header->height);
    result->header->image_size = result->header->size - 54;
    //printf("%d\n",54 + (result->header->width * result->header->height * 3) + (offset * result->header->height));
 
    for (int i = 0; i < image->header->height; i++) {
        for (int j = 0; j < image->header->width; j++) {
            result->data[(image->header->height * (image->header->width - 1 - j)) + i] = image->data[j + (image->header->width * i)];
        }
    } 
    
    return result;
}

struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width){
    if (image == NULL) return NULL;
    if (start_x < 0 || start_x > image->header->width) return NULL;
    if (start_y < 0 || start_y > image->header->height) return NULL;
    if (width < 1 || width > image->header->width - start_x) return NULL;
    if (height < 1 || height > image->header->height - start_y) return NULL;
    
    struct bmp_image* result = calloc(1, sizeof(struct bmp_image));
    result->header = calloc(1, sizeof(struct bmp_header));
    memcpy(result->header, image->header, sizeof(struct bmp_header));
    int offset = (4 - ((sizeof(struct pixel) * width) % 4)) % 4;
    result->header->size = (width * height * sizeof(struct pixel)) + (offset * height) + sizeof(struct bmp_header);
    result->header->image_size = result->header->size - 54;
    result->header->width = width;
    result->header->height = height;
    result->data = calloc(width * height, sizeof(struct pixel));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {                       
            result->data[((height - 1 - i) * width) + j] = image->data[((image->header->height - 1 - i - start_y) * image->header->width) + start_x + j];
        }
    }

    return result;
}


struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep) {                                                                                                                                                   
    if (image == NULL || colors_to_keep == NULL) return NULL;
    int len = strlen(colors_to_keep);

    for (int i = 0; i < len; i++) if (!(colors_to_keep[i] == 'r' || colors_to_keep[i] == 'g' || colors_to_keep[i] == 'b')) return NULL;
    
    struct bmp_image* result = calloc(1, sizeof(struct bmp_image));
    result->header = calloc(1, sizeof(struct bmp_header));
    result->data = calloc(image->header->width * image->header->height, sizeof(struct pixel));
    memcpy(result->header, image->header, sizeof(struct bmp_header));
    memcpy(result->data, image->data, sizeof(struct pixel) * image->header->height * image->header->width);

    int red = 0, green = 0, blue = 0;
    for (int i = 0; i < len; i++) { 
        if (colors_to_keep[i] == 'r') red = 1;
        else if (colors_to_keep[i] == 'g') green = 1;
        else if (colors_to_keep[i] == 'b') blue = 1;
    }

    for (int i = 0; i < image->header->height * image->header->width; i++) {
        if (!red) result->data[i].red = 0;
        if (!green) result->data[i].green = 0;
        if (!blue) result->data[i].blue = 0;
    }

    return result;
}

struct bmp_image* scale(const struct bmp_image* image, float factor){
    if (image == NULL || factor < 0) return NULL;
    int new_width = round((float)image->header->width * factor);
    int new_height = round((float)image->header->height * factor);
    int offset = (4 - ((sizeof(struct pixel) * new_width) % 4)) % 4;

    struct bmp_image* result = calloc(1, sizeof(struct bmp_image));
    result->header = calloc(1, sizeof(struct bmp_header));
    result->data = calloc(new_width*new_height, sizeof(struct pixel));
    memcpy(result->header, image->header, sizeof(struct bmp_header));
    result->header->width = new_width;
    result->header->height = new_height;
    result->header->size = 54 + (new_height*new_width*sizeof(struct pixel)) + (offset*new_height);
    result->header->image_size = result->header->size - 54;
    
    struct pixel* temp = calloc(new_width*image->header->height, sizeof(struct pixel));

    for (int i = 0; i < image->header->height; i++) {
        for (int j = 0; j < new_width; j++) {
            //printf("temp[%d] = image->data[%d]\n", (new_width*i) + j, (i * image->header->width) + (int)floor((float)(j * image->header->width) / (float)new_width)); 
            temp[(new_width*i) + j] = image->data[(i * image->header->width) + (int)floor((float)(j * image->header->width) / (float)new_width)];
        }
    }

    for (int i = 0; i < new_width; i++) {
        for (int j = 0; j < new_height; j++) {
            //printf("result[%d] = temp[%d]\n", (new_width*j) + i, (((int)floor((float)(j * image->header->height) / (float)new_height)) * new_width) + i);
            result->data[(new_width*j) + i] = temp[(((int)floor((float)(j * image->header->height) / (float)new_height)) * new_width) + i];
        }
    }

    free(temp);

    return result;
}
