//
// Created by cpasjuste on 28/01/2020.
//

#ifndef LOADER_DRAWING_H
#define LOADER_DRAWING_H

#include <arch/types.h>

#define DRAW_PACK_COLOR(a, r, g, b) ( \
    a << 24 | \
    r << 16 | \
    g << 8 | \
    b << 0 )

typedef struct color_t {
    uint8 r;
    uint8 g;
    uint8 b;
    uint8 a;
} Color;

#define COL_WHITE       (Color) {255, 255, 255, 255}
#define COL_BLUE        (Color) {49, 121, 159, 255}
#define COL_BLUE_LIGHT  (Color) {178, 226, 249, 255}
#define COL_YELLOW      (Color) {240, 226, 107, 255}

void draw_init();

void draw_start();

void draw_end();

void draw_string(float x, float y, float z, Color color, char *str);

void draw_box(float x, float y, float w, float h, float z, Color color);

void draw_box_outline(float x, float y, float w, float h, float z, Color color, Color outline_color, float outline_size);

#endif //LOADER_DRAWING_H
