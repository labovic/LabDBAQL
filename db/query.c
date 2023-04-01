//
// Created by Stefan on 16/03/2023.
//

#include "query.h"
#include <stdlib.h>
#include <string.h>

table_to_join *create_table_to_join(table *tb,
                                    uint8_t num_cols,
                                    char **view_cols,
                                    condition *cond,
                                    column *col_to_join) {
    table_to_join *tj = malloc(sizeof(table_to_join));
    tj->tb = tb;
    tj->num_cols = num_cols;
    tj->view_cols = view_cols;
    tj->col_to_join = col_to_join;
}

condition* create_condition(enum condition_type type, condition_operand* left_operand,
                            condition_operand* right_operand, enum relation relation,
                            enum next_relation next_relation) {

    condition* c = calloc(1,sizeof(condition));
    c->type = type;
    c->left_operand = left_operand;
    c->right_operand = right_operand;
    c->relation = relation;
    c->next_relation = next_relation;

    return c;
}

condition* create_condition_join(enum belongs_to_table btt, enum condition_type type, condition_operand* left_operand,
                                 condition_operand* right_operand, enum relation relation,
                                 enum next_relation next_relation) {

    condition* c = calloc(1,sizeof(condition));
    c->type = type;
    c->left_operand = left_operand;
    c->right_operand = right_operand;
    c->relation = relation;
    c->next_relation = next_relation;

    return c;
}

condition_operand * create_condition_integer_operand(int32_t value, enum belongs_to_table btt) {
    condition_operand* co = malloc(sizeof(condition_operand));
    co->belongs_to_table = btt;
    co->type = INTEGER;
    co->size = sizeof(int32_t);
    co->value = malloc(sizeof(union type_value));
    co->value->i = value;
    return co;
}

condition_operand * create_condition_float_operand(float value, enum belongs_to_table btt) {
    condition_operand* co = malloc(sizeof(condition_operand));
    co->belongs_to_table = btt;
    co->type = FLOAT;
    co->size = sizeof(int32_t);
    co->value = malloc(sizeof(union type_value));
    co->value->f = value;
    return co;
}

condition_operand * create_condition_bool_operand(bool value, enum belongs_to_table btt) {
    condition_operand* co = malloc(sizeof(condition_operand));
    co->belongs_to_table = btt;
    co->type = BOOL;
    co->size = sizeof(bool);
    co->value = malloc(sizeof(union type_value));
    co->value->b = value;
    return co;
}

condition_operand * create_condition_string_operand(char* value, enum belongs_to_table btt) {
    condition_operand* co = malloc(sizeof(condition_operand));
    co->belongs_to_table = btt;
    co->type = STRING;
    co->size = strlen(value)+1;
    co->value = malloc(sizeof(union type_value));
    co->value->s = value;
    return co;
}

bool check_integers(int32_t first, int32_t second, enum relation rel) {
    switch (rel) {
        case LESS:
            if (first < second) {
                return true;
            }
            break;
        case LESS_EQUAL:
            if (first <= second) {
                return true;
            }
            break;
        case MORE:
            if (first > second) {
                return true;
            }
            break;
        case MORE_EQUAL:
            if (first >= second) {
                return true;
            }
            break;
        case EQUAL:
            if (first == second) {
                return true;
            }
            break;
        case NOT_EQUAL:
            if (first != second) {
                return true;
            }
            break;
        default:
            return false;
    }
    return false;
}

bool check_floats(float first, float second, enum relation rel) {
    switch (rel) {
        case LESS:
            if (first < second) {
                return true;
            }
            break;
        case LESS_EQUAL:
            if (first <= second) {
                return true;
            }
            break;
        case MORE:
            if (first > second) {
                return true;
            }
            break;
        case MORE_EQUAL:
            if (first >= second) {
                return true;
            }
            break;
        case EQUAL:
            if (first == second) {
                return true;
            }
            break;
        case NOT_EQUAL:
            if (first != second) {
                return true;
            }
            break;
        default:
            return false;
    }
    return false;
}

bool check_bools(bool first, bool second, enum relation rel) {
    switch (rel) {
        case EQUAL:
            if (first == second) {
                return true;
            }
            break;
        case NOT_EQUAL:
            if (first != second) {
                return true;
            }
            break;
        default:
            return false;
    }
    return false;
}

bool check_strings(char *first, char *second, enum relation rel) {
    switch (rel) {
        case LESS:
            if (strlen(first) < strlen(second)) {
                return true;
            }
            break;
        case LESS_EQUAL:
            if (strlen(first) <= strlen(second)) {
                return true;
            }
            break;
        case MORE:
            if (strlen(first) > strlen(second)) {
                return true;
            }
            break;
        case MORE_EQUAL:
            if (strlen(first) >= strlen(second)) {
                return true;
            }
            break;
        case EQUAL:
            if (!strcmp(first, second)) {
                return true;
            }
            break;
        case NOT_EQUAL:
            if (strcmp(first, second)) {
                return true;
            }
        case LIKE:
            if(strlen(second) > strlen(first)){
                return false;
            }
            for(int i = 0; i <= strlen(first); i++) {
                if(second[i] == '\0'){
                    break;
                }
                if(second[i] != first[i]){
                    return false;
                }
            }
            return true;
        default:
            return false;
    }
    return false;
}

void compare_column_value(bool* flag, table* tb, record* r, condition* c, enum next_relation next_relation) {
    bool met_condition;
    switch (c->right_operand->type) {
        case INTEGER:;
            int32_t i_n = get_integer_record(tb, r, c->left_operand->value->s);
            met_condition = check_integers(i_n, c->right_operand->value->i, c->relation);
            switch (next_relation) {
                case OR:
                    *flag = *flag || met_condition;
                    break;
                case AND:;
                    *flag = *flag && met_condition;
                    break;
                case NONE:
                    *flag = *flag && met_condition;
                    break;
            }
            break;
        case FLOAT:;
            float f_n = get_float_record(tb, r, c->left_operand->value->s);
            met_condition = check_floats(f_n, c->right_operand->value->f, c->relation);
            switch (next_relation) {
                case OR:
                    *flag = *flag || met_condition;
                    break;
                case AND:;
                    *flag = *flag && met_condition;
                    break;
                case NONE:
                    *flag = *flag && met_condition;
                    break;
            }
            break;
        case BOOL:;
            bool b_n = get_boolean_record(tb, r, c->left_operand->value->s);
            met_condition = check_bools(b_n, c->right_operand->value->b, c->relation);
            switch (next_relation) {
                case OR:
                    *flag = *flag || met_condition;
                    break;
                case AND:;
                    *flag = *flag && met_condition;
                    break;
                case NONE:
                    *flag = *flag && met_condition;
                    break;
            }
            break;
        case STRING:;
            char *s = get_string_record(tb, r, c->left_operand->value->s);
            met_condition = check_strings(s, c->right_operand->value->s, c->relation);
            switch (next_relation) {
                case OR:
                    *flag = *flag || met_condition;
                    break;
                case AND:;
                    *flag = *flag && met_condition;
                    break;
                case NONE:
                    *flag = *flag && met_condition;
                    break;
            }
            break;
    }
}

void compare_column_column(bool* flag, table* tb, record* r, condition* c, enum next_relation next_relation) {
    bool met_condition;
    enum data_type dt = get_column_type_by_name(tb, c->left_operand->value->s);
    switch (dt) {
        case INTEGER:;
            int32_t l_i = get_integer_record(tb, r, c->left_operand->value->s);
            int32_t r_i = get_integer_record(tb, r, c->right_operand->value->s);
            met_condition = check_integers(l_i, r_i, c->relation);
            switch (next_relation) {
                case OR:
                    *flag = *flag || met_condition;
                    break;
                case AND:;
                    *flag = *flag && met_condition;
                    break;
                case NONE:
                    *flag = *flag && met_condition;
                    break;
            }
            break;
        case FLOAT:;
            float l_f = get_float_record(tb, r, c->left_operand->value->s);
            float r_f = get_float_record(tb, r, c->right_operand->value->s);
            met_condition = check_floats(l_f, r_f, c->relation);
            switch (next_relation) {
                case OR:
                    *flag = *flag || met_condition;
                    break;
                case AND:;
                    *flag = *flag && met_condition;
                    break;
                case NONE:
                    *flag = *flag && met_condition;
                    break;
            }
            break;
        case BOOL:;
            bool l_b = get_boolean_record(tb, r, c->left_operand->value->s);
            bool r_b = get_boolean_record(tb, r, c->right_operand->value->s);
            met_condition = check_bools(l_b, r_b, c->relation);
            switch (next_relation) {
                case OR:
                    *flag = *flag || met_condition;
                    break;
                case AND:;
                    *flag = *flag && met_condition;
                    break;
                case NONE:
                    *flag = *flag && met_condition;
                    break;
            }
            break;
        case STRING:;
            char* l_s = get_string_record(tb, r, c->left_operand->value->s);
            char* r_s = get_string_record(tb, r, c->right_operand->value->s);
            met_condition = check_strings(l_s, r_s, c->relation);
            switch (next_relation) {
                case OR:
                    *flag = *flag || met_condition;
                    break;
                case AND:;
                    *flag = *flag && met_condition;
                    break;
                case NONE:
                    *flag = *flag && met_condition;
                    break;
            }
            break;
    }
}

void compare_value_value(bool* flag, condition* c, enum next_relation next_relation) {
    bool met_condition;
    switch (c->left_operand->type) {
        case INTEGER:;
            met_condition = check_integers(c->left_operand->value->i, c->right_operand->value->i, c->relation);
            switch (next_relation) {
                case OR:
                    *flag = *flag || met_condition;
                    break;
                case AND:;
                    *flag = *flag && met_condition;
                    break;
                case NONE:
                    *flag = *flag && met_condition;
                    break;
            }
            break;
        case FLOAT:;
            met_condition = check_floats(c->left_operand->value->f, c->right_operand->value->f, c->relation);
            switch (next_relation) {
                case OR:
                    *flag = *flag || met_condition;
                    break;
                case AND:;
                    *flag = *flag && met_condition;
                    break;
                case NONE:
                    *flag = *flag && met_condition;
                    break;
            }
            break;
        case BOOL:;
            met_condition = check_bools(c->left_operand->value->b, c->right_operand->value->b, c->relation);
            switch (next_relation) {
                case OR:
                    *flag = *flag || met_condition;
                    break;
                case AND:;
                    *flag = *flag && met_condition;
                    break;
                case NONE:
                    *flag = *flag && met_condition;
                    break;
            }
            break;
        case STRING:;
            met_condition = check_strings(c->left_operand->value->s, c->right_operand->value->s, c->relation);
            switch (next_relation) {
                case OR:
                    *flag = *flag || met_condition;
                    break;
                case AND:;
                    *flag = *flag && met_condition;
                    break;
                case NONE:
                    *flag = *flag && met_condition;
                    break;
            }
            break;
    }
}

void compare_column_column_join(bool* flag, table* left_tb, table* right_tb, record* left_r, record* right_r, condition* c, enum next_relation next_relation) {
    bool met_condition;
    enum data_type dt;

    switch (c->left_operand->belongs_to_table) {
        case LEFT:
            dt = get_column_type_by_name(left_tb, c->left_operand->value->s);
            break;
        case RIGHT:
            dt = get_column_type_by_name(right_tb, c->left_operand->value->s);
            break;
    }

    switch (dt) {
        int32_t l_i;
        int32_t r_i;
        case INTEGER:;
            switch (c->left_operand->belongs_to_table) {
                case LEFT:
                    l_i = get_integer_record(left_tb, left_r, c->left_operand->value->s);
                    break;
                case RIGHT:
                    l_i = get_integer_record(right_tb, right_r, c->left_operand->value->s);
                    break;
            }
            switch (c->right_operand->belongs_to_table) {
                case LEFT:
                    r_i = get_integer_record(left_tb, left_r, c->right_operand->value->s);
                    break;
                case RIGHT:
                    r_i = get_integer_record(right_tb, right_r, c->right_operand->value->s);
                    break;
            }
            met_condition = check_integers(l_i, r_i, c->relation);
            switch (next_relation) {
                case OR:
                    *flag = *flag || met_condition;
                    break;
                case AND:;
                    *flag = *flag && met_condition;
                    break;
                case NONE:
                    *flag = *flag && met_condition;
                    break;
            }
            break;
        case FLOAT:;
            float l_f;
            float r_f;

            switch (c->left_operand->belongs_to_table) {
                case LEFT:
                    l_f = get_float_record(left_tb, left_r, c->left_operand->value->s);
                    break;
                case RIGHT:
                    l_f = get_float_record(right_tb, right_r, c->left_operand->value->s);
                    break;
            }
            switch (c->right_operand->belongs_to_table) {
                case LEFT:
                    r_f = get_float_record(left_tb, left_r, c->right_operand->value->s);
                    break;
                case RIGHT:
                    r_f = get_float_record(right_tb, right_r, c->right_operand->value->s);
                    break;
            }
            met_condition = check_floats(l_f, r_f, c->relation);
            switch (next_relation) {
                case OR:
                    *flag = *flag || met_condition;
                    break;
                case AND:;
                    *flag = *flag && met_condition;
                    break;
                case NONE:
                    *flag = *flag && met_condition;
                    break;
            }
            break;
        case BOOL:;
            bool l_b;
            bool r_b;

            switch (c->left_operand->belongs_to_table) {
                case LEFT:
                    l_b = get_boolean_record(left_tb, left_r, c->left_operand->value->s);
                    break;
                case RIGHT:
                    l_b = get_boolean_record(right_tb, right_r, c->left_operand->value->s);
                    break;
            }
            switch (c->right_operand->belongs_to_table) {
                case LEFT:
                    r_b = get_boolean_record(left_tb, left_r, c->right_operand->value->s);
                    break;
                case RIGHT:
                    r_b = get_boolean_record(right_tb, right_r, c->right_operand->value->s);
                    break;
            }

            met_condition = check_bools(l_b, r_b, c->relation);
            switch (next_relation) {
                case OR:
                    *flag = *flag || met_condition;
                    break;
                case AND:;
                    *flag = *flag && met_condition;
                    break;
                case NONE:
                    *flag = *flag && met_condition;
                    break;
            }
            break;
        case STRING:;
            char* l_s;
            char* r_s;

            switch (c->left_operand->belongs_to_table) {
                case LEFT:
                    l_s = get_string_record(left_tb, left_r, c->left_operand->value->s);
                    break;
                case RIGHT:
                    l_s = get_string_record(right_tb, right_r, c->left_operand->value->s);
                    break;
            }
            switch (c->right_operand->belongs_to_table) {
                case LEFT:
                    r_s = get_string_record(left_tb, left_r, c->right_operand->value->s);
                    break;
                case RIGHT:
                    r_s = get_string_record(right_tb, right_r, c->right_operand->value->s);
                    break;
            }

            met_condition = check_strings(l_s, r_s, c->relation);
            switch (next_relation) {
                case OR:
                    *flag = *flag || met_condition;
                    break;
                case AND:;
                    *flag = *flag && met_condition;
                    break;
                case NONE:
                    *flag = *flag && met_condition;
                    break;
            }
            break;
    }
}


column_to_update *create_integer_column_to_update(char *name, int32_t val) {

    column_to_update *c = calloc(1, sizeof(column_to_update));
    c->col_name = name;
    c->type = INTEGER;
    c->size = sizeof(int32_t);
    c->value = calloc(1, c->size);
    c->value->i = val;
    c->next = NULL;
    return c;
}

column_to_update *create_float_column_to_update(char *name, float val) {

    column_to_update *c = calloc(1, sizeof(column_to_update));
    c->col_name = name;
    c->type = FLOAT;
    c->size = sizeof(float);
    c->value = calloc(1, c->size);
    c->value->f = val;
    c->next = NULL;
    return c;
}

column_to_update *create_bool_column_to_update(char *name, bool val) {

    column_to_update *c = calloc(1, sizeof(column_to_update));
    c->col_name = name;
    c->type = BOOL;
    c->size = sizeof(bool);
    c->value = calloc(1, c->size);
    c->value->b = val;
    c->next = NULL;
    return c;
}

column_to_update *create_string_column_to_update(char *name, char *val) {

    column_to_update *c = calloc(1, sizeof(column_to_update));
    c->col_name = name;
    c->type = STRING;
    c->size = strlen(val) + 1;
    c->value = calloc(1, c->size);
    strcpy(c->value->s, val);
    c->next = NULL;
    return c;
}

uint32_t select_records_from_table(uint32_t block_offset, char *buffer, uint32_t buff_sz,
                                   uint8_t num_cols, char **view_cols, condition *cond,
                                   table *tb, database *db, FILE *f) {
    uint32_t buffer_offset = 0;
    page *curr_pg = allocate_page(db->block_size);
    uint32_t off = sizeof(block);
    if (block_offset == 0) {
        read_page_from_file(f, curr_pg, tb->first_record_block_id);
    } else {
        read_page_from_file(f, curr_pg, block_offset / db->block_size);
        off = block_offset % db->block_size;
    }

    block *curr_blk = read_block_from_page(curr_pg);

    char *string = calloc(1, 2);
    while ((curr_blk->id != tb->last_record_block_id) || (off < curr_blk->offset)) {
        if (off >= curr_blk->offset) {
            off = sizeof(block);
            get_next_block(curr_blk->next_id, curr_blk, curr_pg, f);
        }
        record *r = read_record_from_page(tb, curr_pg, off);
        off += get_record_size(tb);

        memcpy(string, "|", 2);
        for (int i = 0; i < num_cols; i++) {
            column *c = get_column_by_name(tb, view_cols[i]);
            switch (c->type) {
                case INTEGER:
                    string = integer_to_string(get_integer_record(tb, r, c->name), string);
                    break;
                case FLOAT:
                    string = float_to_string(get_float_record(tb, r, c->name), string);
                    break;
                case BOOL:
                    string = bool_to_string(get_boolean_record(tb, r, c->name), string);
                    break;
                case STRING:;
                    char *temp = get_string_record(tb, r, c->name);
                    string = string_to_string(temp, string);
                    free(temp);
                    break;
            }
        }

        bool flag = true;
        bool temp_flag = true;
        condition *temp = cond;
        enum next_relation next_relation = NONE;

        while (temp != NULL) {
            switch (temp->type) {
                case COLUMN_VALUE:
                    compare_column_value(&temp_flag, tb, r, temp, next_relation);
                    break;
                case COLUMN_COLUMN:
                    compare_column_column(&flag,tb,r,temp,next_relation);
                    break;
                case VALUE_VALUE:
                    compare_value_value(&flag,temp,next_relation);
                    break;
            }
            next_relation = temp->next_relation;
            temp = temp->next;
            if (next_relation == NONE) {
                flag = flag && temp_flag;
                temp_flag = true;
            }
        }

        if (flag) {
            if (buffer_offset < buff_sz) {
                memcpy(buffer + buffer_offset, string, strlen(string));
                buffer_offset += strlen(string);
                memcpy(buffer + buffer_offset, "\n", strlen("\n"));
                buffer_offset += strlen("\n");
                if (strlen(string) + 1 + buffer_offset >= buff_sz) {
                    memcpy(buffer + buffer_offset, "\0", strlen("\0"));

                    int32_t return_off = off + curr_blk->id * db->block_size;

                    free(string);
                    free(curr_blk);
                    destroy_page(curr_pg);

                    return return_off;
                }
            }
        }
        destroy_record(r);
    }
    free(string);
    free(curr_blk);
    destroy_page(curr_pg);
    return 0;
}

void select_records_from_table_inner_join(uint32_t *left_block_off,
                                          uint32_t *right_block_off,
                                          char *buffer,
                                          uint32_t buff_sz,
                                          table_to_join *left,
                                          table_to_join *right,
                                          condition* cond,
                                          database *db, FILE *f) {
    uint32_t buffer_offset = 0;

    table *left_table = left->tb;
    page *left_pg = allocate_page(db->block_size);
    uint32_t left_off = sizeof(block);
    if (*left_block_off == 0) {
        read_page_from_file(f, left_pg, left_table->first_record_block_id);
    } else {
        read_page_from_file(f, left_pg, *left_block_off / db->block_size);
        left_off = *left_block_off % db->block_size;
    }
    block *left_blk = read_block_from_page(left_pg);

    table *right_table = right->tb;
    page *right_pg = allocate_page(db->block_size);
    char *string = calloc(1, 2);

    memcpy(string, "|", 2);
    for (int i = 0; i < left->num_cols; i++) {
        char* temp = strdup(left->view_cols[i]);
        string = string_to_string(temp, string);
    }

    for (int i = 0; i < right->num_cols; i++) {
        char* temp = strdup(right->view_cols[i]);
        string = string_to_string(temp, string);
    }

    memcpy(buffer + buffer_offset, string, strlen(string));
    buffer_offset += strlen(string);
    memcpy(buffer + buffer_offset, "\n", strlen("\n"));
    buffer_offset += strlen("\n");
    memcpy(string, "|", 2);

    while ((left_blk->id != left_table->last_record_block_id) || (left_off < left_blk->offset)) {
        if (left_off >= left_blk->offset) {
            left_off = sizeof(block);
            get_next_block(left_blk->next_id, left_blk, left_pg, f);
        }
        record *left_r = read_record_from_page(left_table, left_pg, left_off);
        left_off += get_record_size(left_table);

        // RIGHT TABLE

        uint32_t right_off = sizeof(block);
        if (*right_block_off == 0) {
            read_page_from_file(f, right_pg, right_table->first_record_block_id);
        } else {
            read_page_from_file(f, right_pg, *right_block_off / db->block_size);
            right_off = *right_block_off % db->block_size;
        }
        block *right_blk = read_block_from_page(right_pg);

        while ((right_blk->id != right_table->last_record_block_id) || (right_off < right_blk->offset)) {
            if (right_off >= right_blk->offset) {
                right_off = sizeof(block);
                get_next_block(right_blk->next_id, right_blk, right_pg, f);
            }
            record *right_r = read_record_from_page(right_table, right_pg, right_off);
            right_off += get_record_size(right_table);

            bool join_flag = false;
            switch (left->col_to_join->type) {
                case INTEGER:;
                    int32_t l_i = get_integer_record(left_table, left_r, left->col_to_join->name);
                    int32_t r_i = get_integer_record(right_table, right_r, right->col_to_join->name);
                    if (check_integers(l_i, r_i, EQUAL)) {
                        join_flag = true;
                    }
                    break;
                case FLOAT:;
                    float l_f = get_float_record(left_table, left_r, left->col_to_join->name);
                    float r_f = get_float_record(right_table, right_r, right->col_to_join->name);
                    if (check_floats(l_f, r_f, EQUAL)) {
                        join_flag = true;
                    }
                    break;
                case BOOL:;
                    bool l_b = get_boolean_record(left_table, left_r, left->col_to_join->name);
                    bool r_b = get_boolean_record(right_table, right_r, right->col_to_join->name);
                    if (check_bools(l_b, r_b, EQUAL)) {
                        join_flag = true;
                    }
                    break;
                case STRING:;
                    char *l_s = get_string_record(left_table, left_r, left->col_to_join->name);
                    char *r_s = get_string_record(right_table, right_r, right->col_to_join->name);
                    if (check_strings(l_s, r_s, EQUAL)) {
                        join_flag = true;
                    }
                    break;
            }

            if (join_flag) {

                bool flag = true;
                bool temp_flag = true;
                condition *temp = cond;
                enum next_relation next_relation = NONE;

                while (temp != NULL) {
                    switch (temp->type) {
                        case COLUMN_VALUE:
                            switch (temp->left_operand->belongs_to_table) {
                                case LEFT:
                                    compare_column_value(&temp_flag, left_table, left_r, temp, next_relation);
                                    break;
                                case RIGHT:
                                    compare_column_value(&temp_flag, right_table, right_r, temp, next_relation);
                                    break;
                            }
                            break;
                        case COLUMN_COLUMN:
                            compare_column_column_join(&temp_flag, left_table, right_table, left_r, right_r, temp, next_relation);
                            break;
                        case VALUE_VALUE:
                            compare_value_value(&temp_flag, temp, next_relation);
                            break;
                    }
                    next_relation = temp->next_relation;
                    temp = temp->next;
                    if (next_relation == NONE) {
                        flag = flag && temp_flag;
                        temp_flag = true;
                    }
                }

                if (flag) {
                    memcpy(string, "|", 2);
                    for (int i = 0; i < left->num_cols; i++) {
                        column *c = get_column_by_name(left_table, left->view_cols[i]);
                        switch (c->type) {
                            case INTEGER:
                                string = integer_to_string(get_integer_record(left_table, left_r, c->name), string);
                                break;
                            case FLOAT:
                                string = float_to_string(get_float_record(left_table, left_r, c->name), string);
                                break;
                            case BOOL:
                                string = bool_to_string(get_boolean_record(left_table, left_r, c->name), string);
                                break;
                            case STRING:;
                                char *temp = get_string_record(left_table, left_r, c->name);
                                string = string_to_string(temp, string);
                                free(temp);
                                break;
                        }
                    }
                    for (int i = 0; i < right->num_cols; i++) {
                        column *c = get_column_by_name(right_table, right->view_cols[i]);
                        switch (c->type) {
                            case INTEGER:
                                string = integer_to_string(get_integer_record(right_table, right_r, c->name), string);
                                break;
                            case FLOAT:
                                string = float_to_string(get_float_record(right_table, right_r, c->name), string);
                                break;
                            case BOOL:
                                string = bool_to_string(get_boolean_record(right_table, right_r, c->name), string);
                                break;
                            case STRING:;
                                char *temp = get_string_record(right_table, right_r, c->name);
                                string = string_to_string(temp, string);
                                free(temp);
                                break;
                        }
                    }

                    if (buffer_offset < buff_sz) {
                        memcpy(buffer + buffer_offset, string, strlen(string));
                        buffer_offset += strlen(string);
                        memcpy(buffer + buffer_offset, "\n", strlen("\n"));
                        buffer_offset += strlen("\n");
                        if (strlen(string) + 1 + buffer_offset >= buff_sz) {
                            memcpy(buffer + buffer_offset, "\0", strlen("\0"));
                            *left_block_off = left_off + left_blk->id * db->block_size;
                            *right_block_off = right_off + right_blk->id * db->block_size;
                            return;
                        }
                    }
                }

            }
            destroy_record(right_r);

        }
        free(right_blk);
        destroy_record(left_r);
    }
    *left_block_off = 0;
    free(string);
    free(left_blk);
    destroy_page(left_pg);
    destroy_page(right_pg);
}

void update_records_in_table(column_to_update *col, condition *cond, table *tb, database *db, FILE *f) {
    page *curr_pg = allocate_page(db->block_size);
    read_page_from_file(f, curr_pg, tb->first_record_block_id);
    block *curr_blk = read_block_from_page(curr_pg);

    uint32_t off = sizeof(block);

    for (uint32_t read_rows = 0; read_rows < tb->num_rows; read_rows++) {
        if (off >= curr_blk->offset) {
            off = sizeof(block);
            get_next_block(curr_blk->next_id, curr_blk, curr_pg, f);
        }
        record *r = read_record_from_page(tb, curr_pg, off);

        bool flag = true;
        bool temp_flag = true;
        condition *temp = cond;
        enum next_relation next_relation = NONE;

        while (temp != NULL) {
            switch (temp->type) {
                case COLUMN_VALUE:
                    compare_column_value(&temp_flag, tb, r, temp, next_relation);
                    break;
                case COLUMN_COLUMN:
                    compare_column_column(&flag,tb,r,temp,next_relation);
                    break;
                case VALUE_VALUE:
                    compare_value_value(&flag,temp,next_relation);
                    break;
            }
            next_relation = temp->next_relation;
            temp = temp->next;
            if (next_relation == NONE) {
                flag = flag && temp_flag;
                temp_flag = true;
            }
        }

        if (flag) {
            column_to_update *temp_col = col;
            while (temp_col != NULL) {

                switch (temp_col->type) {
                    case INTEGER:
                        insert_integer_record(tb, r, temp_col->col_name, temp_col->value->i);
                        break;
                    case FLOAT:
                        insert_float_record(tb, r, temp_col->col_name, temp_col->value->f);
                        break;
                    case BOOL:
                        insert_boolean_record(tb, r, temp_col->col_name, temp_col->value->b);
                        break;
                    case STRING:
                        insert_string_record(tb, r, temp_col->col_name, temp_col->value->s);
                        break;
                }

                temp_col = temp_col->next;
            }
            write_record_to_page(r, curr_pg, off, get_columns_size(tb));
            write_page_to_file(f, curr_pg, curr_blk->id);

        }
        free(r);
        off += get_record_size(tb);
    }

}

void delete_records_from_table(condition *cond, table *tb, database *db, FILE *f) {

    uint32_t pre_id = tb->first_record_block_id;

    page *curr_pg = allocate_page(db->block_size);
    read_page_from_file(f, curr_pg, tb->first_record_block_id);
    block *curr_blk = read_block_from_page(curr_pg);

    uint32_t next_id = curr_blk->next_id;

    page *last_pg = allocate_page(db->block_size);
    read_page_from_file(f, last_pg, tb->last_record_block_id);
    block *last_blk = read_block_from_page(last_pg);

    uint32_t deleted_rows = 0;
    uint32_t off = sizeof(block);

    bool block_flag = false;

    for (uint32_t i = 0; i < tb->num_rows; i++) {

        record *r = read_record_from_page(tb, curr_pg, off);

        bool flag = true;
        bool temp_flag = true;
        condition *temp = cond;
        enum next_relation next_relation = NONE;

        while (temp != NULL) {
            switch (temp->type) {
                case COLUMN_VALUE:
                    compare_column_value(&temp_flag, tb, r, temp, next_relation);
                    break;
                case COLUMN_COLUMN:
                    compare_column_column(&flag,tb,r,temp,next_relation);
                    break;
                case VALUE_VALUE:
                    compare_value_value(&flag,temp,next_relation);
                    break;
            }
            next_relation = temp->next_relation;
            temp = temp->next;
            if (next_relation == NONE) {
                flag = flag && temp_flag;
                temp_flag = true;
            }
        }

        if (flag) {
            block_flag = true;
            r->valid = false;
            write_record_to_page(r, curr_pg, off, get_columns_size(tb));
            deleted_rows++;
        }
        off += get_record_size(tb);

        if (off >= curr_blk->offset || i + 1 >= tb->num_rows) {
            if (block_flag) {
                if (pre_id != curr_blk->id) {
                    page *pre_pg = allocate_page(db->block_size);
                    read_page_from_file(f, pre_pg, pre_id);
                    block *pre_blk = read_block_from_page(pre_pg);

                    pre_blk->next_id = curr_blk->next_id;

                    write_block_to_page(pre_blk, pre_pg);
                    write_page_to_file(f, pre_pg, pre_id);

                    free(pre_blk);
                    free(pre_pg);
                } else {
                    tb->first_record_block_id = curr_blk->next_id;
                }
                next_id = curr_blk->next_id;
                write_to_last_record_block(f,
                                           curr_pg,
                                           curr_blk,
                                           last_pg,
                                           last_blk,
                                           tb,
                                           db);

                block_flag = false;
            }

            off = sizeof(block);
            pre_id = curr_blk->id;
            get_next_block(next_id, curr_blk, curr_pg, f);
        }
        free(r);
    }
    tb->num_rows -= deleted_rows;

    page *pg = allocate_page(db->block_size);
    read_page_from_file(f, pg, tb->block_id);
    write_table_to_page(tb, pg, tb->offset);
    write_page_to_file(f, pg, tb->block_id);
}