//
// Created by stele on 25/03/23.
//

#include <jansson.h>
#include "client_transport.h"



json_t* query_to_json(query* q) {
    json_t* root = json_object();
    json_t* table = json_object();
    json_t* tables = json_array();
    json_t* params = json_array();
    json_t* columns = json_array();
    json_t* filters = json_array();

    switch (q->type) {
        case CREATE_TBL:
            json_object_set_new(root, "query_type", json_integer(q->type));
            json_object_set_new(table, "name", json_string(q->ct->name));
            json_object_set_new(table, "params", params);
            json_object_set(root, "table", table);
            json_object_set_new(root, "return_value", json_integer(OK));
            column* temp = q->ct->column;
            while(temp!=NULL){
                json_t* col = json_object();
                json_object_set_new(col, "name", json_string(temp->name));
                json_object_set_new(col, "column_type", json_integer(temp->type));
                json_object_set_new(col, "column_size", json_integer(temp->size));
                json_array_append(params, col);
                temp = temp->next;
                json_decref(col);
            }
            break;
        case REMOVE_TBL:
            root = json_pack("{s:i, s:{s:s}, s:i}",
                             "query_type", q->type,
                             "table", "name",q->rt->name,
                             "return_value", OK);
            break;
        case INSERT_R:
            json_object_set_new(root, "query_type", json_integer(q->type));
            json_object_set_new(root, "insert_type", json_integer(q->ir->type));
            switch (q->ir->type) {
                case SIMPLE_INSERT:
                    json_object_set_new(table, "name", json_string(q->ir->table_name));
                    json_object_set_new(table, "params", params);
                    json_object_set(root, "table", table);
                    json_object_set_new(root, "return_value", json_integer(OK));
                    record_field* temp = q->ir->rfs->rf;
                    while(temp!=NULL){
                        json_t* field = json_object();
                        json_object_set_new(table, "name", json_string(q->ir->table_name));
                        json_object_set_new(field, "name", json_string(temp->name));
                        json_object_set_new(field, "type", json_integer(temp->value->type));
                        switch (temp->value->type) {
                            case INTEGER_AST:
                                json_object_set_new(field, "value", json_integer(temp->value->value->i));
                                break;
                            case FLOAT_AST:
                                json_object_set_new(field, "value", json_real(temp->value->value->f));
                                break;
                            case BOOLEAN_AST:
                                json_object_set_new(field, "value", json_integer(temp->value->value->b));
                                break;
                            case VARCHAR_AST:
                                json_object_set_new(field, "value", json_string(temp->value->value->s));
                                break;
                        }
                        json_array_append(params, field);
                        temp = temp->next;
                        json_decref(field);
                    }
                    break;
                case COMPLEX_INSERT:
                    //To do
                    break;
            }
            break;
        case UPDATE_R:;
            switch (q->ur->type) {
                case UPDATE_ALL:;
                    record_field* ur_rf_temp = q->ur->rf;
                    while(ur_rf_temp != NULL) {
                        json_t* col = json_object();
                        json_object_set_new(col, "type", json_integer(ur_rf_temp->value->type));
                        json_object_set_new(col, "name", json_string(ur_rf_temp->name));

                        switch (ur_rf_temp->value->type) {
                            case INTEGER_AST:
                                json_object_set_new(col, "value", json_integer(ur_rf_temp->value->value->i));
                                break;
                            case FLOAT_AST:
                                json_object_set_new(col, "value", json_real(ur_rf_temp->value->value->f));
                                break;
                            case BOOLEAN_AST:
                                json_object_set_new(col, "value", json_integer(ur_rf_temp->value->value->b));
                                break;
                            case VARCHAR_AST:
                                json_object_set_new(col, "value", json_string(ur_rf_temp->value->value->s));
                                break;
                        }
                        json_array_append_new(columns, col);
                        ur_rf_temp = ur_rf_temp->next;
                    }

                    json_object_set_new(root, "query_type", json_integer(q->type));
                    json_object_set_new(root, "update_type", json_integer(q->ur->type));
                    json_object_set_new(table, "name", json_string(q->ur->table_name));
                    json_object_set(root, "table", table);
                    json_object_set(table, "columns", columns);
                    json_object_set_new(root, "return_value", json_integer(OK));

                    break;
                case UPDATE_FILTER:;
                    record_field* uf_rf_temp = q->ur->rf;
                    while(uf_rf_temp != NULL) {
                        json_t* col = json_object();
                        json_object_set_new(col, "type", json_integer(uf_rf_temp->value->type));
                        json_object_set_new(col, "name", json_string(uf_rf_temp->name));

                        switch (uf_rf_temp->value->type) {
                            case INTEGER_AST:
                                json_object_set_new(col, "value", json_integer(uf_rf_temp->value->value->i));
                                break;
                            case FLOAT_AST:
                                json_object_set_new(col, "value", json_real(uf_rf_temp->value->value->f));
                                break;
                            case BOOLEAN_AST:
                                json_object_set_new(col, "value", json_integer(uf_rf_temp->value->value->b));
                                break;
                            case VARCHAR_AST:
                                json_object_set_new(col, "value", json_string(uf_rf_temp->value->value->s));
                                break;
                        }
                        json_array_append_new(columns, col);
                        uf_rf_temp = uf_rf_temp->next;
                    }

                    filter* uf_f_temp = q->ur->filter;
                    while(uf_f_temp != NULL) {
                        json_t* filter = json_array();
                        comparison* uf_c_temp = uf_f_temp->comparison;
                        while(uf_c_temp != NULL){
                            json_t* comparison = json_object();
                            json_t* left_operand = json_object();
                            json_t* right_operand = json_object();

                            json_object_set_new(left_operand, "type", json_integer(uf_c_temp->left_operand->type));
                            switch (uf_c_temp->left_operand->type) {
                                case INTEGER_AST:
                                    json_object_set_new(left_operand, "value", json_integer(uf_c_temp->left_operand->value->i));
                                    break;
                                case FLOAT_AST:
                                    json_object_set_new(left_operand, "value", json_real(uf_c_temp->left_operand->value->f));
                                    break;
                                case BOOLEAN_AST:
                                    json_object_set_new(left_operand, "value", json_integer(uf_c_temp->left_operand->value->b));
                                    break;
                                case VARCHAR_AST:
                                    json_object_set_new(left_operand, "value", json_string(uf_c_temp->left_operand->value->s));
                                    break;
                                case REFERENCE_AST:
                                    break;
                            }
                            json_object_set_new(comparison, "left_operand", left_operand);

                            json_object_set_new(right_operand, "type", json_integer(uf_c_temp->right_operand->type));
                            switch (uf_c_temp->right_operand->type) {
                                case INTEGER_AST:
                                    json_object_set_new(right_operand, "value", json_integer(uf_c_temp->right_operand->value->i));
                                    break;
                                case FLOAT_AST:
                                    json_object_set_new(right_operand, "value", json_real(uf_c_temp->right_operand->value->f));
                                    break;
                                case BOOLEAN_AST:
                                    json_object_set_new(right_operand, "value", json_integer(uf_c_temp->right_operand->value->b));
                                    break;
                                case VARCHAR_AST:
                                    json_object_set_new(right_operand, "value", json_string(uf_c_temp->right_operand->value->s));
                                    break;
                            }
                            json_object_set_new(comparison, "right_operand", right_operand);

                            json_object_set_new(comparison, "comparison", json_integer(uf_c_temp->relation));
                            json_object_set_new(comparison, "relation", json_integer(uf_c_temp->comparison_relation));
                            json_array_append_new(filter, comparison);
                            uf_c_temp = uf_c_temp->next;
                        }
                        json_array_append_new(filters, filter);
                        uf_f_temp = uf_f_temp->next;
                    }

                    json_object_set_new(root, "query_type", json_integer(q->type));
                    json_object_set_new(root, "update_type", json_integer(q->ur->type));
                    json_object_set_new(table, "name", json_string(q->ur->table_name));
                    json_object_set(root, "table", table);
                    json_object_set(table, "columns", columns);
                    json_object_set(table, "filters", filters);
                    json_object_set_new(root, "return_value", json_integer(OK));

                    break;
            }
            break;
        case REMOVE_R:
            switch (q->rem_r->type) {
                case REMOVE_ALL:
                    root = json_pack("{s:i, s:i, s:{s:s}, s:i}",
                                     "query_type", q->type,
                                     "remove_type", q->rem_r->type,
                                     "table", "name",q->rem_r->table_name,
                                     "return_value", OK);
                    break;
                case REMOVE_FILTER:;
                    filter* rf_f_temp = q->rem_r->filter;
                    while(rf_f_temp != NULL) {
                        json_t* filter = json_array();
                        comparison* rf_c_temp = rf_f_temp->comparison;
                        while(rf_c_temp != NULL){
                            json_t* comparison = json_object();
                            json_t* left_operand = json_object();
                            json_t* right_operand = json_object();

                            json_object_set_new(left_operand, "type", json_integer(rf_c_temp->left_operand->type));
                            switch (rf_c_temp->left_operand->type) {
                                case INTEGER_AST:
                                    json_object_set_new(left_operand, "value", json_integer(rf_c_temp->left_operand->value->i));
                                    break;
                                case FLOAT_AST:
                                    json_object_set_new(left_operand, "value", json_real(rf_c_temp->left_operand->value->f));
                                    break;
                                case BOOLEAN_AST:
                                    json_object_set_new(left_operand, "value", json_integer(rf_c_temp->left_operand->value->b));
                                    break;
                                case VARCHAR_AST:
                                    json_object_set_new(left_operand, "value", json_string(rf_c_temp->left_operand->value->s));
                                    break;
                            }
                            json_object_set_new(comparison, "left_operand", left_operand);

                            json_object_set_new(right_operand, "type", json_integer(rf_c_temp->right_operand->type));
                            switch (rf_c_temp->right_operand->type) {
                                case INTEGER_AST:
                                    json_object_set_new(right_operand, "value", json_integer(rf_c_temp->right_operand->value->i));
                                    break;
                                case FLOAT_AST:
                                    json_object_set_new(right_operand, "value", json_real(rf_c_temp->right_operand->value->f));
                                    break;
                                case BOOLEAN_AST:
                                    json_object_set_new(right_operand, "value", json_integer(rf_c_temp->right_operand->value->b));
                                    break;
                                case VARCHAR_AST:
                                    json_object_set_new(right_operand, "value", json_string(rf_c_temp->right_operand->value->s));
                                    break;
                            }
                            json_object_set_new(comparison, "right_operand", right_operand);

                            json_object_set_new(comparison, "comparison", json_integer(rf_c_temp->relation));
                            json_object_set_new(comparison, "relation", json_integer(rf_c_temp->comparison_relation));
                            json_array_append_new(filter, comparison);
                            rf_c_temp = rf_c_temp->next;
                        }
                        json_array_append_new(filters, filter);
                        rf_f_temp = rf_f_temp->next;
                    }

                    json_object_set_new(root, "query_type", json_integer(q->type));
                    json_object_set_new(root, "remove_type", json_integer(q->rem_r->type));
                    json_object_set_new(table, "name", json_string(q->rem_r->loop->table_name));
                    json_object_set(root, "table", table);
                    json_object_set(table, "filters", filters);
                    json_object_set_new(root, "return_value", json_integer(OK));

                    break;
            }
            break;
        case RETURN_R:
            switch (q->ret_r->type) {
                case RETURN_ROW:
                    json_object_set_new(root, "query_type", json_integer(q->type));
                    json_object_set_new(root, "return_type", json_integer(q->ret_r->type));
                    json_object_set_new(table, "name", json_string(q->ret_r->left_loop->table_name));
                    json_object_set(root, "table", table);
                    json_object_set_new(root, "return_value", json_integer(ARRAY));
                    break;
                case RETURN_ROW_FILTER: {
                    filter *rrf_f_temp = q->ret_r->filter;
                    while (rrf_f_temp != NULL) {
                        json_t *filter = json_array();
                        comparison *rrf_c_temp = rrf_f_temp->comparison;
                        while (rrf_c_temp != NULL) {
                            json_t *comparison = json_object();
                            json_t *left_operand = json_object();
                            json_t *right_operand = json_object();

                            json_object_set_new(comparison, "comparison_type",
                                                json_integer(q->ret_r->filter->comparison->type));

                            json_object_set_new(left_operand, "type", json_integer(rrf_c_temp->left_operand->type));
                            switch (rrf_c_temp->left_operand->type) {
                                case INTEGER_AST:
                                    json_object_set_new(left_operand, "value",
                                                        json_integer(rrf_c_temp->left_operand->value->i));
                                    break;
                                case FLOAT_AST:
                                    json_object_set_new(left_operand, "value",
                                                        json_real(rrf_c_temp->left_operand->value->f));
                                    break;
                                case BOOLEAN_AST:
                                    json_object_set_new(left_operand, "value",
                                                        json_integer(rrf_c_temp->left_operand->value->b));
                                    break;
                                case VARCHAR_AST:
                                    json_object_set_new(left_operand, "value",
                                                        json_string(rrf_c_temp->left_operand->value->s));
                                    break;
                                case REFERENCE_AST:
                                    json_object_set_new(left_operand, "value",
                                                        json_string(rrf_c_temp->left_operand->value->s));
                                    break;
                            }
                            json_object_set_new(comparison, "left_operand", left_operand);

                            json_object_set_new(right_operand, "type", json_integer(rrf_c_temp->right_operand->type));
                            switch (rrf_c_temp->right_operand->type) {
                                case INTEGER_AST:
                                    json_object_set_new(right_operand, "value",
                                                        json_integer(rrf_c_temp->right_operand->value->i));
                                    break;
                                case FLOAT_AST:
                                    json_object_set_new(right_operand, "value",
                                                        json_real(rrf_c_temp->right_operand->value->f));
                                    break;
                                case BOOLEAN_AST:
                                    json_object_set_new(right_operand, "value",
                                                        json_integer(rrf_c_temp->right_operand->value->b));
                                    break;
                                case VARCHAR_AST:
                                    json_object_set_new(right_operand, "value",
                                                        json_string(rrf_c_temp->right_operand->value->s));
                                    break;
                                case REFERENCE_AST:
                                    json_object_set_new(right_operand, "value",
                                                        json_string(rrf_c_temp->right_operand->value->s));
                                    break;
                            }
                            json_object_set_new(comparison, "right_operand", right_operand);

                            json_object_set_new(comparison, "comparison", json_integer(rrf_c_temp->relation));
                            json_object_set_new(comparison, "relation", json_integer(rrf_c_temp->comparison_relation));
                            json_array_append_new(filter, comparison);
                            rrf_c_temp = rrf_c_temp->next;
                        }
                        json_array_append_new(filters, filter);
                        rrf_f_temp = rrf_f_temp->next;
                    }

                    json_object_set_new(root, "query_type", json_integer(q->type));
                    json_object_set_new(root, "return_type", json_integer(q->ret_r->type));
                    json_object_set_new(table, "name", json_string(q->ret_r->left_loop->table_name));
                    json_object_set(root, "table", table);
                    json_object_set(table, "filters", filters);
                    json_object_set_new(root, "return_value", json_integer(ARRAY));
                    break;
                }
                case RETURN_FIELDS:;
                    field* rf_f_temp = q->ret_r->f;
                    while(rf_f_temp != NULL) {
                        json_t* col = json_object();
                        json_object_set_new(col, "name", json_string(rf_f_temp->name));
                        json_array_append_new(columns, col);

                        rf_f_temp = rf_f_temp->next;
                    }

                    json_object_set_new(root, "query_type", json_integer(q->type));
                    json_object_set_new(root, "return_type", json_integer(q->ret_r->type));
                    json_object_set_new(table, "name", json_string(q->ret_r->left_loop->table_name));
                    json_object_set(root, "table", table);
                    json_object_set(table, "columns", columns);
                    json_object_set_new(root, "return_value", json_integer(ARRAY));

                    break;
                case RETURN_FIELDS_FILTER:;
                    filter* rff_f_temp = q->ret_r->filter;
                    while(rff_f_temp != NULL) {
                        json_t* filter = json_array();
                        comparison* rff_c_temp = rff_f_temp->comparison;
                        while(rff_c_temp != NULL){
                            json_t* comparison = json_object();
                            json_t* left_operand = json_object();
                            json_t* right_operand = json_object();

                            json_object_set_new(left_operand, "type", json_integer(rff_c_temp->left_operand->type));
                            switch (rff_c_temp->left_operand->type) {
                                case INTEGER_AST:
                                    json_object_set_new(left_operand, "value", json_integer(rff_c_temp->left_operand->value->i));
                                    break;
                                case FLOAT_AST:
                                    json_object_set_new(left_operand, "value", json_real(rff_c_temp->left_operand->value->f));
                                    break;
                                case BOOLEAN_AST:
                                    json_object_set_new(left_operand, "value", json_integer(rff_c_temp->left_operand->value->b));
                                    break;
                                case VARCHAR_AST:
                                    json_object_set_new(left_operand, "value", json_string(rff_c_temp->left_operand->value->s));
                                    break;
                            }
                            json_object_set_new(comparison, "left_operand", left_operand);

                            json_object_set_new(right_operand, "type", json_integer(rff_c_temp->right_operand->type));
                            switch (rff_c_temp->right_operand->type) {
                                case INTEGER_AST:
                                    json_object_set_new(right_operand, "value", json_integer(rff_c_temp->right_operand->value->i));
                                    break;
                                case FLOAT_AST:
                                    json_object_set_new(right_operand, "value", json_real(rff_c_temp->right_operand->value->f));
                                    break;
                                case BOOLEAN_AST:
                                    json_object_set_new(right_operand, "value", json_integer(rff_c_temp->right_operand->value->b));
                                    break;
                                case VARCHAR_AST:
                                    json_object_set_new(right_operand, "value", json_string(rff_c_temp->right_operand->value->s));
                                    break;
                            }
                            json_object_set_new(comparison, "right_operand", right_operand);

                            json_object_set_new(comparison, "comparison", json_integer(rff_c_temp->relation));
                            json_object_set_new(comparison, "relation", json_integer(rff_c_temp->comparison_relation));
                            json_array_append_new(filter, comparison);
                            rff_c_temp = rff_c_temp->next;
                        }
                        json_array_append_new(filters, filter);
                        rff_f_temp = rff_f_temp->next;
                    }

                    field* rff_field_temp = q->ret_r->f;
                    while(rff_field_temp != NULL) {
                        json_t* col = json_object();
                        json_object_set_new(col, "name", json_string(rff_field_temp->name));
                        json_array_append_new(columns, col);

                        rff_field_temp = rff_field_temp->next;
                    }

                    json_object_set_new(root, "query_type", json_integer(q->type));
                    json_object_set_new(root, "return_type", json_integer(q->ret_r->type));
                    json_object_set_new(table, "name", json_string(q->ret_r->left_loop->table_name));
                    json_object_set(root, "table", table);
                    json_object_set(table, "columns", columns);
                    json_object_set(table, "filters", filters);
                    json_object_set_new(root, "return_value", json_integer(ARRAY));
                    break;
                case RETURN_ROW_JOIN:

                    break;
                case RETURN_ROW_JOIN_FILTER:
                    break;
                case RETURN_FIELDS_JOIN: {

                    json_t* left_table = json_object();
                    json_t* right_table = json_object();
                    json_t* left_columns = json_array();
                    json_t* right_columns = json_array();

                    field* rrj_f_temp = q->ret_r->f;
                    while (rrj_f_temp != NULL) {

                        json_t* field = json_object();
                        json_object_set_new(field, "name", json_string(rrj_f_temp->name));

                        if(strcmp(q->ret_r->left_loop->row_name, rrj_f_temp->row_name) == 0) {
                            json_array_append_new(left_columns, field);
                        } else if (strcmp(q->ret_r->right_loop->row_name, rrj_f_temp->row_name) == 0) {
                            json_array_append_new(right_columns, field);
                        }

                        rrj_f_temp = rrj_f_temp->next;
                    }

                    json_object_set_new(root, "query_type", json_integer(q->type));
                    json_object_set_new(root, "return_type", json_integer(q->ret_r->type));
                    json_object_set_new(root, "tables", tables);
                    json_array_append_new(tables, left_table);
                    json_array_append_new(tables, right_table);

                    json_object_set_new(left_table, "name", json_string(q->ret_r->left_loop->table_name));
                    char* left_operand = q->ret_r->join_condition->left_operand->value->s;
                    char* l_token = strtok(left_operand, ".");
                    l_token = strtok(NULL, ".");
                    json_object_set_new(left_table, "joint_column", json_string(l_token));
                    json_object_set_new(left_table, "return_columns", left_columns);

                    json_object_set_new(right_table, "name", json_string(q->ret_r->right_loop->table_name));
                    char* right_operand = q->ret_r->join_condition->right_operand->value->s;
                    char* r_token = strtok(right_operand, ".");
                    r_token = strtok(NULL, ".");
                    json_object_set_new(right_table, "joint_column", json_string(r_token));
                    json_object_set_new(right_table, "return_columns", right_columns);

                    json_object_set_new(root, "return_value", json_integer(ARRAY));

                    break;
                }
                case RETURN_FIELDS_JOIN_FILTER: {

                    filter* rfjf_f_temp = q->ret_r->filter;
                    while(rfjf_f_temp != NULL) {
                        json_t* filter = json_array();
                        comparison* rrf_c_temp = rfjf_f_temp->comparison;
                        while(rrf_c_temp != NULL){
                            json_t* comparison = json_object();
                            json_t* left_operand = json_object();
                            json_t* right_operand = json_object();

                            json_object_set_new(comparison, "comparison_type", json_integer(q->ret_r->filter->comparison->type));

                            json_object_set_new(left_operand, "type", json_integer(rrf_c_temp->left_operand->type));
                            switch (rrf_c_temp->left_operand->type) {
                                case INTEGER_AST:
                                    json_object_set_new(left_operand, "value", json_integer(rrf_c_temp->left_operand->value->i));
                                    break;
                                case FLOAT_AST:
                                    json_object_set_new(left_operand, "value", json_real(rrf_c_temp->left_operand->value->f));
                                    break;
                                case BOOLEAN_AST:
                                    json_object_set_new(left_operand, "value", json_integer(rrf_c_temp->left_operand->value->b));
                                    break;
                                case VARCHAR_AST:
                                    json_object_set_new(left_operand, "value", json_string(rrf_c_temp->left_operand->value->s));
                                    break;
                                case REFERENCE_AST:
                                    json_object_set_new(left_operand, "value", json_string(rrf_c_temp->left_operand->value->s));
                                    break;
                            }
                            json_object_set_new(comparison, "left_operand", left_operand);

                            json_object_set_new(right_operand, "type", json_integer(rrf_c_temp->right_operand->type));
                            switch (rrf_c_temp->right_operand->type) {
                                case INTEGER_AST:
                                    json_object_set_new(right_operand, "value", json_integer(rrf_c_temp->right_operand->value->i));
                                    break;
                                case FLOAT_AST:
                                    json_object_set_new(right_operand, "value", json_real(rrf_c_temp->right_operand->value->f));
                                    break;
                                case BOOLEAN_AST:
                                    json_object_set_new(right_operand, "value", json_integer(rrf_c_temp->right_operand->value->b));
                                    break;
                                case VARCHAR_AST:
                                    json_object_set_new(right_operand, "value", json_string(rrf_c_temp->right_operand->value->s));
                                    break;
                                case REFERENCE_AST:
                                    json_object_set_new(right_operand, "value", json_string(rrf_c_temp->right_operand->value->s));
                                    break;
                            }
                            json_object_set_new(comparison, "right_operand", right_operand);

                            json_object_set_new(comparison, "comparison", json_integer(rrf_c_temp->relation));
                            json_object_set_new(comparison, "relation", json_integer(rrf_c_temp->comparison_relation));
                            json_array_append_new(filter, comparison);
                            rrf_c_temp = rrf_c_temp->next;
                        }
                        json_array_append_new(filters, filter);
                        rfjf_f_temp = rfjf_f_temp->next;
                    }

                    json_t* left_table = json_object();
                    json_t* right_table = json_object();
                    json_t* left_columns = json_array();
                    json_t* right_columns = json_array();

                    field* rrj_f_temp = q->ret_r->f;
                    while (rrj_f_temp != NULL) {

                        json_t* field = json_object();
                        json_object_set_new(field, "name", json_string(rrj_f_temp->name));

                        if(strcmp(q->ret_r->left_loop->row_name, rrj_f_temp->row_name) == 0) {
                            json_array_append_new(left_columns, field);
                        } else if (strcmp(q->ret_r->right_loop->row_name, rrj_f_temp->row_name) == 0) {
                            json_array_append_new(right_columns, field);
                        }

                        rrj_f_temp = rrj_f_temp->next;
                    }

                    json_object_set_new(root, "query_type", json_integer(q->type));
                    json_object_set_new(root, "return_type", json_integer(q->ret_r->type));
                    json_object_set_new(root, "filters", filters);
                    json_object_set_new(root, "tables", tables);
                    json_array_append_new(tables, left_table);
                    json_array_append_new(tables, right_table);

                    json_object_set_new(left_table, "name", json_string(q->ret_r->left_loop->table_name));
                    char* left_operand = q->ret_r->join_condition->left_operand->value->s;
                    char* l_token = strtok(left_operand, ".");
                    l_token = strtok(NULL, ".");
                    json_object_set_new(left_table, "joint_column", json_string(l_token));
                    json_object_set_new(left_table, "return_columns", left_columns);

                    json_object_set_new(right_table, "name", json_string(q->ret_r->right_loop->table_name));
                    char* right_operand = q->ret_r->join_condition->right_operand->value->s;
                    char* r_token = strtok(right_operand, ".");
                    r_token = strtok(NULL, ".");
                    json_object_set_new(right_table, "joint_column", json_string(r_token));
                    json_object_set_new(right_table, "return_columns", right_columns);

                    json_object_set_new(root, "return_value", json_integer(ARRAY));

                    break;
                }
            }
            break;
    }

    return root;
}

void client_communicate(int sockfd)
{
    char buff[MAX];
    for (;;) {
        query *q = yyparse();
        json_t* t = query_to_json(q);
        char *s = json_dumps(t, JSON_INDENT(2));

        memset(buff, '\0', MAX);
        strcpy(buff,s);

        write(sockfd, buff, sizeof(buff));
        memset(buff, '\0', MAX);

        do {
            read(sockfd, buff, sizeof(buff));
            if(buff[0] != '\0') {
                printf("%s", buff);
            }

        } while(buff[0] != '\0');
        memset(buff, '\0', MAX);

    }
}