%option noyywrap case-insensitive
%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <stdbool.h>
  
  #include "ast.h"
  #include "aql.tab.h"
%}

integer_pattern ([-+]?[0-9]+)
float_pattern ([-+]?[0-9]+\.[0-9]+)
boolean_pattern ("TRUE"|"FALSE")
string_pattern ([a-zA-Z0-9_][a-zA-Z0-9_]*)

%%

"CREATE"   return CREATE;
"REMOVE"   return REMOVE;
"TABLE"    return TABLE;

"INSERT"   return INSERT;
"UPDATE"   return UPDATE;
"WITH"     return WITH;
"FILTER"   return FILTER;
"RETURN"   return RETURN;
"FOR"      return FOR;
"IN"       return IN;

"INTEGER"  {yylval.type = 0; return INTEGER;}
"FLOAT"    {yylval.type = 1; return FLOAT;}
"BOOLEAN"  {yylval.type = 2; return BOOLEAN;}
"VARCHAR"  {yylval.type = 3; return VARCHAR;}

"OR"   {yylval.op = 0; return OP;}
"AND"  {yylval.op = 1; return OP;}

"=="   {yylval.cmp = 0; return CMP;}
"!="   {yylval.cmp = 1; return CMP;}
"<"    {yylval.cmp = 2; return CMP;}
">"    {yylval.cmp = 3; return CMP;}
"<="   {yylval.cmp = 4; return CMP;}
">="   {yylval.cmp = 5; return CMP;}
"~"    {yylval.cmp = 6; return CMP;}

"="  return EQUAL;
"("  return OB;
")"  return CB;
"{"  return OCB;
"}"  return CCB;
"["  return OSB;
"]"  return CSB;
"."  return DOT;
","  return COMMA;
":"  return COLON;
";"  return SEMICOLON;
"'"  return QUOTE;

{integer_pattern}  {yylval.intval = atoi(yytext); return INTVAL;}
{float_pattern}    {yylval.floatval = atof(yytext); return FLOATVAL;}
{boolean_pattern}  {yylval.boolval = atoi(yytext); return BOOLVAL;}
{string_pattern}   {yylval.strval = strdup(yytext);  return STRING;}

[\n] ;
[ \t]+ ;

%%
