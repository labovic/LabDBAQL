//
// Created by Stefan on 04/03/2023.
//

#ifndef LABDB_TABLE_H
#define LABDB_TABLE_H
#include <stdint.h>
#include <stdbool.h>
#include "database.h"

#define MAX_NAME_LENGTH 32

typedef struct column column;
typedef struct table table;
typedef struct record record;

enum data_type {INTEGER, FLOAT, BOOL, STRING, REFERENCE};

struct column {
    char name[MAX_NAME_LENGTH];
    enum data_type type;
    uint8_t size;
} ;

struct table{
    bool valid;
    char name[MAX_NAME_LENGTH];
    uint32_t block_id;
    uint32_t offset;
    uint32_t first_record_block_id;
    uint32_t last_record_block_id;
    uint32_t num_rows;
    uint8_t num_columns;
    column** columns;
} ;

struct record {
    bool valid;
    uint8_t *data;
};

column* create_column(char* name, enum data_type type, uint8_t size);
table* create_table(char* name,
                    uint8_t num_columns,
                    column** cols);
column** create_columns(column* args, ...);
record* create_record(table* tb);
void destroy_record(record* r);
table destroy_table(table* tb);

void insert_integer_record(table* tb, record* r, char* column_name, int32_t value);
void insert_float_record(table* tb, record* r, char* column_name, float value);
void insert_boolean_record(table* tb, record* r, char* column_name, bool value);
void insert_string_record(table* tb, record* r, char* column_name, char* value);

int32_t get_integer_record(table* tb, record* r, char* column_name);
char* get_string_record(table* tb, record* r, char* column_name);
float get_float_record(table* tb, record* r, char* column_name);
bool get_boolean_record(table* tb, record* r, char* column_name);

column* get_column_by_name(table* tb, char* column_name);
enum data_type get_column_type_by_name(table* tb, char* column_name);
uint8_t get_column_size_by_name(table* tb, char* column_name);
uint32_t get_columns_size(table* tb);
size_t get_real_table_size(table* tb);

char* integer_to_string(uint32_t value, char* string);
char* float_to_string(float value, char* string);
char* bool_to_string(bool value, char* string);
char* string_to_string(char* value, char* string);
char* simp_str_str(char* value, char* string);

uint32_t get_record_size(table* tb);


#endif //LABDB_TABLE_H
