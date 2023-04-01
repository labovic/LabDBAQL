//
// Created by Stefan on 05/03/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "table.h"

block* create_block(enum block_type type, uint32_t id, int32_t next_id) {
    block* blk = calloc(1, sizeof(block));

    blk->type=type;
    blk->id=id;
    blk->next_id=next_id;
    blk->offset=sizeof(block);
}

void destroy_block(block* blk) {
    free(blk);
}

database* create_database(char* name,
                          uint32_t block_size) {
    database* db = calloc(1, sizeof(database));

    db->blk = create_block(DATABASE, 0, 1);

    strcpy(db->name, name);
    db->block_size = block_size;
    db->block_num = 3;
    db->schema_first_block_id = 1;
    db->schema_last_block_id = 1;
    db->first_clean_block = 2;
}

void destroy_database(database* db) {
    free(db->blk);
    free(db);
}

void destroy_table_list_node(table_list* tl) {
    free(tl);
}

/**
database *db = create_database("db.ldb", 4096);
page *db_pg = allocate_page(4096);
write_database_to_page(db, db_pg, sizeof(block));

FILE *f = fopen("db.ldb", "wb+");
write_page_to_file(f, db_pg, 0);
initialize_schema(db, f);

**/