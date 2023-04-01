#ifndef AQL_AST_H
#define AQL_AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_NAME_LENGTH 32

typedef struct query query;
typedef struct table_query table_query;
typedef struct records_query records_query;

typedef struct create_table create_table;
typedef struct remove_table remove_table;
typedef struct insert_records insert_records;
typedef struct update_records update_records;
typedef struct remove_records remove_records;
typedef struct return_records return_records;

typedef struct loop loop;

typedef struct column column;
typedef struct record_fields record_fields;
typedef struct record_field record_field;
typedef struct literal literal;
typedef struct field field;

typedef struct filter filter;
typedef struct comparison comparison;

union literal_value;

enum query_type { CREATE_TBL, REMOVE_TBL, INSERT_R, UPDATE_R, REMOVE_R, RETURN_R};

enum data_type { INTEGER_AST, FLOAT_AST, BOOLEAN_AST, VARCHAR_AST, REFERENCE_AST };

enum insert_type {SIMPLE_INSERT, COMPLEX_INSERT};
enum update_type {UPDATE_ALL, UPDATE_FILTER};
enum remove_type {REMOVE_ALL, REMOVE_FILTER};
enum return_type {RETURN_ROW, RETURN_ROW_FILTER, RETURN_FIELDS, RETURN_FIELDS_FILTER,
                  RETURN_ROW_JOIN, RETURN_ROW_JOIN_FILTER, RETURN_FIELDS_JOIN, RETURN_FIELDS_JOIN_FILTER};

enum relation {EQUAL_AST, NOT_EQUAL_AST, LESS_AST, MORE_AST, LESS_EQUAL_AST, MORE_EQUAL_AST};
enum comparison_type {COLUMN_VALUE, COLUMN_COLUMN, VALUE_COLUMN, VALUE_VALUE};
enum comparison_relation {OR_AST, AND_AST, NONE};

struct query {
  enum query_type type;
  create_table* ct;
  remove_table* rt;
  insert_records* ir;
  update_records* ur;
  remove_records* rem_r;
  return_records* ret_r;
};

struct create_table {
  char name[MAX_NAME_LENGTH];
  column* column;
};

struct remove_table {
    char name[MAX_NAME_LENGTH];
};

struct insert_records {
    enum insert_type type;
    char row_name[MAX_NAME_LENGTH];
    char table_name[MAX_NAME_LENGTH];
    record_fields* rfs;
};

struct update_records {
    enum update_type type;
    loop* loop;
    char row_name[MAX_NAME_LENGTH];
    char table_name[MAX_NAME_LENGTH];
    record_field* rf;
    filter* filter;
};

struct remove_records {
    enum remove_type type;
    loop* loop;
    char row_name[MAX_NAME_LENGTH];
    char table_name[MAX_NAME_LENGTH];
    filter* filter;
};

struct return_records {
    enum return_type type;
    loop* left_loop;
    loop* right_loop;

    comparison* join_condition;

    filter* filter;
    char left_return_name[MAX_NAME_LENGTH];
    char right_return_name[MAX_NAME_LENGTH];
    field* f;
};

struct loop {
    char row_name[MAX_NAME_LENGTH];
    char table_name[MAX_NAME_LENGTH];
};

struct column {
  char name[MAX_NAME_LENGTH];
  enum data_type type;
  uint8_t size;

  column* next;
};

struct record_fields {
    record_field* rf;
    record_fields* next;
};

struct record_field {
    char* name;
    literal* value;

    record_field* next;
};

struct literal {
    enum data_type type;
    union literal_value* value;
};

union literal_value {
    int32_t i;
    float f;
    bool b;
    char* s;
};

struct field {
    char* row_name;
    char* name;
    field* next;
};

struct filter {
    comparison* comparison;
    filter* next;
};

struct comparison {
    enum comparison_type type;

    literal* left_operand;
    literal* right_operand;
    enum relation relation;

    enum comparison_relation comparison_relation;

    comparison* next;

};


create_table* create_create_table(char* name, column* col);
void destroy_create_table(create_table* ct);
void print_create_table(create_table* ct);

remove_table* create_remove_table(char* name);
void destroy_remove_table(remove_table* rt);

column* create_column(char* name, int type, uint8_t size);
void destroy_column(column** head_ref);
void print_column(column* col);
void print_columns(column* col);

loop* create_loop(char* row_name, char* table_name);

field* create_field(char* first, char* second);
void print_field_names(field* f);

insert_records* create_loop_insert_records(char* row_name, char* tb_name, record_fields* rfs);
insert_records* create_insert_records(char* name, record_field* rf);

update_records* create_update_records(char* name, record_field* rf);
update_records* create_update_records_filter(loop* loop, filter* f, char* upd_row, record_field* rf, char* upd_tb);

remove_records* create_remove_records(char* name);
remove_records* create_remove_records_filter(loop* loop, filter* f, char* ret_row, char* ret_tb);

return_records* create_return_records(loop* loop, char* return_name);
return_records* create_return_records_filter(loop* loop, filter* f, char* return_name);
return_records* create_return_records_fields(loop* loop, field* f);
return_records* create_return_records_fields_filter(loop* loop, filter* filter, field* f);

return_records* create_return_joined_records(loop* left, loop* right,
                                             comparison* join_condition,
                                             char* left_row, char* right_row);
return_records* create_return_joined_records_filter(loop* left, loop* right,
                                                    comparison* join_condition,
                                                    filter* filter,
                                                    char* left_row, char* right_row);
return_records* create_return_joined_records_fields(loop* left, loop* right,
                                                    comparison* join_condition, field* f);
return_records* create_return_joined_records_fields_filter(loop* left, loop* right, comparison* join_condition,
                                                           filter* filter, field* f);

record_fields* create_record_fields(record_field* rf);
record_field* create_record_field(char* name, literal* value);

literal* create_integer_literal(int32_t i);
literal* create_float_literal(float f);
literal* create_boolean_literal(bool b);
literal* create_string_literal(char* s);
literal* create_reference_literal(char* first, char* second);

void print_insert_records(insert_records* ir);
void print_record_field(record_field* rf);

filter* create_filter(comparison* c);
comparison* create_comparison(literal* left, literal* right, int cmp);
comparison* create_complex_comparison(literal* left, literal* right, int cmp, int op);
comparison* create_join_condition(char* left_row, char* left_field, char* right_row, char* right_field);

void print_filter(filter* f);
void print_comparison(comparison* c);
void print_literal(literal* l);


query* create_create_table_query(create_table* ct);
query* create_remove_table_query(remove_table* rt);
query* create_insert_records_query(insert_records* ir);
query* create_update_records_query(update_records* ir);
query* create_remove_records_query(remove_records* ir);
query* create_return_records_query(return_records* ir);


void print_query(query* q);

#endif //AQL_AST_H
