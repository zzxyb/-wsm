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

#include "wsm_log.h"
#include "wsm_common.h"

#include <time.h>
#include <ctype.h>
#include <string.h>

static const char whitespace[] = " \f\n\r\t\v";
static const long NSEC_PER_SEC = 1000000000;

void strip_whitespace(char *str) {
    size_t len = strlen(str);
    size_t start = strspn(str, whitespace);
    memmove(str, &str[start], len + 1 - start);

    if (*str) {
        for (len -= start + 1; isspace(str[len]); --len) {}
        str[len + 1] = '\0';
    }
}

char *vformat_str(const char *fmt, va_list args) {
    char *str = NULL;
    va_list args_copy;
    va_copy(args_copy, args);

    int len = vsnprintf(NULL, 0, fmt, args);
    if (len < 0) {
        wsm_log_errno(WSM_ERROR, "vsnprintf(\"%s\") failed", fmt);
        goto out;
    }

    str = malloc(len + 1);
    if (str == NULL) {
        wsm_log_errno(WSM_ERROR, "malloc() failed");
        goto out;
    }

    vsnprintf(str, len + 1, fmt, args_copy);

out:
    va_end(args_copy);
    return str;
}

char *format_str(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char *str = vformat_str(fmt, args);
    va_end(args);
    return str;
}

uint32_t get_current_time_msec(void) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec * 1000 + now.tv_nsec / 1000000;
}

char *lenient_strcat(char *dest, const char *src) {
    if (dest && src) {
        return strcat(dest, src);
    }
    return dest;
}

char *lenient_strncat(char *dest, const char *src, size_t len) {
    if (dest && src) {
        return strncat(dest, src, len);
    }
    return dest;
}

int lenient_strcmp(const char *a, const char *b) {
    if (a == b) {
        return 0;
    } else if (!a) {
        return -1;
    } else if (!b) {
        return 1;
    } else {
        return strcmp(a, b);
    }
}

void color_to_rgba(float dest[static 4], uint32_t color) {
    dest[0] = ((color >> 24) & 0xff) / 255.0;
    dest[1] = ((color >> 16) & 0xff) / 255.0;
    dest[2] = ((color >> 8) & 0xff) / 255.0;
    dest[3] = (color & 0xff) / 255.0;
}

char* int_to_string(int num) {
    int length = snprintf(NULL, 0, "%d", num);
    char *str = (char *)malloc((length + 1) * sizeof(char));
    if (str == NULL) {
        return NULL;
    }
    snprintf(str, length + 1, "%d", num);
    return str;
}

int64_t timespec_to_msec(const struct timespec *a) {
    return (int64_t)a->tv_sec * 1000 + a->tv_nsec / 1000000;
}

int64_t timespec_to_nsec(const struct timespec *a) {
    return (int64_t)a->tv_sec * NSEC_PER_SEC + a->tv_nsec;
}
