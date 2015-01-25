# StringBuffer
C string buffer

# Example
```
StringBuffer *sb = string_buffer_new();

string_buffer_append(sb, "hello");
string_buffer_append_n(sb, "123456", 3);
string_buffer_appendf(sb, "%08d", 10);
string_buffer_append_set(sb, 'A', 4);

printf("%s\n", string_buffer_get_string(sb));
// hello12300000010AAAA

string_buffer_delete(sb);
```