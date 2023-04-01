//
// Created by stele on 26/03/23.
//

#ifndef CLIENT_SERVER_SERVER_TRANSPORT_H
#define CLIENT_SERVER_SERVER_TRANSPORT_H

#define MAX_NAME_LENGTH 32
#define MAX 1024


#include <jansson.h>
#include <unistd.h>

#include "../db/database.h"
#include "../db/table.h"
#include "../db/pager.h"
#include "../db/query.h"

#include "../db/utils.h"

typedef struct create_table create_table_query;
typedef struct remove_table  remove_table_query;
typedef struct insert_record insert_record_query;
typedef struct return_records return_records_query;
typedef struct return_records_table return_records_table;

typedef struct return_records_column return_records_column;

typedef struct record_field record_field;
typedef struct literal literal;
union literal_value;


enum aql_query_type { CREATE_TBL, REMOVE_TBL ,INSERT_R, UPDATE_R, REMOVE_R, RETURN_R};

enum insert_type {SIMPLE_INSERT, COMPLEX_INSERT};
enum update_type {UPDATE_ALL, UPDATE_FILTER};
enum remove_type {REMOVE_ALL, REMOVE_FILTER};
enum return_type {RETURN_ROW, RETURN_ROW_FILTER, RETURN_FIELDS, RETURN_FIELDS_FILTER,
    RETURN_ROW_JOIN, RETURN_ROW_JOIN_FILTER, RETURN_FIELDS_JOIN, RETURN_FIELDS_JOIN_FILTER};
enum return_value {OK, ARRAY};

typedef struct query_to_execute {
    enum aql_query_type query_type;
    enum insert_type ins_type;
    enum update_type upd_type;
    enum remove_type rem_type;
    enum return_type ret_type;

    create_table_query* createTableQuery;
    insert_record_query* insertRecordQuery;
    return_records_query* returnRecordsQuery;

    condition* condition;
    char* table_name;

    enum return_value return_value;
} query_to_execute;

struct create_table {
    char* name;
    uint8_t num_cols;
    column** cols;
};

struct remove_table {
    char *name;
};

struct return_records {
    return_records_table* left;
    return_records_table* right;
};

struct return_records_table {
    char* table_name;
    char* joint_column_name;
    int8_t num_cols;
    char** return_columns;
};


struct insert_record{
    enum insert_type ins_type;
    char* table_name;
    record_field* rec;
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

query_to_execute* server_decode_json(char* s);
void server_communicate(int connfd, database* db, FILE* f);

record_field* create_record_field(char* name, literal* value);

literal* create_integer_literal(int32_t i);
literal* create_float_literal(float f) ;
literal* create_boolean_literal(bool b);
literal* create_string_literal(char* s);

#endif //CLIENT_SERVER_SERVER_TRANSPORT_H
