%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <stdbool.h>

  #include "ast.h"
  extern int yylex();
  void yyerror(const char*);

  %}

%token CREATE REMOVE TABLE
%token INSERT IN UPDATE WITH RETURN FOR
%token FILTER

%token INTEGER FLOAT BOOLEAN VARCHAR
%token OP
%token CMP 
%token INTVAL FLOATVAL BOOLVAL STRING
%token COLON SEMICOLON COMMA OB CB OCB CCB OSB CSB DOT EQUAL QUOTE

%left OP
%left CMP

%type <type> INTEGER FLOAT BOOLEAN VARCHAR
%type <op> OP
%type <cmp> CMP

%type <intval> INTVAL
%type <floatval> FLOATVAL
%type <boolval> BOOLVAL
%type <strval> STRING

%type <query> query

%type <column> column
%type <column> columns

%type <record_fields> records_fields
%type <record_field> record_fields
%type <record_field> record_field
%type <literal> value compare_operand column_name
%type <field> fields
%type <loop> loop

%type <filter> filters
%type <comparison> filter join_condition

%type <create_table> create_table
%type <remove_table> remove_table
%type <insert_records> insert_records
%type <update_records> update_records
%type <remove_records> remove_records
%type <return_records> return_records

%union {
  int intval;
  float floatval;
  bool boolval;
  char* strval;

  int type;
  int op;
  int cmp;

  query* query;
  create_table* create_table;
  remove_table* remove_table;
  insert_records* insert_records;
  update_records* update_records;
  remove_records* remove_records;
  return_records* return_records;

  record_fields* record_fields;
  record_field* record_field;
  literal* literal;
  loop* loop;
  column* column;
  field* field;

  filter* filter;
  comparison* comparison;
}

%%

input:
| input query SEMICOLON {return $2;}

query: create_table {$$ = create_create_table_query($1);}
| remove_table {$$ = create_remove_table_query($1); }
| insert_records {$$ = create_insert_records_query($1); }
| update_records {$$ = create_update_records_query($1); }
| remove_records {$$ = create_remove_records_query($1); }
| return_records {$$ = create_return_records_query($1); }
;

/* Table Creation */
create_table: CREATE TABLE STRING OCB columns CCB {$$ = create_create_table($3,$5);}
;

columns: column
| column COMMA columns {$$=$1; $1->next = $3;}
;

column: STRING COLON INTEGER {$$ = create_column($1, $3, 0);}
| STRING COLON FLOAT {$$ = create_column($1, $3, 0);}
| STRING COLON BOOLEAN {$$ = create_column($1, $3, 0);}
| STRING COLON VARCHAR OB INTVAL CB {$$ = create_column($1, $3, $5);}
;

/* Table Removal */
remove_table: REMOVE TABLE STRING {$$ = create_remove_table($3);}

/* Records Insertion */
insert_records: INSERT OCB record_fields CCB IN STRING {$$ = create_insert_records($6, $3);}
| FOR STRING IN OSB records_fields CSB INSERT IN STRING {$$ = create_loop_insert_records($2, $9, $5);}
;

records_fields: OCB record_fields CCB {$$ = create_record_fields($2); }
| OCB record_fields CCB COMMA records_fields { $$ = create_record_fields($2); $$->next = $5; }
;

record_fields: record_field
| record_field COMMA record_fields {$$ = $1; $$->next = $3;}
;

record_field: STRING COLON value {$$ = create_record_field($1, $3);}
;

/* Records Update */
update_records: UPDATE WITH OCB record_fields CCB IN STRING {$$ = create_update_records($7, $4);}
| loop filters UPDATE STRING WITH OCB record_fields CCB IN STRING { $$ = create_update_records_filter($1, $2, $4, $7, $10); }
;

/* Records Removal */
remove_records: REMOVE IN STRING {$$ = create_remove_records($3);}
| loop filters REMOVE STRING IN STRING {$$ = create_remove_records_filter($1, $2, $4, $6);}
;

/* Records Return */
return_records: loop RETURN STRING {$$ = create_return_records($1, $3);}
| loop filters RETURN STRING {$$ = create_return_records_filter($1, $2, $4);}
| loop RETURN OCB fields CCB {$$ = create_return_records_fields($1, $4);}
| loop filters RETURN OCB fields CCB {$$ = create_return_records_fields_filter($1, $2, $5);}
| loop loop join_condition RETURN STRING COMMA STRING {$$ = create_return_joined_records($1, $2, $3, $5, $7);}
| loop loop join_condition filters RETURN STRING COMMA STRING {$$ = create_return_joined_records_filter($1, $2, $3, $4, $6, $8);}
| loop loop join_condition RETURN OCB fields CCB {$$ = create_return_joined_records_fields($1, $2, $3, $6);}
| loop loop join_condition filters RETURN OCB fields CCB {$$ = create_return_joined_records_fields_filter($1, $2, $3, $4, $7);}
;

/* FOR loop */
loop: FOR STRING IN STRING {$$ = create_loop($2, $4);}
;

/* Filters */
filters: FILTER filter {$$ = create_filter($2);}
| FILTER filter filters {$$ = create_filter($2); $$->next = $3;}
;

filter: compare_operand CMP compare_operand { $$ = create_comparison($1, $3, $2); }
| compare_operand CMP compare_operand OP filter { $$ = create_complex_comparison($1, $3, $2, $4); $$->next = $5; }
;

join_condition: FILTER STRING DOT STRING EQUAL STRING DOT STRING { $$ = create_join_condition($2, $4, $6, $8); }
;

compare_operand: value
| column_name
;

column_name: STRING {$$ = create_reference_literal(NULL, $1);}
| STRING DOT STRING { $$ = create_reference_literal($1, $3); }
;

value: INTVAL {$$ = create_integer_literal($1);}
| FLOATVAL {$$ = create_float_literal($1);}
| BOOLVAL {$$ = create_boolean_literal($1);}
| QUOTE STRING QUOTE {$$ = create_string_literal($2);}
;

fields: STRING {$$ = create_field(NULL, $1);}
| STRING COMMA fields {$$ = create_field(NULL, $1); $$->next = $3;}
| STRING DOT STRING {$$ = create_field($1, $3);}
| STRING DOT STRING COMMA fields {$$ = create_field($1, $3); $$->next = $5;}
;

%%

void yyerror(const char* str) {
  fprintf(stderr, "error: %s\n", str);
}
