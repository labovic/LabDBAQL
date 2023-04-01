//
// Created by Stefan on 20/02/23.
//

#ifndef LABDB_PAGER_H
#define LABDB_PAGER_H

#include <stdint.h>
#include "database.h"
#include "table.h"

typedef struct page page;

struct page {
    uint16_t size;
    uint8_t* buffer;
    page* next;
};

/* Initialization and Closing of the page struct that contains internal byte buffer */

page* allocate_page(uint16_t size);
void destroy_page(page* page);


void write_page_to_file(FILE* f, page* pg, uint32_t block_id);
void read_page_from_file(FILE* f, page* pg, uint32_t block_id);

void write_block_to_page(block* blk, page* pg);
block* read_block_from_page(page* pg);

void initialize_first_free_block(database* db, FILE* f);

void write_database_to_page(database* db, page* pg, uint16_t offset);
database* read_database_from_page(page* pg, uint16_t offset);

uint32_t write_table_to_page(table* tb, page* pg, uint16_t offset);
table * read_table_from_page(page* pg, uint16_t offset);

uint32_t write_record_to_page(record* r, page* pg, uint16_t offset, uint16_t size);
record* read_record_from_page(table* tb, page* pg, uint16_t offset);

void write_table_list_to_page(table_list * tbl, page* pg, uint16_t offset);
void read_table_list_from_page(table_list* tbl, page* pg, uint16_t offset);

void initialize_schema(database* db, FILE* f);
void insert_table_to_schema(table* tb, database* db, FILE* f);
table* get_table_from_schema(char* name, database* db, FILE* f);
bool delete_table_from_schema(char* name, database* db, FILE* f);

void initialize_table_record_block(table* tb, database* db, FILE* f);
void insert_record_to_table(record* r, table* tb, database* db, FILE* f);

void get_next_block(uint32_t next_id, block* blk, page* pg, FILE* f);
void write_to_last_record_block(FILE* f, page* curr_pg, block* curr_blk, page* last_pg, block* last_blk, table* tb, database* db);

#endif //LABDB_PAGER_H
