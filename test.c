/**
 * MIT License (MIT)
 *
 * Copyright (c) 2015 Zhiyuan Wang
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "string_buffer.h"

static
void test_new_delete()
{
    StringBuffer *sb = string_buffer_new();
    string_buffer_delete(sb);
    string_buffer_delete(NULL);
}

static
void test_append()
{
    int ret;
    StringBuffer *sb;
    sb = string_buffer_new();
    ret = string_buffer_append(sb, "123456");
    assert(ret == 6);
    ret = string_buffer_append(sb, "123456");
    assert(string_buffer_length(sb) == 12);
    assert(strcmp(string_buffer_get_string(sb), "123456123456") == 0);
    string_buffer_delete(sb);
}

static
void test_append_n()
{
    int ret;
    StringBuffer *sb;
    sb = string_buffer_new();
    ret = string_buffer_append_n(sb, "123456", 4);
    assert(ret == 4);
    string_buffer_append_n(sb, "56999", 2);
    assert(string_buffer_length(sb) == 6);
    assert(strcmp(string_buffer_get_string(sb), "123456") == 0);
    string_buffer_delete(sb);
}

static
void test_appendf()
{
    int ret;
    StringBuffer *sb;
    sb = string_buffer_new();
    ret = string_buffer_appendf(sb, "%05d", 1);
    assert(ret == 5);
    assert(strcmp(string_buffer_get_string(sb), "00001") == 0);
    string_buffer_appendf(sb, "%s", "hello");
    assert(string_buffer_length(sb) == 10);
    assert(strcmp(string_buffer_get_string(sb), "00001hello") == 0);
    string_buffer_delete(sb);
}

static
void test_append_set()
{
    int ret;
    StringBuffer *sb;
    sb = string_buffer_new();
    ret = string_buffer_append_set(sb, ' ', 5);
    assert(ret == 5);
    assert(string_buffer_length(sb) == 5);
    string_buffer_append_set(sb, 'a', 5);
    assert(string_buffer_length(sb) == 10);
    assert(strcmp(string_buffer_get_string(sb), "     aaaaa") == 0);
    string_buffer_delete(sb);
}

static
void test_clear()
{
    StringBuffer *sb;
    sb = string_buffer_new();
    string_buffer_append(sb, "123456");
    string_buffer_clear(sb);
    assert(string_buffer_length(sb) == 0);
    assert(strcmp(string_buffer_get_string(sb), "") == 0);
    string_buffer_delete(sb);
}

static
void test_buffer()
{
    int ret = 0;
    char data[10240 + 1];
    StringBuffer *sb = NULL;

    sb = string_buffer_new();

    for (int i = 0; i < sizeof(data); ++i) {
        memset(data, '1', i);
        data[i] = '\0';
        ret = string_buffer_append(sb, data);
        assert(string_buffer_length(sb) == i);
        assert(strcmp(string_buffer_get_string(sb), data) == 0);
        assert(string_buffer_capacity(sb) == (i / 512 + 1) * 512 - 1);

        string_buffer_clear(sb);
    }
    string_buffer_delete(sb);
}

int main(int argc, char const *argv[])
{
    test_new_delete();
    test_append();
    test_append_n();
    test_appendf();
    test_append_set();
    test_clear();
    test_buffer();
    printf("test ok\n");
    return 0;
}