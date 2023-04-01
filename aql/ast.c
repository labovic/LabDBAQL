#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ast.h"

char* query_type_strings[6] = {"Create Table", "Remove Table", "Insert Records", "Update Records",
                               "Remove Records", "Return Records"};
char* relation_strings[6] = {"==", "!=", "<", ">","<=",">="};
char* comparison_relation_strings[2] = {"OR", "AND"};

query* create_create_table_query(create_table* ct) {
    query* q = malloc(sizeof(query));
    q->type = CREATE_TBL;
    q->ct = ct;
    return q;
}

query* create_remove_table_query(remove_table* rt) {
    query* q = malloc(sizeof(query));
    q->type = REMOVE_TBL;
    q->rt = rt;
    return q;
}

query* create_insert_records_query(insert_records* ir){
    query* q = malloc(sizeof(query));
    q->type = INSERT_R;
    q->ir = ir;
    return q;
}

query* create_update_records_query(update_records* ur){
    query* q = malloc(sizeof(query));
    q->type = UPDATE_R;
    q->ur = ur;
    return q;
}

query* create_remove_records_query(remove_records* rem_r){
    query* q = malloc(sizeof(query));
    q->type = REMOVE_R;
    q->rem_r = rem_r;
    return q;
}

query* create_return_records_query(return_records* ret_r){
    query* q = malloc(sizeof(query));
    q->type = RETURN_R;
    q->ret_r = ret_r;
    return q;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

create_table* create_create_table(char* name, column* col) {
  create_table* ct = malloc(sizeof(create_table));
  strcpy(ct->name, name);
  ct->column = col;
  return ct;
}

remove_table* create_remove_table(char* name) {
    remove_table* rt = malloc(sizeof(remove_table));
    strcpy(rt->name, name);
    return rt;
}

insert_records* create_loop_insert_records(char* row_name, char* tb_name, record_fields* rfs) {
    insert_records* ir = malloc(sizeof(insert_records));
    ir->type = COMPLEX_INSERT;
    strcpy(ir->row_name, row_name);
    strcpy(ir->table_name, tb_name);
    ir->rfs = rfs;
    return ir;
}

insert_records* create_insert_records(char* name, record_field* rf) {
    insert_records* ir = malloc(sizeof(insert_records));
    ir->type = SIMPLE_INSERT;
    strcpy(ir->table_name, name);
    ir->rfs = create_record_fields(rf);
    return ir;
}

update_records* create_update_records(char* name, record_field* rf) {
    update_records* ur = malloc(sizeof(update_records));
    ur->type = UPDATE_ALL;
    strcpy(ur->table_name, name);
    ur->rf = rf;
    return ur;
}

update_records* create_update_records_filter(loop* loop, filter* f, char* upd_row, record_field* rf, char* upd_tb) {
    update_records* ur = malloc(sizeof(update_records));
    ur->type = UPDATE_FILTER;
    ur->filter = f;
    ur->rf = rf;

    strcpy(ur->row_name, upd_row);
    strcpy(ur->table_name, upd_tb);
    return ur;
}

remove_records* create_remove_records(char* name) {
    remove_records* rem_r = malloc(sizeof(remove_records));
    rem_r->type = REMOVE_ALL;
    strcpy(rem_r->table_name, name);
    return rem_r;
}

remove_records* create_remove_records_filter(loop* loop, filter* f, char* rem_row, char* rem_tb) {
    remove_records* rem_r = malloc(sizeof(remove_records));
    rem_r->type = REMOVE_FILTER;
    rem_r->loop = loop;
    rem_r->filter = f;

    strcpy(rem_r->row_name, rem_row);
    strcpy(rem_r->table_name, rem_tb);

    return rem_r;
}

return_records* create_return_records(loop* loop, char* return_name) {
    return_records* ret_r = malloc(sizeof(return_records));
    ret_r->type = RETURN_ROW;
    ret_r->left_loop = loop;
    strcpy(ret_r->left_return_name, return_name);

    return ret_r;
}

return_records* create_return_records_filter(loop* loop, filter* f, char* return_name) {
    return_records* ret_r = malloc(sizeof(return_records));
    ret_r->type = RETURN_ROW_FILTER;
    ret_r->left_loop = loop;
    ret_r->filter = f;

    strcpy(ret_r->left_return_name, return_name);

    return ret_r;
}

return_records* create_return_records_fields(loop* loop, field* f) {
    return_records* ret_r = malloc(sizeof(return_records));
    ret_r->type = RETURN_FIELDS;
    ret_r->left_loop = loop;
    ret_r->f = f;

    return ret_r;
}

return_records* create_return_records_fields_filter(loop* loop, filter* filter, field* f) {
    return_records* ret_r = malloc(sizeof(return_records));
    ret_r->type = RETURN_FIELDS_FILTER;
    ret_r->left_loop = loop;
    ret_r->filter = filter;
    ret_r->f = f;

    return ret_r;
}

return_records* create_return_joined_records(loop* left, loop* right,
                                             comparison* join_condition,
                                             char* left_row, char* right_row) {
    return_records* ret_r = malloc(sizeof(return_records));
    ret_r->type = RETURN_ROW_JOIN;
    ret_r->left_loop = left;
    ret_r->right_loop = right;
    ret_r->join_condition = join_condition;
    strcpy(ret_r->left_return_name, left_row);
    strcpy(ret_r->right_return_name, right_row);

    return ret_r;
}
return_records* create_return_joined_records_filter(loop* left, loop* right, comparison* join_condition,
                                                    filter* f, char* left_row, char* right_row) {
    return_records* ret_r = malloc(sizeof(return_records));
    ret_r->type = RETURN_ROW_JOIN_FILTER;
    ret_r->left_loop = left;
    ret_r->right_loop = right;
    ret_r->join_condition = join_condition;
    ret_r->filter = f;
    strcpy(ret_r->left_return_name, left_row);
    strcpy(ret_r->right_return_name, right_row);

    return ret_r;
}
return_records* create_return_joined_records_fields(loop* left, loop* right,
                                                    comparison* join_condition, field* f) {
    return_records* ret_r = malloc(sizeof(return_records));
    ret_r->type = RETURN_FIELDS_JOIN;
    ret_r->left_loop = left;
    ret_r->right_loop = right;
    ret_r->join_condition = join_condition;
    ret_r->f = f;

    return ret_r;

}
return_records* create_return_joined_records_fields_filter(loop* left, loop* right, comparison* join_condition,
                                                           filter* filter, field* f) {
    return_records* ret_r = malloc(sizeof(return_records));
    ret_r->type = RETURN_FIELDS_JOIN_FILTER;
    ret_r->left_loop = left;
    ret_r->right_loop = right;
    ret_r->join_condition = join_condition;
    ret_r->filter = filter;
    ret_r->f = f;

    return ret_r;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

field* create_field(char* first, char* second) {
    field* f = malloc(sizeof(field));
    f->row_name = first;
    f->name = second;
    return f;
}

loop* create_loop(char* row_name, char* table_name) {
    loop* l = malloc(sizeof(loop));
    strcpy(l->row_name, row_name);
    strcpy(l->table_name, table_name);
    return l;
}

record_fields* create_record_fields(record_field* rf) {
    record_fields* rfs = malloc(sizeof(record_fields));
    rfs->rf = rf;
    return rfs;
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
    l->type = INTEGER_AST;
    l->value = malloc(sizeof(int32_t));
    l->value->i = i;
    return l;
}

literal* create_float_literal(float f) {
    literal* l = malloc(sizeof(literal));
    l->type = FLOAT_AST;
    l->value = malloc(sizeof(float));
    l->value->f = f;
    return l;
}

literal* create_boolean_literal(bool b) {
    literal* l = malloc(sizeof(literal));
    l->type = BOOLEAN_AST;
    l->value = malloc(sizeof(bool));
    l->value->b = b;
    return l;
}

literal* create_string_literal(char* s) {
    literal* l = malloc(sizeof(literal));
    l->type = VARCHAR_AST;
    l->value = malloc(sizeof(char*));
    l->value->s = s;
    return l;
}

literal* create_reference_literal(char* first, char* second) {
    literal* l = malloc(sizeof(literal));
    l->type = REFERENCE_AST;
    if (first == NULL) {
        l->value = malloc(sizeof(char*));
        l->value->s = second;
    } else {
        l->value = malloc(strlen(first) + strlen(second) + 2);
        l->value->s = strcat(first, ".");
        l->value->s = strcat(l->value->s, second);
    }

    return l;
}

void fill_integer_column(column* col, char* name) {
    strcpy(col->name, name);
    col->type = INTEGER_AST;
    col->size = sizeof(int32_t);
}

void fill_float_column(column* col, char* name) {
    strcpy(col->name, name);
    col->type = FLOAT_AST;
    col->size = sizeof(float);
}

void fill_boolean_column(column* col, char* name) {
    strcpy(col->name, name);
    col->type = BOOLEAN_AST;
    col->size = sizeof(bool);
}

void fill_string_column(column* col, char* name, uint8_t size) {
    strcpy(col->name, name);
    col->type = VARCHAR_AST;
    col->size = size;
}

column* create_column(char* name, int type, uint8_t size) {
  column* col = malloc(sizeof(column));
  
  switch(type) {
      case INTEGER_AST:
          fill_integer_column(col, name);
          break;
      case FLOAT_AST:
          fill_float_column(col, name);
          break;
      case BOOLEAN_AST:
          fill_boolean_column(col, name);
          break;
      case VARCHAR_AST:
          fill_string_column(col, name, size);
          break;
      default:
          break;
  }

  return col;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

filter* create_filter(comparison* c) {
    filter* f = malloc(sizeof(filter));
    f->comparison = c;

    return f;
}

comparison* create_comparison(literal* left, literal* right, int cmp) {
    comparison* c = malloc(sizeof(comparison));
    if((left->type == INTEGER_AST) || (left->type == BOOLEAN_AST) || (left->type == FLOAT_AST) || (left->type == VARCHAR_AST)) {
        if ((right->type == INTEGER_AST) || (right->type == BOOLEAN_AST) || (right->type == FLOAT_AST) || (right->type == VARCHAR_AST)) {
            c->type = VALUE_VALUE;
        }
        if (right->type == REFERENCE_AST) {
            c->type = VALUE_COLUMN;
        }
    } else if (left->type == REFERENCE_AST) {
        if ((right->type == INTEGER_AST) || (right->type == BOOLEAN_AST) || (right->type == FLOAT_AST) || (right->type == VARCHAR_AST)) {
            c->type = COLUMN_VALUE;
        }
        if (right->type == REFERENCE_AST) {
            c->type = COLUMN_COLUMN;
        }
    }
    c->left_operand = left;
    c->right_operand = right;
    c->relation = (enum relation) cmp;
    c->comparison_relation = NONE;
    return c;
}

comparison* create_complex_comparison(literal* left, literal* right, int cmp, int op) {
    comparison* c = malloc(sizeof(comparison));
    if((left->type == INTEGER_AST) || (left->type == BOOLEAN_AST) || (left->type == FLOAT_AST) || (left->type == VARCHAR_AST)) {
        if ((right->type == INTEGER_AST) || (right->type == BOOLEAN_AST) || (right->type == FLOAT_AST) || (right->type == VARCHAR_AST)) {
            c->type = VALUE_VALUE;
        }
        if (right->type == REFERENCE_AST) {
            c->type = VALUE_COLUMN;
        }
    } else if (left->type == REFERENCE_AST) {
        if ((right->type == INTEGER_AST) || (right->type == BOOLEAN_AST) || (right->type == FLOAT_AST) || (right->type == VARCHAR_AST)) {
            c->type = COLUMN_VALUE;
        }
        if (right->type == REFERENCE_AST) {
            c->type = COLUMN_COLUMN;
        }
    }
    c->left_operand = left;
    c->right_operand = right;
    c->relation = (enum relation) cmp;
    c->comparison_relation = (enum comparison_relation) op;

    return c;
}

comparison* create_join_condition(char* left_row, char* left_field, char* right_row, char* right_field){
    comparison* c = malloc(sizeof(comparison));
    c->left_operand = create_reference_literal(left_row, left_field);
    c->right_operand = create_reference_literal(right_row, right_field);
    c->relation = (enum relation) 0;

    return c;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void print_filter(filter* f) {

    filter* temp = f;
    while(temp != NULL){
        printf("|- Filter:\n");
        printf("           `");
        print_comparison(temp->comparison);
        temp = temp->next;
        printf("         ");
    }
}

void print_comparison(comparison* c) {
    comparison* temp = c;
    while(temp != NULL){
        printf("|- 'Left Operand': ");
        print_literal(temp->left_operand);
        printf(", 'Right Operand': ");
        print_literal(temp->right_operand);
        printf(" 'Relation': ");
        printf("'%s'\n", relation_strings[temp->relation]);

        if(temp->next != NULL) {
            printf("            |- %s\n", comparison_relation_strings[c->comparison_relation]);
            printf("            ");
        }
        temp = temp->next;
    }
}

void print_literal(literal* l) {
    switch (l->type) {
        case INTEGER_AST:
            printf("%d", l->value->i);
            break;
        case FLOAT_AST:
            printf("%f", l->value->f);
            break;
        case BOOLEAN_AST:
            printf("%d", l->value->b);
            break;
        case VARCHAR_AST:
            printf("'%s'", l->value->s);
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void print_create_table(create_table* ct) {
    printf("|- Table: 'name': '%s'\n", ct->name);
    column* temp = ct->column;
    printf("     `");
    while(temp != NULL){
        print_column(temp);
        temp = temp->next;
        printf("      ");
    }

}

void print_remove_table(remove_table* rt) {
    printf("|- Table: 'name': '%s'\n", rt->name);
}

void print_remove_records(remove_records* rem_r) {
    printf("|- Table: 'name': '%s'\n", rem_r->table_name);
}

void print_remove_records_filter(remove_records* rem_r) {
    printf("|- Table: 'name': '%s'\n", rem_r->loop->table_name);
    printf("     `|- Read Row: 'name' : '%s'\n", rem_r->loop->row_name);
    printf("        `");
    print_filter(rem_r->filter);
}

void print_return_records(return_records* ret_r) {
    printf("|- Table: 'name': '%s'\n", ret_r->left_loop->table_name);
    printf("     `|- Read Row: 'name' : '%s'\n", ret_r->left_loop->row_name);
    printf("      |- Return Row: 'name' : '%s'\n", ret_r->left_return_name);
}

void print_return_records_filter(return_records* ret_r) {
    printf("|- Table: 'name': '%s'\n", ret_r->left_loop->table_name);
    printf("     `|- Read Row: 'name' : '%s'\n", ret_r->left_loop->row_name);
    printf("        `");
    print_filter(ret_r->filter);
}

void print_return_records_fields(return_records* ret_r) {
    printf("|- Table: 'name' : '%s'\n", ret_r->left_loop->table_name);
    printf("     `|- Row: 'name' : '%s'\n", ret_r->left_loop->row_name);
    field* temp = ret_r->f;
    printf("        `");
    while(temp != NULL){
        print_field_names(temp);
        temp = temp->next;
        printf("         ");
    }
};

void print_return_records_fields_filter(return_records* ret_r) {
    printf("|- Table: 'name' : '%s'\n", ret_r->left_loop->table_name);
    printf("     `|- Row: 'name' : '%s'\n", ret_r->left_loop->row_name);

    field* temp = ret_r->f;
    printf("        `");
    while(temp != NULL){
        print_field_names(temp);
        temp = temp->next;
        printf("         ");
    }
    print_filter(ret_r->filter);
}

void print_return_joined_records(return_records* ret_r) {
    printf("|- Table: 'name': '%s'\n", ret_r->left_loop->table_name);
    printf("     `|- Read Row: 'name' : '%s'\n", ret_r->left_loop->row_name);
    printf("      |- Table: 'name': '%s'\n", ret_r->right_loop->table_name);
    printf("        `|- Read Row: 'name' : '%s'\n", ret_r->right_loop->row_name);
    printf("         ");
    print_comparison(ret_r->join_condition);
    printf("            |- Return Row: 'name': '%s', Return Row: 'name': '%s'", ret_r->left_return_name, ret_r->right_return_name);
}

void print_return_joined_records_filter(return_records* ret_r) {
    printf("|- Table: 'name': '%s'\n", ret_r->left_loop->table_name);
    printf("     `|- Read Row: 'name' : '%s'\n", ret_r->left_loop->row_name);
    printf("      |- Table: 'name': '%s'\n", ret_r->right_loop->table_name);
    printf("        `|- Read Row: 'name' : '%s'\n", ret_r->right_loop->row_name);
    printf("         ");
    print_comparison(ret_r->join_condition);
    printf("         ");
    print_filter(ret_r->filter);
    printf("            |- Return Row: 'name': '%s', Return Row: 'name': '%s'", ret_r->left_return_name, ret_r->right_return_name);
}

void print_return_joined_records_fields(return_records* ret_r) {
    printf("|- Table: 'name': '%s'\n", ret_r->left_loop->table_name);
    printf("     `|- Read Row: 'name' : '%s'\n", ret_r->left_loop->row_name);
    printf("      |- Table: 'name': '%s'\n", ret_r->right_loop->table_name);
    printf("        `|- Read Row: 'name' : '%s'\n", ret_r->right_loop->row_name);
    printf("         ");
    print_comparison(ret_r->join_condition);
    printf("            ");
    field* temp = ret_r->f;
    while(temp != NULL){
        print_field_names(temp);
        temp = temp->next;
        printf("         ");
    }
}

void print_return_joined_records_fields_filter(return_records* ret_r) {
    printf("|- Table: 'name': '%s'\n", ret_r->left_loop->table_name);
    printf("     `|- Read Row: 'name' : '%s'\n", ret_r->left_loop->row_name);
    printf("      |- Table: 'name': '%s'\n", ret_r->right_loop->table_name);
    printf("        `|- Read Row: 'name' : '%s'\n", ret_r->right_loop->row_name);
    printf("         ");
    print_comparison(ret_r->join_condition);
    printf("            ");
    field* temp = ret_r->f;
    while(temp != NULL){
        print_field_names(temp);
        temp = temp->next;
        printf("         ");
    }
    print_filter(ret_r->filter);
}

void print_update_records(update_records* ur) {
    printf("|- Table: 'name' : '%s'\n", ur->table_name);
    record_field* temp = ur->rf;
    printf("     `");
    while(temp != NULL){
        print_record_field(temp);
        temp = temp->next;
        printf("      ");
    }
};

void print_update_records_filter(update_records* ur) {
    printf("|- Table: 'name' : '%s'\n", ur->table_name);
    printf("     `|- Row: 'name' : '%s'\n", ur->row_name);

    record_field* temp = ur->rf;
    printf("        `");
    while(temp != NULL){
        print_record_field(temp);
        temp = temp->next;
        printf("         ");
    }
    print_filter(ur->filter);
}

void print_insert_records(insert_records* ir) {
    printf("|- Table: 'name' : '%s'\n", ir->table_name);
    record_field* temp = ir->rfs->rf;
    printf("     `");
    while(temp != NULL){
        print_record_field(temp);
        temp = temp->next;
        printf("      ");
    }
};

void print_loop_insert_records(insert_records* ir) {
    printf("|- Table: 'name' : '%s'\n", ir->table_name);
    printf("     `");
    record_fields* temp_rfs = ir->rfs;
    while(temp_rfs != NULL) {
        printf("|- Row: 'name' : '%s'\n", ir->row_name);
        record_field *temp_rf = temp_rfs->rf;
        printf("        `");
        while (temp_rf != NULL) {
            print_record_field(temp_rf);
            temp_rf = temp_rf->next;
            if (temp_rf != NULL) printf("         ");
        }
        temp_rfs = temp_rfs->next;
        printf("      ");
    }
}

void print_field_names(field* f) {
    printf("|- Field: 'name' : '%s'\n", f->name);
}

void print_record_field(record_field* rf) {
    printf("|- Record field: 'name' : '%s', 'value' : ", rf->name);
    switch (rf->value->type) {
        case INTEGER_AST:
            printf("%d\n", rf->value->value->i);
            break;
        case FLOAT_AST:
            printf("%f\n", rf->value->value->f);
            break;
        case BOOLEAN_AST:
            printf("%d\n", rf->value->value->b);
            break;
        case VARCHAR_AST:
            printf("%s\n", rf->value->value->s);
            break;
    }
}

void print_column(column* col) {

    printf("|- Column: 'name': '%s', 'type': %d, 'size': %d\n", col->name, col->type, col->size);
}

void print_query(query* q) {

    printf("|- Query: 'type': '%s'\n", query_type_strings[q->type]);
    printf("  `");

    switch (q->type) {
        case CREATE_TBL:
            print_create_table(q->ct);
            break;
        case REMOVE_TBL:
            print_remove_table(q->rt);
            break;
        case INSERT_R:
            switch (q->ir->type) {
                case SIMPLE_INSERT:
                    print_insert_records(q->ir);
                    break;
                case COMPLEX_INSERT:
                    print_loop_insert_records(q->ir);
                    break;
            }
            break;
        case UPDATE_R:
            switch (q->ur->type) {
                case UPDATE_ALL:
                    print_update_records(q->ur);
                    break;
                case UPDATE_FILTER:
                    print_update_records_filter(q->ur);
                    break;
            }
            break;
        case REMOVE_R:
            switch (q->rem_r->type) {
                case REMOVE_ALL:
                    print_remove_records(q->rem_r);
                    break;
                case REMOVE_FILTER:
                    print_remove_records_filter(q->rem_r);
                    break;
            }
            break;
        case RETURN_R:
            switch (q->ret_r->type) {
                case RETURN_ROW:
                    print_return_records(q->ret_r);
                    break;
                case RETURN_FIELDS:
                    print_return_records_fields(q->ret_r);
                    break;
                case RETURN_ROW_FILTER:
                    print_return_records_filter(q->ret_r);
                    break;
                case RETURN_FIELDS_FILTER:
                    print_return_records_fields_filter(q->ret_r);
                    break;
                case RETURN_ROW_JOIN:
                    print_return_joined_records(q->ret_r);
                    break;
                case RETURN_ROW_JOIN_FILTER:
                    print_return_joined_records_filter(q->ret_r);
                    break;
                case RETURN_FIELDS_JOIN:
                    print_return_joined_records_fields(q->ret_r);
                    break;
                case RETURN_FIELDS_JOIN_FILTER:
                    print_return_joined_records_fields_filter(q->ret_r);
                    break;
            }
            break;
    }


}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_create_table(create_table* ct) {
    destroy_column(&ct->column);
    free(ct);
}

void destroy_remove_table(remove_table* rt) {
    free(rt);
}

void destroy_column(column** head_ref) {
    column* current = *head_ref;
    column * next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head_ref = NULL;
}