//
// Created by Stefan on 20/02/23.
//
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "pager.h"
#include "database.h"
#include "table.h"

/* Initialization and Closing of the page struct that contains internal byte buffer */
page* allocate_page(uint16_t size) {
    uint8_t* buffer = calloc(1, size);
    page* pg = calloc(1, sizeof(page));
    pg->buffer = buffer;
    pg->size = size;
    pg->next = NULL;
    return pg;
}

void destroy_page(page* page) {
    free(page->buffer);
    free(page);
}
/* Page and File */

void write_page_to_file(FILE* f, page* pg, uint32_t block_id) {
    if(pg != NULL) {
        fseek(f, block_id * pg->size, SEEK_SET);
        fwrite(pg->buffer, pg->size, 1, f);
    }
}

void read_page_from_file(FILE* f, page* pg, uint32_t block_id) {
    fseek(f, block_id * pg->size,SEEK_SET);
    fread(pg->buffer, pg->size, 1, f);
}

/* Page and Block */

void write_block_to_page(block* blk, page* pg) {
    memcpy(pg->buffer, blk, sizeof(block));
}

block* read_block_from_page(page* pg) {
    block* blk = calloc(1, sizeof(block));
    memcpy(blk, pg->buffer, sizeof(block));
    return blk;
}

/* Database and Page */

void write_database_to_page(database* db, page* pg, uint16_t offset){
    memcpy(pg->buffer, db->blk, sizeof(block));
    memcpy(pg->buffer + offset, db, sizeof(database)-sizeof(block*));
}

database* read_database_from_page(page* pg, uint16_t offset){
    block* blk = calloc(1, sizeof (block));
    memcpy(blk, pg->buffer, offset);
    database* db = calloc(1, sizeof (database));
    memcpy(db, pg->buffer+offset, sizeof(database)-sizeof (block*));
    offset += sizeof(database);
    blk->offset = offset;
    db->blk = blk;
}

void initialize_first_free_block(database* db, FILE* f) {
    block* blk = calloc(1, sizeof(block));
    page* fbl_pg = allocate_page(db->block_size);

    blk->type = FREE;
    blk->id = db->first_clean_block;
    blk->next_id = db->first_clean_block;
    blk->offset = sizeof(block);

    write_block_to_page(blk, fbl_pg);
    write_page_to_file(f, fbl_pg, blk->id);

    free(blk);
    destroy_page(fbl_pg);
}

/* Table and Page */

uint32_t write_table_to_page(table* tb, page* pg, uint16_t offset){
    uint32_t table_size = sizeof(table)-sizeof(column**);
    memcpy(pg->buffer + offset, tb, table_size);
    offset += table_size;

    for(int i = 0; i < tb->num_columns; i++) {
        memcpy(pg->buffer + offset, tb->columns[i], sizeof(column));
        offset += sizeof(column);
    }
    return offset;
}

table* read_table_from_page(page* pg, uint16_t offset){
    table* tb = calloc(1, sizeof(table));
    uint32_t table_size = sizeof(table)-sizeof(column**);
    memcpy(tb, pg->buffer + offset, table_size);
    offset += table_size;

    column** cols = calloc(1, sizeof(column)*tb->num_columns);
    tb->columns = cols;

    for(int i = 0; i < tb->num_columns; i++) {
        column* col = calloc(1, sizeof(column));
        memcpy(col, pg->buffer+offset, sizeof(column));
        tb->columns[i] = col;
        offset += sizeof(column);
    }
    return tb;
}

/* Records and Page */

uint32_t write_record_to_page(record* r, page* pg, uint16_t offset, uint16_t size){
    uint32_t sz = size + sizeof(bool);
    memcpy(pg->buffer + offset, &(r->valid), sizeof(bool));
    memcpy(pg->buffer + offset + sizeof(bool), r->data, size);
    return sz;
}

record* read_record_from_page(table* tb, page* pg, uint16_t offset){
    record* r = create_record(tb);
    memcpy(&(r->valid), pg->buffer + offset, sizeof(bool));
    memcpy(r->data, pg->buffer + offset + sizeof(bool), get_columns_size(tb));
    return r;
}

/* Initialize Schema */

page* load_first_schema_block_to_page(database* db) {
    page* pg = allocate_page(db->block_size);
    block* blk = calloc(1, sizeof(block));

    blk->type = SCHEMA;
    blk->id = db->schema_first_block_id;
    blk->next_id = db->schema_last_block_id;
    blk->offset = sizeof(block);

    write_block_to_page(blk, pg);
    free(blk);
    return pg;
}

void initialize_schema(database* db, FILE* f) {
    initialize_first_free_block(db, f);
    page* pg = load_first_schema_block_to_page(db);
    write_page_to_file(f, pg, db->schema_first_block_id);
    destroy_page(pg);
}

/* Table and Database */

void get_empty_scheme_block(database* db, block* blk, page* pg, FILE* f) {
    blk->next_id = db->first_clean_block;
    write_block_to_page(blk, pg);
    write_page_to_file(f, pg, blk->id);

    page* tmp_pg = allocate_page(db->block_size);
    read_page_from_file(f, tmp_pg, db->first_clean_block);
    block* tmp_blk = read_block_from_page(tmp_pg);

    blk->offset = sizeof(block);
    blk->id = db->first_clean_block;
    db->schema_last_block_id = blk->id;

    if (tmp_blk->id == tmp_blk->next_id) {
        db->first_clean_block = db->block_num;
        db->block_num++;
        initialize_first_free_block(db, f);
    } else {
        db->first_clean_block = tmp_blk->next_id;
    }

    free(tmp_blk);
    destroy_page(tmp_pg);
}

void return_empty_schema_block(database* db, block* blk, FILE* f){
    blk->next_id = db->first_clean_block;
    db->first_clean_block = blk->id;
    blk->offset = sizeof(block);
    blk->type = FREE;

    page* tmp_pg = allocate_page(db->block_size);

    write_block_to_page(blk, tmp_pg);
    write_page_to_file(f, tmp_pg, blk->id);

    write_database_to_page(db, tmp_pg, sizeof(block));
    write_page_to_file(f, tmp_pg, 0);

    destroy_page(tmp_pg);
}

void get_next_block(uint32_t next_id, block* blk, page* pg, FILE* f) {
    read_page_from_file(f, pg, next_id);
    block* new_blk = calloc(1, sizeof(block));
    memcpy(new_blk, pg->buffer, sizeof(block));

    blk->offset = new_blk->offset;
    blk->id = new_blk->id;
    blk->next_id = new_blk->next_id;

    free(new_blk);

}


void insert_table_to_schema(table* tb, database* db, FILE* f) {

    page* pg = allocate_page(db->block_size);
    read_page_from_file(f, pg, db->schema_last_block_id);
    block* blk = read_block_from_page(pg);

    if((get_real_table_size(tb) + blk->offset) >= db->block_size) {
        get_empty_scheme_block(db, blk, pg, f);
    }
    tb->valid = true;
    tb->block_id = blk->id;
    tb->offset = blk->offset;

    blk->offset = write_table_to_page(tb, pg, blk->offset);
    write_block_to_page(blk, pg);
    write_page_to_file(f, pg, blk->id);
    write_database_to_page(db, pg, sizeof(block));
    write_page_to_file(f, pg, 0);

    free(blk);
    destroy_page(pg);
}

table* get_table_from_schema(char* name, database* db, FILE* f) {
    page* pg = allocate_page(db->block_size);
    read_page_from_file(f, pg, db->schema_first_block_id);
    block* blk = read_block_from_page(pg);

    table* tb = NULL;

    uint32_t off = sizeof(block);
    while((blk->id != db->schema_last_block_id) || off < blk->offset) {
        while(off < blk->offset) {
            tb = read_table_from_page(pg, off);
            if(!strcmp(name, tb->name)) {
                free(blk);
                destroy_page(pg);
                return tb;
            }
            off += get_real_table_size(tb);
        }
        if (blk->id != db->schema_last_block_id) {
            off = sizeof(block);
        }
        get_next_block(blk->next_id, blk, pg, f);
    }

    free(blk);
    destroy_page(pg);
    return NULL;
}

void write_to_last_record_block(FILE* f, page* curr_pg, block* curr_blk, page* last_pg, block* last_blk, table* tb, database* db) {
    uint32_t read_off = sizeof(block);
    uint32_t off = sizeof(block);

    while(read_off < curr_blk->offset){
        record* r = read_record_from_page(tb, curr_pg, read_off);
        if(r->valid){
            if(last_blk->id != curr_blk->id) {
                if ((last_blk->offset + get_record_size(tb)) < db->block_size) {
                    write_record_to_page(r, last_pg, last_blk->offset, get_columns_size(tb));
                    last_blk->offset += get_record_size(tb);
                } else {
                    write_record_to_page(r, curr_pg, off, get_columns_size(tb));
                    off += get_record_size(tb);
                }
            } else {
                write_record_to_page(r, curr_pg, off, get_columns_size(tb));
                off += get_record_size(tb);
            }
        }
        read_off += get_record_size(tb);
    }

    curr_blk->offset = off;

    if (curr_blk->offset == sizeof(block) && ((curr_blk->id != tb->first_record_block_id) && ((curr_blk->id != tb->last_record_block_id)))){
        return_empty_schema_block(db, curr_blk, f);
    } else {
        tb->last_record_block_id = curr_blk->id;
        curr_blk->next_id = curr_blk->id;
        last_blk->next_id = curr_blk->id;
    }

    write_block_to_page(last_blk, last_pg);
    write_page_to_file(f, last_pg, last_blk->id);

    write_block_to_page(curr_blk, curr_pg);
    write_page_to_file(f, curr_pg, curr_blk->id);

    page* db_pg = allocate_page(db->block_size);
    write_database_to_page(db, db_pg, sizeof(block));
    write_page_to_file(f, db_pg, 0);
    destroy_page(db_pg);

}

void write_to_last_schema_block(FILE* f, page* curr_pg, block* curr_blk, page* last_pg, block* last_blk, database* db) {
    uint32_t read_off = sizeof(block);
    uint32_t off = sizeof(block);

    while(read_off < curr_blk->offset){
        table* tb = read_table_from_page(curr_pg, read_off);
        if(tb->valid){
            if(last_blk->id != curr_blk->id) {
                if ((last_blk->offset + get_real_table_size(tb)) < db->block_size) {
                    write_table_to_page(tb, last_pg, last_blk->offset);
                    last_blk->offset += get_real_table_size(tb);
                } else {
                    write_table_to_page(tb, curr_pg, off);
                    off += get_real_table_size(tb);
                }
            } else {
                write_table_to_page(tb, curr_pg, off);
                off += get_real_table_size(tb);
            }
        }
        read_off += get_real_table_size(tb);
    }

    curr_blk->offset = off;

    if (curr_blk->offset == sizeof(block) && ((curr_blk->id != db->schema_first_block_id) && ((curr_blk->id != db->schema_last_block_id)))){
        return_empty_schema_block(db, curr_blk, f);
    } else {
        db->schema_last_block_id = curr_blk->id;
        curr_blk->next_id = curr_blk->id;
        last_blk->next_id = curr_blk->id;
    }

    write_block_to_page(last_blk, last_pg);
    write_page_to_file(f, last_pg, last_blk->id);

    write_block_to_page(curr_blk, curr_pg);
    write_page_to_file(f, curr_pg, curr_blk->id);

    write_database_to_page(db, last_pg, sizeof(block));
    write_page_to_file(f, last_pg, 0);

}

bool delete_table_from_schema(char* name, database* db, FILE* f) {

    uint32_t pre_id = db->schema_first_block_id;

    page* curr_pg = allocate_page(db->block_size);
    read_page_from_file(f, curr_pg, db->schema_first_block_id);
    block* curr_blk = read_block_from_page(curr_pg);

    page* last_pg = allocate_page(db->block_size);
    read_page_from_file(f, last_pg, db->schema_last_block_id);
    block* last_blk = read_block_from_page(last_pg);

    table* tb = NULL;

    uint32_t off = sizeof(block);
    while((curr_blk->id != db->schema_last_block_id) || off < curr_blk->offset) {
        while(off < curr_blk->offset) {
            tb = read_table_from_page(curr_pg, off);
            if(!strcmp(name, tb->name)) {

                tb->valid = false;
                write_table_to_page(tb, curr_pg, off);

                if(pre_id != curr_blk->id) {
                    page* pre_pg = allocate_page(db->block_size);
                    read_page_from_file(f, pre_pg, pre_id);
                    block* pre_blk = read_block_from_page(pre_pg);

                    pre_blk->next_id = curr_blk->next_id;

                    write_block_to_page(pre_blk, pre_pg);
                    write_page_to_file(f, pre_pg, pre_id);

                    free(pre_blk);
                    destroy_page(pre_pg);
                } else {
                    db->schema_first_block_id = curr_blk->next_id;
                }

                write_to_last_schema_block(f,
                                           curr_pg,
                                           curr_blk,
                                           last_pg,
                                           last_blk,
                                           db);

                free(curr_blk);
                free(last_blk);
                destroy_page(curr_pg);
                destroy_page(last_pg);

                return true;
            }
            off += get_real_table_size(tb);
        }
        if (curr_blk->id != db->schema_last_block_id) {
            off = sizeof(block);
        }
        pre_id = curr_blk->id;
        get_next_block(curr_blk->next_id, curr_blk, curr_pg, f);
    }

    free(curr_blk);
    free(last_blk);
    destroy_page(curr_pg);
    destroy_page(last_pg);

    return false;
}

/* Records and Table */

void get_empty_record_block(table* tb, database* db, block* blk, page* pg, FILE* f) {
    blk->next_id = db->first_clean_block;
    write_block_to_page(blk, pg);
    write_page_to_file(f, pg, blk->id);

    page* tmp_pg = allocate_page(db->block_size);
    read_page_from_file(f, tmp_pg, db->first_clean_block);
    block* tmp_blk = read_block_from_page(tmp_pg);

    blk->offset = sizeof(block);
    blk->id = db->first_clean_block;
    tb->last_record_block_id = blk->id;

    if (tmp_blk->id == tmp_blk->next_id) {
        db->first_clean_block = db->block_num;
        db->block_num++;
        initialize_first_free_block(db, f);
    } else {
        db->first_clean_block = tmp_blk->next_id;
    }

    free(tmp_blk);
    destroy_page(tmp_pg);
}

void initialize_table_record_block(table* tb, database* db, FILE* f) {

    page* pg = allocate_page(db->block_size);
    read_page_from_file(f, pg, db->first_clean_block);
    block* blk = read_block_from_page(pg);

    blk->type = RECORD;
    blk->offset = sizeof(block);
    blk->id = db->first_clean_block;

    tb->first_record_block_id = blk->id;
    tb->last_record_block_id = blk->id;

    if (blk->id == blk->next_id) {
        db->first_clean_block = db->block_num;
        db->block_num++;
        initialize_first_free_block(db, f);
    } else {
        db->first_clean_block = blk->next_id;
    }

    write_block_to_page(blk, pg);
    write_page_to_file(f, pg, blk->id);

    read_page_from_file(f, pg, tb->block_id);
    write_table_to_page(tb, pg, tb->offset);
    write_page_to_file(f, pg, tb->block_id);

    free(blk);
    destroy_page(pg);
}

void insert_record_to_table(record* r, table* tb, database* db, FILE* f) {

    page* pg = allocate_page(db->block_size);
    read_page_from_file(f, pg, tb->last_record_block_id);
    block* blk = read_block_from_page(pg);

    if((get_record_size(tb) + blk->offset) >= db->block_size) {
        get_empty_record_block(tb, db, blk, pg, f);
    }
    r->valid = true;
    blk->offset += write_record_to_page(r, pg, blk->offset, get_columns_size(tb));
    tb->num_rows++;

    write_block_to_page(blk, pg);
    write_page_to_file(f, pg, blk->id);
    write_database_to_page(db, pg, sizeof(block));
    write_page_to_file(f, pg, 0);

    read_page_from_file(f, pg, tb->block_id);
    write_table_to_page(tb, pg, tb->offset);
    write_page_to_file(f, pg, tb->block_id);

    free(blk);
    destroy_page(pg);
}










