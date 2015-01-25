#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "string_buffer.h"


#define STEP_LENGTH    512

#define EXPAND_BUFFER(self, n) \
    if (expand_buffer(self, (n))) { \
        return -1; \
    } \


struct StringBuffer {
    size_t length;
    size_t capacity;
    char  *buf;
};


static
int expand_buffer(StringBuffer *self, size_t min)
{
    char *new_buf = NULL;
    size_t new_capacity = 0;

    min = min + 1 - (self->capacity - self->length);
    if (min <= 0) return 0;

    new_capacity = self->capacity + (min / STEP_LENGTH + 1) * STEP_LENGTH;
    new_buf = realloc(self->buf, new_capacity);
    if (new_buf != NULL) {
        self->buf = new_buf;
        memset(self->buf + self->capacity, 0, new_capacity - self->capacity);
        self->capacity = new_capacity;
        return 0;
    } else {
        return -1;
    }
}

StringBuffer *string_buffer_new()
{
    StringBuffer *self = NULL;

    self = calloc(1, sizeof(*self));
    if (self != NULL) {
        self->buf = calloc(1, STEP_LENGTH);
        if (self->buf != NULL) {
            self->capacity = STEP_LENGTH;
        } else {
            free(self);
            self = NULL;
        }
    }
    return self;
}

void string_buffer_delete(StringBuffer *self)
{
    if (self) {
        if (self->buf) {
            free(self->buf);
        }
        free(self);
    }
}

size_t string_buffer_length(StringBuffer *self)
{
    return self ? self->length : 0;
}

size_t string_buffer_capacity(StringBuffer *self)
{
    return self ? (self->capacity - 1) : 0;
}

char *string_buffer_get_string(StringBuffer *self)
{
    return self ? self->buf : NULL;
}

void string_buffer_clear(StringBuffer *self)
{
    if (self != NULL) {
        memset(self->buf, 0, self->length);
        self->length = 0;
    }
}

int string_buffer_append(StringBuffer *self, const char *str)
{
    return string_buffer_append_n(self, str, strlen(str));
}

int string_buffer_append_n(StringBuffer *self, const char *str, size_t n)
{
    if (self == NULL) return -1;

    EXPAND_BUFFER(self, n);
    memcpy(self->buf + self->length, str, n);
    self->length += n;
    self->buf[self->length] = '\0';
    return n;
}

int string_buffer_appendf(StringBuffer *self, const char *format, ...)
{
    size_t n = 0;
    int ret = 0;
    va_list args;

    if (self == NULL) return -1;

    while (1) {
        n = self->capacity - self->length;
        va_start(args, format);
        ret = vsnprintf(self->buf + self->length, n, format, args);
        va_end(args);

        if (ret >= 0 && ret < n) {
            self->length += ret;
            return ret;
        } else if (ret < 0) {
            // error
            return ret;
        } else {
            // no enough space in buffer
            if (expand_buffer(self, ret - n)) {
                // expand failed
                return -1;
            }
        }
    }
    return ret;
}

int string_buffer_append_set(StringBuffer *self, int value, size_t num)
{
    if (self == NULL) return -1;

    EXPAND_BUFFER(self, num);

    memset(self->buf + self->length, value, num);
    self->length += num;
    self->buf[self->length] = '\0';
    return num;
}
