%include{
#include <iostream>

#include "VUComp.h"
#include "AST/IdExpr.h"

#define LEMON_SUPER VU_Parser
}


%code {

VU_Parser * VU_Parser::create(std::string fName, std::string & fText)
{
	return new yypParser(fName, fText);
}

Position VU_Parser::pos()
{
		yypParser *self = (yypParser *)this;
	return Position(self->m_line, self->m_col, self->m_pos);
}

}

%syntax_error {
	const YYACTIONTYPE stateno = yytos->stateno;
	size_t eolPos = fText.find("\n", m_pos);
	std::string eLine = fText.substr(m_pos, eolPos - m_pos);

	std::cerr << "vuc: " << fName << "(" << std::to_string(m_line) + "," 
			  << std::to_string(m_col) << "): "
			  << "Error V1001: Syntax error: unexpected " 
			  << yyTokenName[yymajor] << "\n";

	std::cerr << "+ " << eLine << "\n";
	std::cerr << "+ ";
	for (int i = 1; i < m_col; i++)
		std::cerr << " ";
	std::cerr << "^";

	std::cerr << "\n\texpected one of: \n";

	for (unsigned i = 0; i < YYNTOKEN; ++i)
	{
		int yyact = yy_find_shift_action(i, stateno);
		if (yyact != YY_ERROR_ACTION && yyact != YY_NO_ACTION)
			std::cerr << "\t" << yyTokenName[i] << "\n";
	}

}


%token_type    {Token}
%token_prefix  TOK_

%token CALL.

%left COMMA.
%right EQUALS.
%right RIGHT_ASSIGN LEFT_ASSIGN MOD_ASSIGN DIV_ASSIGN MUL_ASSIGN.

%right QUESTION COLON.

%left EQ_OP.
%left NE_OP LE_OP GE_OP LCARET RCARET.

%left PLUS MINUS.
%left STAR PERCENT FSLASH.
%right UNA.

%left DOT PTR_OP.
%left UN.

%left LBRACKET LSBRACKET RBRACKET RSBRACKET.

%right DOTACCESS.

%default_type { Node * }

file ::= statement_list EOF.

statement_break ::= EOL.

statement_list ::= statement statement_break.
statement_list ::= statement_list statement statement_break.

statement ::= dotaccess_expr.
statement ::= dotaccess_expr argument_expr_list.

%type primary_expr { Expr * }

primary_expr(e)
	::= IDENTIFIER(I). { e = new IdentExpr(pos(), I.stringValue); }
primary_expr
	::= CONSTANT.
primary_expr
	::= STRING_LITERAL.
primary_expr
	::= LBRACKET expr RBRACKET.

dotaccess_expr
	::= primary_expr.
dotaccess_expr
	::= dotaccess_expr DOT IDENTIFIER. [DOTACCESS]

postfix_expr
	::= dotaccess_expr.
postfix_expr
	::= postfix_expr LSBRACKET expr RSBRACKET. [UN]
postfix_expr
	::= postfix_expr LBRACKET RBRACKET. [UN]
postfix_expr
	::= postfix_expr LBRACKET argument_expr_list RBRACKET. [UN]
postfix_expr
	::= postfix_expr PTR_OP IDENTIFIER. [DOTACCESS]
postfix_expr
	::= postfix_expr INC_OP. 
postfix_expr
	::= postfix_expr DEC_OP.

argument_expr_list
	::= assign_expr.
argument_expr_list
	::= argument_expr_list COMMA assign_expr.

unary_expr
	::= postfix_expr.
unary_expr
	::= unary_operator cast_expr. [UNA]
unary_expr
	::= SIZEOF unary_expr. [UN]
unary_expr
	::= SIZEOF LBRACKET type_name RBRACKET. [UN]

unary_operator
	::= EXCLAMATION.
unary_operator	
	::= AND.	
unary_operator	
	::= STAR.	
unary_operator	
	::= PLUS.	
unary_operator	
	::= MINUS.	
unary_operator	
	::= TILDE.

cast_expr
	::= unary_expr.
cast_expr
	::= LBRACKET type_name RBRACKET cast_expr. [UNA]

mul_expr
	::= cast_expr.
mul_expr
	::= mul_expr STAR cast_expr.
mul_expr
	::= mul_expr FSLASH cast_expr.
mul_expr
	::= mul_expr PERCENT cast_expr.

add_expr
	::= mul_expr.
add_expr
	::= add_expr PLUS mul_expr.
add_expr
	::= add_expr MINUS mul_expr.

shift_expr
	::= add_expr.
shift_expr
	::= shift_expr LEFT_OP add_expr.
shift_expr
	::= shift_expr RIGHT_OP add_expr.

rel_expr
	::= shift_expr.
rel_expr
	::= rel_expr LCARET shift_expr.
rel_expr
	::= rel_expr RCARET shift_expr.
rel_expr
	::= rel_expr LE_OP shift_expr.
rel_expr
	::= rel_expr GE_OP shift_expr.

eq_expr
	::= rel_expr.
eq_expr
	::= eq_expr EQ_OP rel_expr.
eq_expr
	::= eq_expr NE_OP rel_expr.

and_expr
	::= eq_expr.
and_expr
	::= and_expr AND eq_expr.

excl_or_expr
	::= and_expr.
excl_or_expr
	::= excl_or_expr HAT and_expr.

incl_or_expr
	::= excl_or_expr.
incl_or_expr
	::= incl_or_expr BAR excl_or_expr.

log_and_expr
	::= incl_or_expr.
log_and_expr
	::= log_and_expr AND_OP incl_or_expr.

log_or_expr
	::= log_and_expr.
log_or_expr
	::= log_or_expr OR_OP log_and_expr.

cond_expr
	::= log_or_expr.
cond_expr
	::= log_or_expr QUESTION expr COLON cond_expr.

assign_expr
	::= cond_expr.
assign_expr
	::= unary_expr assign_op assign_expr.

assign_op
	::= EQUALS. [EQUALS]
assign_op
	::= MUL_ASSIGN. [EQUALS]
assign_op
	::= DIV_ASSIGN. [EQUALS]
assign_op
	::= MOD_ASSIGN. [EQUALS]
assign_op
	::= ADD_ASSIGN. [EQUALS]
assign_op
	::= SUB_ASSIGN. [EQUALS]
assign_op
	::= LEFT_ASSIGN. [EQUALS]
assign_op
	::= RIGHT_ASSIGN. [EQUALS]
assign_op
	::= AND_ASSIGN. [EQUALS]
assign_op
	::= XOR_ASSIGN. [EQUALS]
assign_op
	::= OR_ASSIGN. [EQUALS]

expr
	::= assign_expr.
expr
	::= expr COMMA assign_expr.

type_name
	::= TYPE.