//
// Created by stele on 26/03/23.
//

#include "server_transport.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


query_to_execute* server_decode_json(char* s) {
    query_to_execute* qte = malloc(sizeof(query_to_execute));

    json_t* root;
    json_error_t error;
    root = json_loads(s,0,&error);

    json_t* aql_query_type = json_object_get(root, "query_type");
    json_unpack(aql_query_type, "i", &qte->query_type);

    json_t* tbl = json_object_get(root, "table");
    json_t* table_name = json_object_get(tbl, "name");
    json_unpack(table_name, "s", &qte->table_name);

    json_t* params = json_object_get(tbl, "params");
    column* cols[json_array_size(params)];

    json_t* return_value = json_object_get(root, "return_value");
    json_unpack(return_value, "i", &qte->return_value);


    switch (qte->query_type) {
        case CREATE_TBL:;
            qte->createTableQuery = malloc(sizeof(create_table_query));
            json_unpack(table_name, "s", &(qte->createTableQuery->name));
            for(int i = 0; i< json_array_size(params); i++){
                json_t* col = json_array_get(params, i);
                char* col_name;
                enum data_type col_type;
                uint16_t col_size;


                json_unpack(col, "{s:s, s:i, s:i}", "name", &col_name, "column_type", &col_type, "column_size", &col_size);
                column* col_to_add = create_column(col_name, col_type, col_size);
                cols[i] = col_to_add;
            }
            qte->createTableQuery->cols = cols;
            qte->createTableQuery->num_cols = json_array_size(params);
            break;
        case REMOVE_TBL:
            qte->table_name = table_name;
            break;
        case INSERT_R:
            qte->insertRecordQuery = malloc(sizeof(insert_record_query));
            json_unpack(table_name, "s", &(qte->insertRecordQuery->table_name));
            json_t* ir_j = json_object_get(root, "insert_type");
            json_unpack(ir_j, "i", &(qte->insertRecordQuery->ins_type));
            record_field* ir_temp;
            record_field* recordField;
            literal* ir_literal;
            for (int i = 0; i < json_array_size(params); ++i) {
                json_t* col = json_array_get(params, i);

                char* col_name;
                json_t* col_name_j = json_object_get(col, "name");
                json_unpack(col_name_j, "s", &col_name);

                enum data_type col_type;
                json_t* col_type_j = json_object_get(col, "type");
                json_unpack(col_type_j, "i", &col_type);

                switch (col_type) {
                    case INTEGER:;
                        int32_t num;
                        json_t* i_j = json_object_get(col, "value");
                        json_unpack(i_j, "i", &num);
                        ir_literal = create_integer_literal(num);
                        if (i == 0) {
                            ir_temp = create_record_field(col_name, ir_literal);
                            recordField=ir_temp;
                        } else {
                            ir_temp->next = create_record_field(col_name, ir_literal);
                            ir_temp = ir_temp->next;
                        }
                        break;
                    case FLOAT:;
                        float f;
                        json_t* f_j = json_object_get(col, "value");
                        json_unpack(f_j, "f", &f);
                        ir_literal = create_float_literal(f);
                        if (i == 0) {
                            ir_temp = create_record_field(col_name, ir_literal);
                            recordField=ir_temp;
                        } else {
                            ir_temp->next = create_record_field(col_name, ir_literal);
                            ir_temp = ir_temp->next;
                        }
                        break;
                    case BOOL:;
                        bool b;
                        json_t* b_j = json_object_get(col, "value");
                        json_unpack(b_j, "i", &b);
                        ir_literal = create_boolean_literal(b);
                        if (i == 0) {
                            ir_temp = create_record_field(col_name, ir_literal);
                            recordField=ir_temp;
                        } else {
                            ir_temp->next = create_record_field(col_name, ir_literal);
                            ir_temp = ir_temp->next;
                        }
                        break;
                    case STRING:;
                        char* s;
                        json_t* s_j = json_object_get(col, "value");
                        json_unpack(s_j, "s", &s);
                        ir_literal = create_string_literal(s);
                        if (i == 0) {
                            ir_temp = create_record_field(col_name, ir_literal);
                            recordField=ir_temp;
                        } else {
                            ir_temp->next = create_record_field(col_name, ir_literal);
                            ir_temp = ir_temp->next;
                        }
                        break;
                }
            }
            qte->insertRecordQuery->rec = recordField;
            break;
        case UPDATE_R: {
            json_t *filters = json_object_get(tbl, "filters");
            condition *query_condition;
            condition *temp_query_condition;
            for (int i = 0; i < json_array_size(filters); i++) {
                json_t *filter = json_array_get(filters, i);
                for (int k = 0; k < json_array_size(filter); k++) {
                    json_t *rrf_cond = json_array_get(filter, k);

                    json_t *relation_type = json_object_get(rrf_cond, "comparison_type");
                    json_t *relation = json_object_get(rrf_cond, "comparison");
                    json_t *next_relation = json_object_get(rrf_cond, "relation");
                    enum condition_type rrf_ct;
                    enum relation rrf_r;
                    enum next_relation rrf_nr;
                    json_unpack(relation_type, "i", &rrf_ct);
                    json_unpack(relation, "i", &rrf_r);
                    json_unpack(next_relation, "i", &rrf_nr);

                    json_t *left_operand = json_object_get(rrf_cond, "left_operand");
                    json_t *left_operand_type = json_object_get(left_operand, "type");
                    json_t *left_operand_value = json_object_get(left_operand, "value");
                    enum data_type l_dt;
                    json_unpack(left_operand_type, "i", &l_dt);

                    condition_operand *rrf_lo;
                    switch (l_dt) {
                        case INTEGER:;
                            int32_t rrf_i;
                            json_unpack(left_operand_value, "i", &rrf_i);
                            rrf_lo = create_condition_integer_operand(rrf_i, LEFT);
                            break;
                        case FLOAT:;
                            float rrf_f;
                            json_unpack(left_operand_value, "f", &rrf_f);
                            rrf_lo = create_condition_float_operand(rrf_f, LEFT);
                            break;
                        case BOOL:;
                            bool rrf_b;
                            json_unpack(left_operand_value, "i", &rrf_b);
                            rrf_lo = create_condition_bool_operand(rrf_b, LEFT);
                            break;
                        case STRING:;
                            char *rrf_s;
                            json_unpack(left_operand_value, "s", &rrf_s);
                            rrf_lo = create_condition_string_operand(rrf_s, LEFT);
                            break;
                        case REFERENCE:;
                            char *rrf_reference;
                            json_unpack(left_operand_value, "s", &rrf_reference);
                            rrf_lo = create_condition_string_operand(rrf_reference, LEFT);
                            break;
                    }

                    json_t *right_operand = json_object_get(rrf_cond, "right_operand");
                    json_t *right_operand_type = json_object_get(right_operand, "type");
                    json_t *right_operand_value = json_object_get(right_operand, "value");
                    enum data_type r_dt;
                    json_unpack(right_operand_type, "i", &r_dt);

                    condition_operand *rrf_ro;
                    switch (r_dt) {
                        case INTEGER:;
                            int32_t rrf_i;
                            json_unpack(right_operand_value, "i", &rrf_i);
                            rrf_ro = create_condition_integer_operand(rrf_i, LEFT);
                            break;
                        case FLOAT:;
                            float rrf_f;
                            json_unpack(right_operand_value, "f", &rrf_f);
                            rrf_ro = create_condition_float_operand(rrf_f, LEFT);
                            break;
                        case BOOL:;
                            bool rrf_b;
                            json_unpack(right_operand_value, "i", &rrf_b);
                            rrf_ro = create_condition_bool_operand(rrf_b, LEFT);
                            break;
                        case STRING:;
                            char *rrf_s;
                            json_unpack(right_operand_value, "s", &rrf_s);
                            rrf_ro = create_condition_string_operand(rrf_s, LEFT);
                            break;
                        case REFERENCE:
                            break;
                    }

                    if (i == 0 && k == 0) {
                        temp_query_condition = create_condition(rrf_ct, rrf_lo, rrf_ro, rrf_r, rrf_nr);
                        query_condition = temp_query_condition;

                    } else {
                        temp_query_condition->next = create_condition(rrf_ct, rrf_lo, rrf_ro, rrf_r, rrf_nr);
                        temp_query_condition = temp_query_condition->next;
                    }

                }
            }
            qte->condition = query_condition;
            break;
        }
        case REMOVE_R:
        {
            json_t *filters = json_object_get(tbl, "filters");
            condition *query_condition;
            condition *temp_query_condition;
            for (int i = 0; i < json_array_size(filters); i++) {
                json_t *filter = json_array_get(filters, i);
                for (int k = 0; k < json_array_size(filter); k++) {
                    json_t *rrf_cond = json_array_get(filter, k);

                    json_t *relation_type = json_object_get(rrf_cond, "comparison_type");
                    json_t *relation = json_object_get(rrf_cond, "comparison");
                    json_t *next_relation = json_object_get(rrf_cond, "relation");
                    enum condition_type rrf_ct;
                    enum relation rrf_r;
                    enum next_relation rrf_nr;
                    json_unpack(relation_type, "i", &rrf_ct);
                    json_unpack(relation, "i", &rrf_r);
                    json_unpack(next_relation, "i", &rrf_nr);

                    json_t *left_operand = json_object_get(rrf_cond, "left_operand");
                    json_t *left_operand_type = json_object_get(left_operand, "type");
                    json_t *left_operand_value = json_object_get(left_operand, "value");
                    enum data_type l_dt;
                    json_unpack(left_operand_type, "i", &l_dt);

                    condition_operand *rrf_lo;
                    switch (l_dt) {
                        case INTEGER:;
                            int32_t rrf_i;
                            json_unpack(left_operand_value, "i", &rrf_i);
                            rrf_lo = create_condition_integer_operand(rrf_i, LEFT);
                            break;
                        case FLOAT:;
                            float rrf_f;
                            json_unpack(left_operand_value, "f", &rrf_f);
                            rrf_lo = create_condition_float_operand(rrf_f, LEFT);
                            break;
                        case BOOL:;
                            bool rrf_b;
                            json_unpack(left_operand_value, "i", &rrf_b);
                            rrf_lo = create_condition_bool_operand(rrf_b, LEFT);
                            break;
                        case STRING:;
                            char *rrf_s;
                            json_unpack(left_operand_value, "s", &rrf_s);
                            rrf_lo = create_condition_string_operand(rrf_s, LEFT);
                            break;
                        case REFERENCE:;
                            char *rrf_reference;
                            json_unpack(left_operand_value, "s", &rrf_reference);
                            rrf_lo = create_condition_string_operand(rrf_reference, LEFT);
                            break;
                    }

                    json_t *right_operand = json_object_get(rrf_cond, "right_operand");
                    json_t *right_operand_type = json_object_get(right_operand, "type");
                    json_t *right_operand_value = json_object_get(right_operand, "value");
                    enum data_type r_dt;
                    json_unpack(right_operand_type, "i", &r_dt);

                    condition_operand *rrf_ro;
                    switch (r_dt) {
                        case INTEGER:;
                            int32_t rrf_i;
                            json_unpack(right_operand_value, "i", &rrf_i);
                            rrf_ro = create_condition_integer_operand(rrf_i, LEFT);
                            break;
                        case FLOAT:;
                            float rrf_f;
                            json_unpack(right_operand_value, "f", &rrf_f);
                            rrf_ro = create_condition_float_operand(rrf_f, LEFT);
                            break;
                        case BOOL:;
                            bool rrf_b;
                            json_unpack(right_operand_value, "i", &rrf_b);
                            rrf_ro = create_condition_bool_operand(rrf_b, LEFT);
                            break;
                        case STRING:;
                            char *rrf_s;
                            json_unpack(right_operand_value, "s", &rrf_s);
                            rrf_ro = create_condition_string_operand(rrf_s, LEFT);
                            break;
                        case REFERENCE:
                            break;
                    }

                    if (i == 0 && k == 0) {
                        temp_query_condition = create_condition(rrf_ct, rrf_lo, rrf_ro, rrf_r, rrf_nr);
                        query_condition = temp_query_condition;

                    } else {
                        temp_query_condition->next = create_condition(rrf_ct, rrf_lo, rrf_ro, rrf_r, rrf_nr);
                        temp_query_condition = temp_query_condition->next;
                    }

                }
            }
            qte->condition = query_condition;
            break;
        }
        case RETURN_R:;
            json_t* return_record_type = json_object_get(root, "return_type");
            json_unpack(return_record_type, "i", &qte->ret_type);

            switch (qte->ret_type) {
                case RETURN_ROW:;
                    break;
                case RETURN_ROW_FILTER: {
                    json_t* filters = json_object_get(tbl, "filters");
                    condition *query_condition;
                    condition *temp_query_condition;
                    for (int i = 0; i < json_array_size(filters); i++) {
                        json_t *filter = json_array_get(filters, i);
                        for (int k = 0; k < json_array_size(filter); k++) {
                            json_t *rrf_cond = json_array_get(filter, k);

                            json_t *relation_type = json_object_get(rrf_cond, "comparison_type");
                            json_t *relation = json_object_get(rrf_cond, "comparison");
                            json_t *next_relation = json_object_get(rrf_cond, "relation");
                            enum condition_type rrf_ct;
                            enum relation rrf_r;
                            enum next_relation rrf_nr;
                            json_unpack(relation_type, "i", &rrf_ct);
                            json_unpack(relation, "i", &rrf_r);
                            json_unpack(next_relation, "i", &rrf_nr);

                            json_t *left_operand = json_object_get(rrf_cond, "left_operand");
                            json_t *left_operand_type = json_object_get(left_operand, "type");
                            json_t *left_operand_value = json_object_get(left_operand, "value");
                            enum data_type l_dt;
                            json_unpack(left_operand_type, "i", &l_dt);

                            condition_operand *rrf_lo;
                            switch (l_dt) {
                                case INTEGER:;
                                    int32_t rrf_i;
                                    json_unpack(left_operand_value, "i", &rrf_i);
                                    rrf_lo = create_condition_integer_operand(rrf_i, LEFT);
                                    break;
                                case FLOAT:;
                                    float rrf_f;
                                    json_unpack(left_operand_value, "f", &rrf_f);
                                    rrf_lo = create_condition_float_operand(rrf_f, LEFT);
                                    break;
                                case BOOL:;
                                    bool rrf_b;
                                    json_unpack(left_operand_value, "i", &rrf_b);
                                    rrf_lo = create_condition_bool_operand(rrf_b, LEFT);
                                    break;
                                case STRING:;
                                    char *rrf_s;
                                    json_unpack(left_operand_value, "s", &rrf_s);
                                    rrf_lo = create_condition_string_operand(rrf_s, LEFT);
                                    break;
                                case REFERENCE:;
                                    char *rrf_reference;
                                    json_unpack(left_operand_value, "s", &rrf_reference);
                                    rrf_lo = create_condition_string_operand(rrf_reference, LEFT);
                                    break;
                            }

                            json_t *right_operand = json_object_get(rrf_cond, "right_operand");
                            json_t *right_operand_type = json_object_get(right_operand, "type");
                            json_t *right_operand_value = json_object_get(right_operand, "value");
                            enum data_type r_dt;
                            json_unpack(right_operand_type, "i", &r_dt);

                            condition_operand *rrf_ro;
                            switch (r_dt) {
                                case INTEGER:;
                                    int32_t rrf_i;
                                    json_unpack(right_operand_value, "i", &rrf_i);
                                    rrf_ro = create_condition_integer_operand(rrf_i, LEFT);
                                    break;
                                case FLOAT:;
                                    float rrf_f;
                                    json_unpack(right_operand_value, "f", &rrf_f);
                                    rrf_ro = create_condition_float_operand(rrf_f, LEFT);
                                    break;
                                case BOOL:;
                                    bool rrf_b;
                                    json_unpack(right_operand_value, "i", &rrf_b);
                                    rrf_ro = create_condition_bool_operand(rrf_b, LEFT);
                                    break;
                                case STRING:;
                                    char *rrf_s;
                                    json_unpack(right_operand_value, "s", &rrf_s);
                                    rrf_ro = create_condition_string_operand(rrf_s, LEFT);
                                    break;
                                case REFERENCE:
                                    break;
                            }

                            if (i == 0 && k == 0) {
                                temp_query_condition = create_condition(rrf_ct, rrf_lo, rrf_ro, rrf_r, rrf_nr);
                                query_condition = temp_query_condition;

                            } else {
                                temp_query_condition->next = create_condition(rrf_ct, rrf_lo, rrf_ro, rrf_r, rrf_nr);
                                temp_query_condition = temp_query_condition->next;
                            }

                        }
                    }
                    qte->condition = query_condition;
                    break;
                }
                case RETURN_FIELDS:
                    break;
                case RETURN_FIELDS_FILTER:{
                    json_t* filters = json_object_get(tbl, "filters");
                    condition *query_condition;
                    condition *temp_query_condition;
                    for (int i = 0; i < json_array_size(filters); i++) {
                        json_t *filter = json_array_get(filters, i);
                        for (int k = 0; k < json_array_size(filter); k++) {
                            json_t *rrf_cond = json_array_get(filter, k);

                            json_t *relation_type = json_object_get(rrf_cond, "comparison_type");
                            json_t *relation = json_object_get(rrf_cond, "comparison");
                            json_t *next_relation = json_object_get(rrf_cond, "relation");
                            enum condition_type rrf_ct;
                            enum relation rrf_r;
                            enum next_relation rrf_nr;
                            json_unpack(relation_type, "i", &rrf_ct);
                            json_unpack(relation, "i", &rrf_r);
                            json_unpack(next_relation, "i", &rrf_nr);

                            json_t *left_operand = json_object_get(rrf_cond, "left_operand");
                            json_t *left_operand_type = json_object_get(left_operand, "type");
                            json_t *left_operand_value = json_object_get(left_operand, "value");
                            enum data_type l_dt;
                            json_unpack(left_operand_type, "i", &l_dt);

                            condition_operand *rrf_lo;
                            switch (l_dt) {
                                case INTEGER:;
                                    int32_t rrf_i;
                                    json_unpack(left_operand_value, "i", &rrf_i);
                                    rrf_lo = create_condition_integer_operand(rrf_i, LEFT);
                                    break;
                                case FLOAT:;
                                    float rrf_f;
                                    json_unpack(left_operand_value, "f", &rrf_f);
                                    rrf_lo = create_condition_float_operand(rrf_f, LEFT);
                                    break;
                                case BOOL:;
                                    bool rrf_b;
                                    json_unpack(left_operand_value, "i", &rrf_b);
                                    rrf_lo = create_condition_bool_operand(rrf_b, LEFT);
                                    break;
                                case STRING:;
                                    char *rrf_s;
                                    json_unpack(left_operand_value, "s", &rrf_s);
                                    rrf_lo = create_condition_string_operand(rrf_s, LEFT);
                                    break;
                                case REFERENCE:;
                                    char *rrf_reference;
                                    json_unpack(left_operand_value, "s", &rrf_reference);
                                    rrf_lo = create_condition_string_operand(rrf_reference, LEFT);
                                    break;
                            }

                            json_t *right_operand = json_object_get(rrf_cond, "right_operand");
                            json_t *right_operand_type = json_object_get(right_operand, "type");
                            json_t *right_operand_value = json_object_get(right_operand, "value");
                            enum data_type r_dt;
                            json_unpack(right_operand_type, "i", &r_dt);

                            condition_operand *rrf_ro;
                            switch (r_dt) {
                                case INTEGER:;
                                    int32_t rrf_i;
                                    json_unpack(right_operand_value, "i", &rrf_i);
                                    rrf_ro = create_condition_integer_operand(rrf_i, LEFT);
                                    break;
                                case FLOAT:;
                                    float rrf_f;
                                    json_unpack(right_operand_value, "f", &rrf_f);
                                    rrf_ro = create_condition_float_operand(rrf_f, LEFT);
                                    break;
                                case BOOL:;
                                    bool rrf_b;
                                    json_unpack(right_operand_value, "i", &rrf_b);
                                    rrf_ro = create_condition_bool_operand(rrf_b, LEFT);
                                    break;
                                case STRING:;
                                    char *rrf_s;
                                    json_unpack(right_operand_value, "s", &rrf_s);
                                    rrf_ro = create_condition_string_operand(rrf_s, LEFT);
                                    break;
                                case REFERENCE:
                                    break;
                            }

                            if (i == 0 && k == 0) {
                                temp_query_condition = create_condition(rrf_ct, rrf_lo, rrf_ro, rrf_r, rrf_nr);
                                query_condition = temp_query_condition;

                            } else {
                                temp_query_condition->next = create_condition(rrf_ct, rrf_lo, rrf_ro, rrf_r, rrf_nr);
                                temp_query_condition = temp_query_condition->next;
                            }

                        }
                    }
                    qte->condition = query_condition;
                    break;
                }
                case RETURN_ROW_JOIN:
                    break;
                case RETURN_ROW_JOIN_FILTER:{
                    json_t* filters = json_object_get(tbl, "filters");
                    condition *query_condition;
                    condition *temp_query_condition;
                    for (int i = 0; i < json_array_size(filters); i++) {
                        json_t *filter = json_array_get(filters, i);
                        for (int k = 0; k < json_array_size(filter); k++) {
                            json_t *rrf_cond = json_array_get(filter, k);

                            json_t *relation_type = json_object_get(rrf_cond, "comparison_type");
                            json_t *relation = json_object_get(rrf_cond, "comparison");
                            json_t *next_relation = json_object_get(rrf_cond, "relation");
                            enum condition_type rrf_ct;
                            enum relation rrf_r;
                            enum next_relation rrf_nr;
                            json_unpack(relation_type, "i", &rrf_ct);
                            json_unpack(relation, "i", &rrf_r);
                            json_unpack(next_relation, "i", &rrf_nr);

                            json_t *left_operand = json_object_get(rrf_cond, "left_operand");
                            json_t *left_operand_type = json_object_get(left_operand, "type");
                            json_t *left_operand_value = json_object_get(left_operand, "value");
                            enum data_type l_dt;
                            json_unpack(left_operand_type, "i", &l_dt);

                            condition_operand *rrf_lo;
                            switch (l_dt) {
                                case INTEGER:;
                                    int32_t rrf_i;
                                    json_unpack(left_operand_value, "i", &rrf_i);
                                    rrf_lo = create_condition_integer_operand(rrf_i, LEFT);
                                    break;
                                case FLOAT:;
                                    float rrf_f;
                                    json_unpack(left_operand_value, "f", &rrf_f);
                                    rrf_lo = create_condition_float_operand(rrf_f, LEFT);
                                    break;
                                case BOOL:;
                                    bool rrf_b;
                                    json_unpack(left_operand_value, "i", &rrf_b);
                                    rrf_lo = create_condition_bool_operand(rrf_b, LEFT);
                                    break;
                                case STRING:;
                                    char *rrf_s;
                                    json_unpack(left_operand_value, "s", &rrf_s);
                                    rrf_lo = create_condition_string_operand(rrf_s, LEFT);
                                    break;
                                case REFERENCE:;
                                    char *rrf_reference;
                                    json_unpack(left_operand_value, "s", &rrf_reference);
                                    rrf_lo = create_condition_string_operand(rrf_reference, LEFT);
                                    break;
                            }

                            json_t *right_operand = json_object_get(rrf_cond, "right_operand");
                            json_t *right_operand_type = json_object_get(right_operand, "type");
                            json_t *right_operand_value = json_object_get(right_operand, "value");
                            enum data_type r_dt;
                            json_unpack(right_operand_type, "i", &r_dt);

                            condition_operand *rrf_ro;
                            switch (r_dt) {
                                case INTEGER:;
                                    int32_t rrf_i;
                                    json_unpack(right_operand_value, "i", &rrf_i);
                                    rrf_ro = create_condition_integer_operand(rrf_i, LEFT);
                                    break;
                                case FLOAT:;
                                    float rrf_f;
                                    json_unpack(right_operand_value, "f", &rrf_f);
                                    rrf_ro = create_condition_float_operand(rrf_f, LEFT);
                                    break;
                                case BOOL:;
                                    bool rrf_b;
                                    json_unpack(right_operand_value, "i", &rrf_b);
                                    rrf_ro = create_condition_bool_operand(rrf_b, LEFT);
                                    break;
                                case STRING:;
                                    char *rrf_s;
                                    json_unpack(right_operand_value, "s", &rrf_s);
                                    rrf_ro = create_condition_string_operand(rrf_s, LEFT);
                                    break;
                                case REFERENCE:
                                    break;
                            }

                            if (i == 0 && k == 0) {
                                temp_query_condition = create_condition(rrf_ct, rrf_lo, rrf_ro, rrf_r, rrf_nr);
                                query_condition = temp_query_condition;

                            } else {
                                temp_query_condition->next = create_condition(rrf_ct, rrf_lo, rrf_ro, rrf_r, rrf_nr);
                                temp_query_condition = temp_query_condition->next;
                            }

                        }
                    }
                    qte->condition = query_condition;
                    break;
                }
                case RETURN_FIELDS_JOIN: {

                    qte->returnRecordsQuery = malloc(sizeof(return_records_query));
                    qte->returnRecordsQuery->left = malloc(sizeof(return_records_table));
                    qte->returnRecordsQuery->right = malloc(sizeof(return_records_table));

                    json_t *tables = json_object_get(root, "tables");
                    json_t *left_table = json_array_get(tables, 0);
                    json_t *right_table = json_array_get(tables, 1);

                    json_t *left_table_name = json_object_get(left_table, "name");
                    json_t *left_joint_column = json_object_get(left_table, "joint_column");
                    json_t *left_return_columns = json_object_get(left_table, "return_columns");

                    json_unpack(left_table_name, "s", &qte->returnRecordsQuery->left->table_name);
                    json_unpack(left_joint_column, "s", &qte->returnRecordsQuery->left->joint_column_name);

                    qte->returnRecordsQuery->left->num_cols = json_array_size(left_return_columns);
                    qte->returnRecordsQuery->left->return_columns = malloc(json_array_size(left_return_columns));

                    for (int i = 0; i < json_array_size(left_return_columns); i++) {
                        json_t *return_column = json_array_get(left_return_columns, i);
                        json_t *json_return_column_name = json_object_get(return_column, "name");
                        char *return_column_name;
                        json_unpack(json_return_column_name, "s", &return_column_name);

                        qte->returnRecordsQuery->left->return_columns[i] = malloc(strlen(return_column_name) + 1);
                        strcpy(qte->returnRecordsQuery->left->return_columns[i], return_column_name);
                    }

                    json_t *right_table_name = json_object_get(right_table, "name");
                    json_t *right_joint_column = json_object_get(right_table, "joint_column");
                    json_t *right_return_columns = json_object_get(right_table, "return_columns");

                    json_unpack(right_table_name, "s", &qte->returnRecordsQuery->right->table_name);
                    json_unpack(right_joint_column, "s", &qte->returnRecordsQuery->right->joint_column_name);

                    qte->returnRecordsQuery->right->num_cols = json_array_size(right_return_columns);
                    qte->returnRecordsQuery->right->return_columns = malloc(json_array_size(right_return_columns));

                    for (int i = 0; i < json_array_size(right_return_columns); i++) {
                        json_t *return_column = json_array_get(right_return_columns, i);
                        json_t *json_return_column_name = json_object_get(return_column, "name");
                        char *return_column_name;
                        json_unpack(json_return_column_name, "s", &return_column_name);

                        qte->returnRecordsQuery->right->return_columns[i] = malloc(strlen(return_column_name) + 1);
                        strcpy(qte->returnRecordsQuery->right->return_columns[i], return_column_name);
                    }

                    break;
                }
                case RETURN_FIELDS_JOIN_FILTER: {

                    qte->returnRecordsQuery = malloc(sizeof(return_records_query));
                    qte->returnRecordsQuery->left = malloc(sizeof(return_records_table));
                    qte->returnRecordsQuery->right = malloc(sizeof(return_records_table));

                    json_t* tables = json_object_get(root, "tables");
                    json_t* left_table = json_array_get(tables, 0);
                    json_t* right_table = json_array_get(tables, 1);

                    json_t* left_table_name = json_object_get(left_table, "name");
                    json_t* left_joint_column = json_object_get(left_table, "joint_column");
                    json_t* left_return_columns = json_object_get(left_table, "return_columns");

                    json_unpack(left_table_name, "s", &qte->returnRecordsQuery->left->table_name);
                    json_unpack(left_joint_column, "s", &qte->returnRecordsQuery->left->joint_column_name);

                    qte->returnRecordsQuery->left->num_cols = json_array_size(left_return_columns);
                    qte->returnRecordsQuery->left->return_columns = malloc(json_array_size(left_return_columns));

                    for (int i = 0; i < json_array_size(left_return_columns); i++) {
                        json_t* return_column = json_array_get(left_return_columns, i);
                        json_t* json_return_column_name = json_object_get(return_column, "name");
                        char* return_column_name;
                        json_unpack(json_return_column_name, "s", &return_column_name);

                        qte->returnRecordsQuery->left->return_columns[i] = malloc(strlen(return_column_name)+1);
                        strcpy(qte->returnRecordsQuery->left->return_columns[i], return_column_name);
                    }

                    json_t* right_table_name = json_object_get(right_table, "name");
                    json_t* right_joint_column = json_object_get(right_table, "joint_column");
                    json_t* right_return_columns = json_object_get(right_table, "return_columns");

                    json_unpack(right_table_name, "s", &qte->returnRecordsQuery->right->table_name);
                    json_unpack(right_joint_column, "s", &qte->returnRecordsQuery->right->joint_column_name);

                    qte->returnRecordsQuery->right->num_cols = json_array_size(right_return_columns);
                    qte->returnRecordsQuery->right->return_columns = malloc(json_array_size(right_return_columns));

                    for (int i = 0; i < json_array_size(right_return_columns); i++) {
                        json_t* return_column = json_array_get(right_return_columns, i);
                        json_t* json_return_column_name = json_object_get(return_column, "name");
                        char* return_column_name;
                        json_unpack(json_return_column_name, "s", &return_column_name);

                        qte->returnRecordsQuery->right->return_columns[i] = malloc(strlen(return_column_name)+1);
                        strcpy(qte->returnRecordsQuery->right->return_columns[i], return_column_name);
                    }

                    json_t* filters = json_object_get(root, "filters");

                    condition* query_condition;
                    condition* temp_query_condition;
                    for(int i = 0; i < json_array_size(filters); i++) {
                        json_t* filter = json_array_get(filters, i);
                        for(int k = 0; k < json_array_size(filter); k++) {
                            json_t* rrf_cond = json_array_get(filter, k);

                            json_t* relation_type = json_object_get(rrf_cond, "comparison_type");
                            json_t* relation = json_object_get(rrf_cond, "comparison");
                            json_t* next_relation = json_object_get(rrf_cond, "relation");
                            enum condition_type rrf_ct;
                            enum relation rrf_r;
                            enum next_relation rrf_nr;
                            json_unpack(relation_type, "i", &rrf_ct);
                            json_unpack(relation, "i", &rrf_r);
                            json_unpack(next_relation, "i", &rrf_nr);

                            json_t* left_operand = json_object_get(rrf_cond, "left_operand");
                            json_t* left_operand_type = json_object_get(left_operand, "type");
                            json_t* left_operand_value = json_object_get(left_operand, "value");
                            enum data_type l_dt;
                            json_unpack(left_operand_type, "i", &l_dt);

                            condition_operand* rrf_lo;
                            switch (l_dt) {
                                case INTEGER:;
                                    int32_t rrf_i;
                                    json_unpack(left_operand_value, "i", &rrf_i);
                                    rrf_lo = create_condition_integer_operand(rrf_i, LEFT);
                                    break;
                                case FLOAT:;
                                    float rrf_f;
                                    json_unpack(left_operand_value, "f", &rrf_f);
                                    rrf_lo = create_condition_float_operand(rrf_f, LEFT);
                                    break;
                                case BOOL:;
                                    bool rrf_b;
                                    json_unpack(left_operand_value, "i", &rrf_b);
                                    rrf_lo = create_condition_bool_operand(rrf_b, LEFT);
                                    break;
                                case STRING:;
                                    char* rrf_s;
                                    json_unpack(left_operand_value, "s", &rrf_s);
                                    rrf_lo = create_condition_string_operand(rrf_s, LEFT);
                                    break;
                                case REFERENCE:;
                                    char* rrf_reference;
                                    json_unpack(left_operand_value, "s", &rrf_reference);
                                    char* r_token = strtok(rrf_reference, ".");
                                    if(strcmp(r_token, qte->returnRecordsQuery->left->table_name) == 0) {
                                        r_token = strtok(NULL, ".");
                                        rrf_lo = create_condition_string_operand(r_token, LEFT);
                                    } else if (strcmp(r_token, qte->returnRecordsQuery->right->table_name) == 0) {
                                        r_token = strtok(NULL, ".");
                                        rrf_lo = create_condition_string_operand(r_token, RIGHT);
                                    }
                                    break;
                            }

                            json_t* right_operand = json_object_get(rrf_cond, "right_operand");
                            json_t* right_operand_type = json_object_get(right_operand, "type");
                            json_t* right_operand_value = json_object_get(right_operand, "value");
                            enum data_type r_dt;
                            json_unpack(right_operand_type, "i", &r_dt);

                            condition_operand* rrf_ro;
                            switch (r_dt) {
                                case INTEGER:;
                                    int32_t rrf_i;
                                    json_unpack(right_operand_value, "i", &rrf_i);
                                    rrf_ro = create_condition_integer_operand(rrf_i, LEFT);
                                    break;
                                case FLOAT:;
                                    float rrf_f;
                                    json_unpack(right_operand_value, "f", &rrf_f);
                                    rrf_ro = create_condition_float_operand(rrf_f, LEFT);
                                    break;
                                case BOOL:;
                                    bool rrf_b;
                                    json_unpack(right_operand_value, "i", &rrf_b);
                                    rrf_ro = create_condition_bool_operand(rrf_b, LEFT);
                                    break;
                                case STRING:;
                                    char* rrf_s;
                                    json_unpack(right_operand_value, "s", &rrf_s);
                                    rrf_ro = create_condition_string_operand(rrf_s, LEFT);
                                    break;
                                case REFERENCE:;
                                    char* rrf_reference;
                                    json_unpack(left_operand_value, "s", &rrf_reference);
                                    char* r_token = strtok(rrf_reference, ".");
                                    if(strcmp(r_token, qte->returnRecordsQuery->left->table_name) == 0) {
                                        r_token = strtok(NULL, ".");
                                        rrf_lo = create_condition_string_operand(r_token, LEFT);
                                    } else if (strcmp(r_token, qte->returnRecordsQuery->right->table_name) == 0) {
                                        r_token = strtok(NULL, ".");
                                        rrf_lo = create_condition_string_operand(r_token, RIGHT);
                                    }
                                    break;
                            }

                            if(i==0 && k==0) {
                                temp_query_condition = create_condition(rrf_ct, rrf_lo, rrf_ro, rrf_r, rrf_nr);
                                query_condition = temp_query_condition;

                            }else {
                                temp_query_condition->next = create_condition(rrf_ct, rrf_lo, rrf_ro, rrf_r, rrf_nr);
                                temp_query_condition = temp_query_condition->next;
                            }

                        }
                    }
                    qte->condition = query_condition;

                    break;
                }
            }
            break;
    }
    return qte;
}

record_field* create_record_field(char* name, literal* value){
    record_field* rf = malloc(sizeof(record_field));
    rf->name = name;
    rf->value = malloc(sizeof(literal));
    rf->value = value;
    return rf;
}

literal* create_integer_literal(int32_t i) {
    literal* l = malloc(sizeof(literal));
    l->type = INTEGER;
    l->value = malloc(sizeof(int32_t));
    l->value->i = i;
    return l;
}

literal* create_float_literal(float f) {
    literal* l = malloc(sizeof(literal));
    l->type = FLOAT;
    l->value = malloc(sizeof(float));
    l->value->f = f;
    return l;
}

literal* create_boolean_literal(bool b) {
    literal* l = malloc(sizeof(literal));
    l->type = BOOL;
    l->value = malloc(sizeof(bool));
    l->value->b = b;
    return l;
}

literal* create_string_literal(char* s) {
    literal* l = malloc(sizeof(literal));
    l->type = STRING;
    l->value = malloc(sizeof(char*));
    l->value->s = s;
    return l;
}

void execute_query(int connfd, database* db, FILE* f, char* buff, query_to_execute* qte){

    switch (qte->return_value) {
        case OK:
            switch (qte->query_type) {
                case CREATE_TBL: {
                    table *t = create_table(qte->createTableQuery->name, qte->createTableQuery->num_cols,
                                            qte->createTableQuery->cols);
                    insert_table_to_schema(t, db, f);
                    initialize_table_record_block(t, db, f);
                    //json_t* resp = response_to_json(OK);
                    //strcpy(buff, resp);
                    strcpy(buff, "OK");
                    write(connfd, buff, sizeof(buff));
                    memset(buff, '\0', MAX);
                    break;
                }
                case REMOVE_TBL: {
                    delete_table_from_schema(qte->table_name, db, f);
                    //json_t* resp = response_to_json(OK);
                    //strcpy(buff, resp);
                    strcpy(buff, "OK");
                    write(connfd, buff, sizeof(buff));
                    memset(buff, '\0', MAX);
                    break;
                }
                case INSERT_R: {
                    table *tb = get_table_from_schema(qte->table_name, db, f);
                    record *rec = create_record(tb);
                    record_field *temp_rf = qte->insertRecordQuery->rec;
                    while (temp_rf != NULL) {

                        switch (temp_rf->value->type) {
                            case INTEGER:
                                insert_integer_record(tb, rec, temp_rf->name, temp_rf->value->value->i);
                                break;
                            case FLOAT:
                                insert_float_record(tb, rec, temp_rf->name, temp_rf->value->value->f);
                                break;
                            case BOOL:
                                insert_boolean_record(tb, rec, temp_rf->name, temp_rf->value->value->b);
                                break;
                            case STRING:
                                insert_string_record(tb, rec, temp_rf->name, temp_rf->value->value->s);
                                break;
                        }
                        temp_rf = temp_rf->next;
                    }
                    insert_record_to_table(rec, tb, db, f);
                    strcpy(buff, "OK\n");
                    write(connfd, buff, sizeof(buff));
                    memset(buff, '\0', MAX);
                    break;
                }
                case UPDATE_R:{
                    table* tb = get_table_from_schema(qte->table_name,db,f);
                    column* col;
                    record_field* temp_rf = qte->insertRecordQuery->rec;
                    while(temp_rf != NULL) {
                        switch (temp_rf->value->type) {
                            case INTEGER:
                                col=create_integer_column_to_update(temp_rf->name, temp_rf->value->value->i);
                                break;
                            case FLOAT:
                                col=create_float_column_to_update(temp_rf->name, temp_rf->value->value->f);
                                break;
                            case BOOL:
                                col=create_bool_column_to_update(temp_rf->name, temp_rf->value->value->b);
                                break;
                            case STRING:
                                col=create_string_column_to_update(temp_rf->name, temp_rf->value->value->s);
                                break;
                        }
                        temp_rf = temp_rf->next;
                    }

                    update_records_in_table(col, qte->condition, tb, db, f);
                    strcpy(buff, "OK\n");
                    write(connfd, buff, sizeof(buff));
                    memset(buff, '\0', MAX);
                    break;
                }
                case REMOVE_R:{
                    table* tb = get_table_from_schema(qte->table_name,db,f);
                    delete_records_from_table(qte->condition,tb,db,f);
                    strcpy(buff, "OK\n");
                    write(connfd, buff, sizeof(buff));
                    memset(buff, '\0', MAX);
                    break;
                }
            }
            break;
        case ARRAY:;
            switch (qte->ret_type) {
                case RETURN_ROW: {

                    uint32_t off = 0;

                    table* tb = get_table_from_schema(qte->table_name,db,f);
                    char** niz = malloc(tb->num_columns);
                    for(int i = 0; i<tb->num_columns; i++){
                        niz[i] = strdup(tb->columns[i]->name);
                    }
                    do {
                        off = select_records_from_table(off, buff, MAX, tb->num_columns, niz, NULL, tb, db, f);
                        write(connfd, buff, sizeof(buff));
                        memset(buff, '\0', MAX);
                    } while (off != 0);
                    break;
                }
                case RETURN_ROW_FILTER: {
                    uint32_t off = 0;

                    table* tb = get_table_from_schema(qte->table_name,db,f);
                    char** niz = malloc(tb->num_columns);
                    for(int i = 0; i<tb->num_columns; i++){
                        niz[i] = strdup(tb->columns[i]->name);
                    }

                    do {
                        off = select_records_from_table(off, buff, MAX, tb->num_columns, niz, qte->condition, tb,
                                                        db, f);
                        write(connfd, buff, sizeof(buff));
                        memset(buff, '\0', MAX);
                    } while (off != 0);
                }
                    break;
                case RETURN_FIELDS:{

                    uint32_t off = 0;

                    table* tb = get_table_from_schema(qte->table_name,db,f);
                    char** niz = malloc(tb->num_columns);
                    for(int i = 0; i<tb->num_columns; i++){
                        niz[i] = strdup(tb->columns[i]->name);
                    }
                    do {
                        off = select_records_from_table(off, buff, MAX, tb->num_columns, niz, NULL, tb, db, f);
                        write(connfd, buff, sizeof(buff));
                        memset(buff, '\0', MAX);
                    } while (off != 0);
                    break;
                }
                    break;
                case RETURN_FIELDS_FILTER:{
                    uint32_t off = 0;

                    table* tb = get_table_from_schema(qte->table_name,db,f);
                    char** niz = malloc(tb->num_columns);
                    for(int i = 0; i<tb->num_columns; i++){
                        niz[i] = strdup(tb->columns[i]->name);
                    }

                    do {
                        off = select_records_from_table(off, buff, MAX, tb->num_columns, niz, qte->condition, tb,
                                                        db, f);
                        write(connfd, buff, sizeof(buff));
                        memset(buff, '\0', MAX);
                    } while (off != 0);
                }
                    break;
                case RETURN_ROW_JOIN:{
                    int32_t left_off = 0;
                    int32_t right_off = 0;

                    table* left_table = get_table_from_schema(qte->returnRecordsQuery->left->table_name, db, f);
                    table* right_table = get_table_from_schema(qte->returnRecordsQuery->right->table_name, db, f);

                    column* left_col_to_join = get_column_by_name(left_table, qte->returnRecordsQuery->left->joint_column_name);
                    column* right_col_to_join = get_column_by_name(right_table, qte->returnRecordsQuery->right->joint_column_name);


                    table_to_join* left = create_table_to_join(left_table, qte->returnRecordsQuery->left->num_cols, qte->returnRecordsQuery->left->return_columns, NULL, left_col_to_join);
                    table_to_join* right = create_table_to_join(right_table, qte->returnRecordsQuery->right->num_cols, qte->returnRecordsQuery->right->return_columns, NULL, right_col_to_join);

                    do {
                        select_records_from_table_inner_join(&left_off, &right_off,buff, MAX,left, right,NULL, db, f);
                        write(connfd, buff, sizeof(buff));
                        memset(buff, '\0', MAX);
                    } while (left_off != 0);
                    break;
                }
                case RETURN_ROW_JOIN_FILTER:
                {
                    int32_t left_off = 0;
                    int32_t right_off = 0;

                    table* left_table = get_table_from_schema(qte->returnRecordsQuery->left->table_name, db, f);
                    table* right_table = get_table_from_schema(qte->returnRecordsQuery->right->table_name, db, f);

                    column* left_col_to_join = get_column_by_name(left_table, qte->returnRecordsQuery->left->joint_column_name);
                    column* right_col_to_join = get_column_by_name(left_table, qte->returnRecordsQuery->right->joint_column_name);


                    table_to_join* left = create_table_to_join(left_table, qte->returnRecordsQuery->left->num_cols, qte->returnRecordsQuery->left->return_columns, NULL, left_col_to_join);
                    table_to_join* right = create_table_to_join(right_table, qte->returnRecordsQuery->right->num_cols, qte->returnRecordsQuery->right->return_columns, NULL, right_col_to_join);

                    do {
                        select_records_from_table_inner_join(&left_off, &right_off,buff, MAX,left, right,qte->condition, db, f);
                        write(connfd, buff, sizeof(buff));
                        memset(buff, '\0', MAX);
                    } while (left_off != 0);
                    break;
                }
                case RETURN_FIELDS_JOIN: {
                    int32_t left_off = 0;
                    int32_t right_off = 0;

                    table* left_table = get_table_from_schema(qte->returnRecordsQuery->left->table_name, db, f);
                    table* right_table = get_table_from_schema(qte->returnRecordsQuery->right->table_name, db, f);

                    column* left_col_to_join = get_column_by_name(left_table, qte->returnRecordsQuery->left->joint_column_name);
                    column* right_col_to_join = get_column_by_name(right_table, qte->returnRecordsQuery->right->joint_column_name);


                    table_to_join* left = create_table_to_join(left_table, qte->returnRecordsQuery->left->num_cols, qte->returnRecordsQuery->left->return_columns, NULL, left_col_to_join);
                    table_to_join* right = create_table_to_join(right_table, qte->returnRecordsQuery->right->num_cols, qte->returnRecordsQuery->right->return_columns, NULL, right_col_to_join);

                    do {
                        select_records_from_table_inner_join(&left_off, &right_off,buff, MAX,left, right,NULL, db, f);
                        write(connfd, buff, sizeof(buff));
                        memset(buff, '\0', MAX);
                    } while (left_off != 0);
                    break;
                }
                case RETURN_FIELDS_JOIN_FILTER: {
                    int32_t left_off = 0;
                    int32_t right_off = 0;

                    table* left_table = get_table_from_schema(qte->returnRecordsQuery->left->table_name, db, f);
                    table* right_table = get_table_from_schema(qte->returnRecordsQuery->right->table_name, db, f);

                    column* left_col_to_join = get_column_by_name(left_table, qte->returnRecordsQuery->left->joint_column_name);
                    column* right_col_to_join = get_column_by_name(left_table, qte->returnRecordsQuery->right->joint_column_name);


                    table_to_join* left = create_table_to_join(left_table, qte->returnRecordsQuery->left->num_cols, qte->returnRecordsQuery->left->return_columns, NULL, left_col_to_join);
                    table_to_join* right = create_table_to_join(right_table, qte->returnRecordsQuery->right->num_cols, qte->returnRecordsQuery->right->return_columns, NULL, right_col_to_join);

                    do {
                        select_records_from_table_inner_join(&left_off, &right_off,buff, MAX,left, right,qte->condition, db, f);
                        write(connfd, buff, sizeof(buff));
                        memset(buff, '\0', MAX);
                    } while (left_off != 0);
                    break;
                }
            }
    }

}

void server_communicate(int connfd, database* db, FILE* f)
{
    char buff[MAX];
    for (;;) {
        memset(buff, '\0', MAX);

        read(connfd, buff, sizeof(buff));
        printf("%s", buff);

        query_to_execute* qte = server_decode_json(buff);
        memset(buff, '\0', MAX);

        execute_query(connfd, db, f, buff, qte);

        memset(buff, '\0', MAX);
        write(connfd, buff, sizeof(buff));

    }
}