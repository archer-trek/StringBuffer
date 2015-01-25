/**
 * MIT License (MIT)
 *
 * Copyright (c) 2015 Zhiyuan Wang
 */

#ifndef _STRING_BUFFER_H_
#define _STRING_BUFFER_H_

/**
 * A buffer of C string.
 */
typedef struct StringBuffer StringBuffer;

/**
 * Create a new buffer initialized to zero, return NULL if fail.
 */
extern StringBuffer *string_buffer_new();

/**
 * Delete a StringBuffer.
 */
extern void string_buffer_delete(StringBuffer *self);

/**
 * Get length of data in the buffer.
 */
extern size_t string_buffer_length(StringBuffer *self);

/**
 * Get capacity of the buffer.
 */
extern size_t string_buffer_capacity(StringBuffer *self);

/**
 * Get the string.
 */
extern char *string_buffer_get_string(StringBuffer *self);

/**
 * Clear all data in the buffer.
 */
extern void string_buffer_clear(StringBuffer *self);

/**
 * Add string to the buffer.
 * Return length of str on success, -1 on failure.
 */
extern int string_buffer_append(StringBuffer *self, const char *str);

/**
 * Add the first n bytes of str to the buffer.
 * Return n on success, -1 on failure.
 */
extern int string_buffer_append_n(StringBuffer *self, const char *str, size_t n);

/**
 * Add data to the buffer, the format specifier is the same with printf.
 * Return value is the number of characters that has been written to the buffer,
 * not counting the terminating null character.
 */
extern int string_buffer_appendf(StringBuffer *self, const char *format, ...);

/**
 * Sets the n bytes of the tail of buffer to the specified value.
 * Return n on sucess, -1 on failure.
 */
extern int string_buffer_append_set(StringBuffer *self, int value, size_t n);

#endif