%{
#define YY_NO_UNISTD_H

#include "parse.h"
%}

%option noyywrap
%option stack
%option yylineno
%option extra-type = "void *"

%{

%}

COMMENT \"(\\.|[^"])*\"

%%

[ \t\r\n]+

"Instance"  return TK_INSTANCE;
