%{
#include "parse.h"

#define YY_NO_UNISTD_H
#define isatty() NULL
%}

%option noyywrap
%option stack
%option yylineno
%option extra-type = "void *"
%option prefix = "vuc"

%{

%}

COMMENT \"(\\.|[^"])*\"

%%

[ \t\r\n]+

