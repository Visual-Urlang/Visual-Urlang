%{
#include "VUComp.h"
#include "parse.h"

#define YY_NO_UNISTD_H
#define isatty(X) NULL
%}

%option noyywrap
%option stack
%option yylineno
%option reentrant
%option extra-type = "VU_Parser *"
%option prefix = "vuc"

%{

#define YY_USER_ACTION \
    yyextra->recOldPos(); \
    for(int i = 0; yytext[i] != '\0'; i++) \
    { \
        if(yytext[i] == '\n') \
        { \
            yyextra->cr(); \
        } \
        else \
            yyextra->incCol(); \
    }

#define prs(x) yyextra->parse(TOK_##x)

%}

DIGIT ([0-9])
LTR ([a-zA-Z_\xA8\xAA\xAD\xAF\xB2\xB5\xB7\xB8\xB9\xBA\xBC\xBD\xBE]|[\xC0-\xFF][\x80-\xBF]*|\\u([0-9a-fA-F]{4}))

NEWLINE ((\n)|(\r)|(\r\n))

COMMENT \"(\\.|[^"])*\"

%%

"_"{NEWLINE}        { /* line continuation */ }
{NEWLINE}           { yyextra->parse(TOK_EOL); }

"As"            { prs(AS); }
"Call"          { yyextra->parse(TOK_CALL); }
"Class"         { prs(CLASS); }
"Dim"           { prs(DIM); }
"End"           { prs(END); }
"Function"      { prs(FUNCTION); }
"Public"        { prs(PUBLIC); }

"Integer"       { prs(INTEGER); }


">>="			{ return(TOK_RIGHT_ASSIGN); }
"<<="			{ return(TOK_LEFT_ASSIGN); }
"+="			{ return(TOK_ADD_ASSIGN); }
"-="			{ return(TOK_SUB_ASSIGN); }
"*="			{ return(TOK_MUL_ASSIGN); }
"/="			{ return(TOK_DIV_ASSIGN); }
"%="			{ return(TOK_MOD_ASSIGN); }
"&="			{ return(TOK_AND_ASSIGN); }
"^="			{ return(TOK_XOR_ASSIGN); }
"|="			{ return(TOK_OR_ASSIGN); }
">>"			{ return(TOK_RIGHT_OP); }
"<<"			{ return(TOK_LEFT_OP); }
"++"			{ return(TOK_INC_OP); }
"--"			{ return(TOK_DEC_OP); }
"->"			{ return(TOK_PTR_OP); }
"&&"			{ return(TOK_AND_OP); }
"||"			{ return(TOK_OR_OP); }
"<="			{ return(TOK_LE_OP); }
">="			{ return(TOK_GE_OP); }
"=="			{ return(TOK_EQ_OP); }
"!="			{ return(TOK_NE_OP); }

"("                { yyextra->parse(TOK_LBRACKET); }
")"                { yyextra->parse(TOK_RBRACKET); }
"["                { yyextra->parse(TOK_LSBRACKET); }
"]"                { yyextra->parse(TOK_RSBRACKET); }
"+"                { yyextra->parse(TOK_PLUS); }
"-"                { yyextra->parse(TOK_MINUS); }
"*"                { yyextra->parse(TOK_STAR); }
"/"                { yyextra->parse(TOK_FSLASH); }
"."                { yyextra->parse(TOK_DOT); }
"="                { yyextra->parse(TOK_EQUALS); }
","                { yyextra->parse(TOK_COMMA); }

([0-9]+)                        { yyextra->parse(TOK_INTCONSTANT, std::stoi(yytext)); }
(:?{LTR})(:?{LTR}|{DIGIT}|::)* { yyextra->parse(TOK_IDENTIFIER, yytext); }


"'"[^\n\r]*         { }

[ \t]+          {}
