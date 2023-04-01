//
// Created by Stefan on 04/03/2023.
//

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "table.h"

column* create_column(char* name,
                      enum data_type type,
                      uint8_t size) {

    column* col = calloc(1, sizeof(column));
    strcpy(col->name, name);
    col->type = type;
    col->size = size;

    return col;
}

void destroy_column(column* col) {
    free(col);
}

column** create_columns(column* args, ...) {
    uint8_t sz = args->size;
    column** cols = calloc(1, sizeof(column) * sz);
    va_list ap;
    va_start(ap, args);
    cols[0] = args;
    for(int i = 1; i < sz; i++) {
        cols[i] = va_arg(ap, column*);
    }
    va_end(ap);
    return cols;
}

table* create_table(char* name,
                    uint8_t num_columns,
                    column** cols) {
    table* tb = calloc(1, sizeof(table));
    strcpy(tb->name, name);
    tb->num_columns = num_columns;
    tb->columns = cols;
    tb->num_rows = 0;
}

table destroy_table(table* tb) {
    free(tb->columns);
    free(tb);
}

record* create_record(table* tb) {
    uint32_t sz = get_columns_size(tb);

    uint8_t* data = calloc(1, sz);
    record* r = calloc(1, sizeof(record));
    r->data = data;
}


void destroy_record(record* r) {
    free(r->data);
    free(r);
}

uint32_t get_columns_size(table* tb){
    uint32_t sz = 0;
    for (int i = 0; i < tb->num_columns; i++) {
        sz += tb->columns[i]->size;
    }
    return sz;
}

uint32_t get_record_size(table* tb) {
    uint32_t sz = 0;
    sz += get_columns_size(tb);
    sz += sizeof(bool);
    return sz;
}

column* get_column_by_name(table* tb, char* column_name) {
    for (int i = 0; i < tb->num_columns; i++) {
        if(!strcmp(tb->columns[i]->name,column_name)) {
            return tb->columns[i];
        }
    }
    return NULL;
}

enum data_type get_column_type_by_name(table* tb, char* column_name) {
    for (int i = 0; i < tb->num_columns; i++) {
        if(strcmp(tb->columns[i]->name,column_name) == 0) {
            return tb->columns[i]->type;
        }
    }
    return 0;
}

uint32_t get_column_offset_by_name(table* tb, char* column_name) {
    uint32_t offset = 0;
    for (int i = 0; i < tb->num_columns; i++) {
        if(strcmp(tb->columns[i]->name,column_name) == 0) {
            return offset;
        }
        offset += tb->columns[i]->size;
    }
    return -1;
}

uint8_t get_column_size_by_name(table* tb, char* column_name) {
    uint8_t size = 0;
    for (int i = 0; i < tb->num_columns; i++) {
        if(!strcmp(tb->columns[i]->name,column_name)) {
            size = (uint8_t) tb->columns[i]->size;
        }
    }
    return size;
}

size_t get_real_table_size(table* tb) {
    size_t real_size = sizeof(table) - sizeof(column**) +sizeof(column) * tb->num_columns;
    return real_size;
}

void insert_integer_record(table* tb, record* r, char* column_name, int32_t value) {
    uint32_t offset = get_column_offset_by_name(tb, column_name);
    memcpy(r->data + offset, &value, get_column_size_by_name(tb, column_name));
}

void insert_float_record(table* tb, record* r, char* column_name, float value) {
    uint32_t offset = get_column_offset_by_name(tb, column_name);
    memcpy(r->data + offset, &value, get_column_size_by_name(tb, column_name));
}

void insert_boolean_record(table* tb, record* r, char* column_name, bool value) {
    uint32_t offset = get_column_offset_by_name(tb, column_name);
    memcpy(r->data + offset, &value, get_column_size_by_name(tb, column_name));
}

void insert_string_record(table* tb, record* r, char* column_name, char* value) {
    uint32_t offset = get_column_offset_by_name(tb, column_name);
    memcpy(r->data + offset, value, get_column_size_by_name(tb, column_name));
}

/* Getters */

int32_t get_integer_record(table* tb, record* r, char* column_name) {
    int32_t i;
    uint32_t offset = get_column_offset_by_name(tb, column_name);
    memcpy(&i, r->data+offset, get_column_size_by_name(tb, column_name));
    return i;
}

float get_float_record(table* tb, record* r, char* column_name) {
    float f;
    uint32_t offset = get_column_offset_by_name(tb, column_name);
    memcpy(&f, r->data+offset, get_column_size_by_name(tb, column_name));
    return f;
}

bool get_boolean_record(table* tb, record* r, char* column_name) {
    bool b;
    uint32_t offset = get_column_offset_by_name(tb, column_name);
    memcpy(&b, r->data+offset, get_column_size_by_name(tb, column_name));
    return b;
}

char* get_string_record(table* tb, record* r, char* column_name) {
    char* s = calloc(1, get_column_size_by_name(tb, column_name));
    uint32_t offset = get_column_offset_by_name(tb, column_name);
    memcpy(s, r->data + offset, get_column_size_by_name(tb, column_name));
    return s;
}

/* To string functions */

char* integer_to_string(uint32_t value, char* dest){
    size_t size = snprintf(NULL, 0, " %22d |", value)+1;
    char* temp = calloc(1, size);
    snprintf(temp, size, " %22d |", value);

    dest = realloc(dest, strlen(dest) + strlen(temp) + 1);
    strcat(dest, temp);
    free(temp);

    return dest;
}

char* float_to_string(float value, char* dest){
    size_t size = snprintf(NULL, 0, " %.5f |", value)+1;
    char* temp = calloc(1, size);
    snprintf(temp, size, " %.5f |", value);

    dest = realloc(dest, strlen(dest) + strlen(temp) + 1);
    strcat(dest, temp);
    free(temp);

    return dest;
}

char*  bool_to_string(bool value, char* dest) {
    char* temp;
    if(value){
        temp = " TRUE |";
    } else {
        temp = " FALSE |";
    }
    dest = realloc(dest, strlen(dest) + strlen(temp) + 1);
    strcat(dest, temp);

    return dest;
}

char* replaceWord(const char* s, const char* oldW,
                  const char* newW)
{
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);

    // Counting the number of times old word
    // occur in the string
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;

            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }

    // Making new string of enough length
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);

    i = 0;
    while (*s) {
        // compare the substring with the result
        if (strstr(s, oldW) == s) {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }

    result[i] = '\0';
    return result;
}

char* string_to_string(char* value, char* dest){

    size_t size = snprintf(NULL, 0, " %22s |", value)+1;
    char* temp = calloc(1, size);
    snprintf(temp, size, " %22s |", value);

    char* this = replaceWord(temp, "_", " ");

    dest = realloc(dest, strlen(dest) + strlen(this) + 1);
    strcat(dest, this);
    free(temp);

    return dest;
}

char* simp_str_str(char* value, char* dest){

    size_t size = snprintf(NULL, 0, "%s", value)+1;
    char* temp = calloc(1, size);
    snprintf(temp, size, "%s", value);

    dest = realloc(dest, strlen(dest) + strlen(temp) + 1);
    strcat(dest, temp);
    free(temp);

    return dest;
}