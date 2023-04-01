//
// Created by Stefan on 05/03/2023.
//

#ifndef LABDB_DATABASE_H
#define LABDB_DATABASE_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct database database;
typedef struct block block;
typedef struct page page;
typedef struct table_list table_list;

#define MAX_NAME_LENGTH 32
#define DEFAULT_PAGE_SIZE 4096

struct database {
    char name[MAX_NAME_LENGTH];
    uint32_t block_size;
    uint32_t block_num;
    uint32_t schema_first_block_id;
    uint32_t schema_last_block_id;
    uint32_t first_clean_block;
    block* blk;
}  ;

enum block_type { DATABASE, SCHEMA, RECORD, FREE };

struct block {
    enum block_type type;
    uint32_t id;
    uint32_t next_id;
    uint16_t offset;
}  ;

database* create_database(char* name,
                          uint32_t block_size);
void destroy_database(database* db);
block* create_block(enum block_type type, uint32_t id, int32_t next_id);
void destroy_block(block* blk);
table_list* create_table_list(char* name,
                              uint32_t first_block,
                              int32_t last_block,
                              bool last);
FILE* open_database(char* s);
database* get_database(FILE* f);

#endif //LABDB_DATABASE_H
