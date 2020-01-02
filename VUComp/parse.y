%include{
#include "VUComp.h"

#define LEMON_SUPER VU_Parser
}

%token_type    {Token}

%left COMMA.
%left SuperUnary.
%left HyperUnary.
%left LBRACKET LSBRACKET RBRACKET RSBRACKET.
%right DotAccess.

file ::= statement_list.

statement_break ::= EOL.

statement_list ::= statement statement_break.
statement_list ::= statement_list statement statement_break.

statement ::= dot_access expr_list. [HyperUnary]
statement ::= CALL dot_access expr_list. [HyperUnary]

expr ::= primary_expr.
expr ::= NOEXP.

expr_list ::= expr.
expr_list ::= expr_list COMMA expr.

bracketed_expr
	::= LBRACKET expr RBRACKET.


/* function call */
primary_expr
    ::= primary_expr LBRACKET expr_list RBRACKET. [SuperUnary]
/* dot access */
primary_expr
	::= dot_access.

field
	::= bracketed_expr.
field
	::= identifier.
field
	::= constant.
field
	::= field LSBRACKET expr RSBRACKET. [SuperUnary]

dot_access
	::= field.
dot_access
	::= dot_access DOT field.

constant ::= CONSTANT.
identifier ::= IDENTIFIER.
