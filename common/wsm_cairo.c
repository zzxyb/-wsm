/*
MIT License

Copyright (c) 2024 YaoBing Xiao

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#define _POSIX_C_SOURCE 200809L
#include "wsm_cairo.h"

void cairo_set_source_u32(cairo_t *cairo, uint32_t color) {
    cairo_set_source_rgba(cairo,
                          (color >> (3*8) & 0xFF) / 255.0,
                          (color >> (2*8) & 0xFF) / 255.0,
                          (color >> (1*8) & 0xFF) / 255.0,
                          (color >> (0*8) & 0xFF) / 255.0);
}

cairo_subpixel_order_t to_cairo_subpixel_order(enum wl_output_subpixel subpixel) {
    switch (subpixel) {
    case WL_OUTPUT_SUBPIXEL_HORIZONTAL_RGB:
        return CAIRO_SUBPIXEL_ORDER_RGB;
    case WL_OUTPUT_SUBPIXEL_HORIZONTAL_BGR:
        return CAIRO_SUBPIXEL_ORDER_BGR;
    case WL_OUTPUT_SUBPIXEL_VERTICAL_RGB:
        return CAIRO_SUBPIXEL_ORDER_VRGB;
    case WL_OUTPUT_SUBPIXEL_VERTICAL_BGR:
        return CAIRO_SUBPIXEL_ORDER_VBGR;
    default:
        return CAIRO_SUBPIXEL_ORDER_DEFAULT;
    }
    return CAIRO_SUBPIXEL_ORDER_DEFAULT;
}

cairo_surface_t *cairo_image_surface_scale(cairo_surface_t *image,
                                           int width, int height) {
    int image_width = cairo_image_surface_get_width(image);
    int image_height = cairo_image_surface_get_height(image);

    cairo_surface_t *new =
        cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cairo_t *cairo = cairo_create(new);
    cairo_scale(cairo, (double)width / image_width,
                (double)height / image_height);
    cairo_set_source_surface(cairo, image, 0, 0);

    cairo_paint(cairo);
    cairo_destroy(cairo);
    return new;
}
