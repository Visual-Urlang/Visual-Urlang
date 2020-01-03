%{
#include "VUComp.h"
#include "parse.h"

#define YY_NO_UNISTD_H
#define isatty() NULL
%}

%option noyywrap
%option stack
%option yylineno
%option reentrant
%option extra-type = "VU_Parser *"
%option prefix = "vuc"

%{

#define YY_USER_ACTION \
    for(int i = 0; yytext[i] != '\0'; i++) \
    { \
        if(yytext[i] == '\n') \
        { \
            yyextra->cr(); \
        } \
        else \
            yyextra->incCol(); \
    }

%}

DIGIT ([0-9])

NEWLINE ((\n)|(\r)|(\r\n))

COMMENT \"(\\.|[^"])*\"

%%

"["                { yyextra->parse(TOK_LSBRACKET); }
"]"

[A-Za-z_$][0-9A-Za-z_$]* { yyextra->parse(TOK_IDENTIFIER); }

[ \t\n\r]+
