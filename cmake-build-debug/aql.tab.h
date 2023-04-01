/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_AQL_TAB_H_INCLUDED
# define YY_YY_AQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CREATE = 258,                  /* CREATE  */
    REMOVE = 259,                  /* REMOVE  */
    TABLE = 260,                   /* TABLE  */
    INSERT = 261,                  /* INSERT  */
    IN = 262,                      /* IN  */
    UPDATE = 263,                  /* UPDATE  */
    WITH = 264,                    /* WITH  */
    RETURN = 265,                  /* RETURN  */
    FOR = 266,                     /* FOR  */
    FILTER = 267,                  /* FILTER  */
    INTEGER = 268,                 /* INTEGER  */
    FLOAT = 269,                   /* FLOAT  */
    BOOLEAN = 270,                 /* BOOLEAN  */
    VARCHAR = 271,                 /* VARCHAR  */
    OP = 272,                      /* OP  */
    CMP = 273,                     /* CMP  */
    INTVAL = 274,                  /* INTVAL  */
    FLOATVAL = 275,                /* FLOATVAL  */
    BOOLVAL = 276,                 /* BOOLVAL  */
    STRING = 277,                  /* STRING  */
    COLON = 278,                   /* COLON  */
    SEMICOLON = 279,               /* SEMICOLON  */
    COMMA = 280,                   /* COMMA  */
    OB = 281,                      /* OB  */
    CB = 282,                      /* CB  */
    OCB = 283,                     /* OCB  */
    CCB = 284,                     /* CCB  */
    OSB = 285,                     /* OSB  */
    CSB = 286,                     /* CSB  */
    DOT = 287,                     /* DOT  */
    EQUAL = 288,                   /* EQUAL  */
    QUOTE = 289                    /* QUOTE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 57 "/home/stele/CLionProjects/client_server/aql/aql.y"

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

#line 127 "aql.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_AQL_TAB_H_INCLUDED  */
