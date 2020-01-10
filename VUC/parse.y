%include{
#include <iostream>
#include <list>

#include "VUComp.h"
#include "AST/Constant.h"
#include "AST/IdExpr.h"
#include "AST/Stmt.h"
#include "AST/TypeLoc.h"
#include "AST/FunCallE.h"
#include "AST/Module.h"

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
	return Position(self->m_oldLine, self->m_oldCol, self->m_oldPos, self->m_line, self->m_col, self->m_pos);
}

}

%syntax_error {
	const YYACTIONTYPE stateno = yytos->stateno;
	size_t eolPos = fText.find("\n", m_pos);
	std::string eLine = fText.substr(m_pos, eolPos - m_pos);
	size_t i;

	std::cerr << "vuc: " << fName << "(" << std::to_string(m_line) + "," 
			  << std::to_string(m_col) << "): "
			  << "Error V1001: Syntax error: unexpected " 
			  << yyTokenName[yymajor] << "\n";

	std::cerr << "+ " << eLine << "\n";
	std::cerr << "+ ";
	for (i = 0; i < m_oldCol; i++)
		std::cerr << " ";
	for (; i < m_col; i++)
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

file ::= module EOF.

module
	::= CLASS opt_signature cls_decl_list(l).
	{
		m_mod = new Class(pos(), "-a-class-", new CompoundStmt(pos(), l));
	}
module
	::= BAS bas_decl_list.

opt_signature
	::= signature.
opt_signature
	::= .

signature
	::= SIGNATURE.

%type cls_decl_list { std::vector<Node *> }

cls_decl_list(L)
	::= cls_decl(c) EOL. { L = std::vector<Node *>({c}); }
cls_decl_list(L)
	::= cls_decl_list(l) cls_decl(c) EOL. { (L = l).push_back(c); }
bas_decl_list
	::= .

cls_decl
	::= block_stmt.

block_stmt ::= variable_stmt.
block_stmt ::= bracketed_expr.
block_stmt ::= dotaccess_expr argument_expr_list.

visibility_spec
	::= DIM.
visibility_spec
	::= PRIVATE.

variable_stmt(S)
	::= visibility_spec variable_stmt_els. { S = new Node(pos()); }

variable_stmt_els
	::= variable_decl_part.
variable_stmt_els
	::= variable_stmt_els COMMA variable_decl_part.

variable_decl_part
	::= IDENTIFIER opt_subscripts AS type_name opt_initialiser.

opt_initialiser
	::= .
opt_initialiser
	::= EQUALS expr.

opt_subscripts
	::= .
opt_subscripts
	::= subscripts.

subscripts
	::= subscript.
subscripts
	::= subscripts subscript.

subscript ::= LBRACKET INTCONSTANT RBRACKET.

%type constant { Constant * }

constant(C)
	::= INTCONSTANT(i). { C = new Constant(pos(), i.intValue); }

%type bracketed_expr { Expr * }
%type primary_expr { Expr * }
%type postfix_expr { Expr * }

bracketed_expr(E)
	::= LBRACKET expr(e) RBRACKET.
	{ E = e; }

primary_expr(E)
	::= IDENTIFIER(i). { E = new IdentExpr(pos(), i.stringValue); }
primary_expr
	::= constant.
primary_expr
	::= STRING_LITERAL.
primary_expr(E)
	::= bracketed_expr(e). { E = e; }

dotaccess_expr
	::= primary_expr.
dotaccess_expr
	::= dotaccess_expr DOT IDENTIFIER. [DOTACCESS]

postfix_expr
	::= dotaccess_expr.
postfix_expr
	::= postfix_expr LSBRACKET expr RSBRACKET. [UN]
postfix_expr(P)
	::= postfix_expr(e) LBRACKET RBRACKET. [UN]
	{
		P = new FunCallExpr(pos(), e, {});
	}
postfix_expr(P)
	::= postfix_expr(e) LBRACKET argument_expr_list(l) RBRACKET. [UN]
	{
		P = new FunCallExpr(pos(), e, l);
	}
postfix_expr
	::= postfix_expr PTR_OP IDENTIFIER. [DOTACCESS]
postfix_expr
	::= postfix_expr INC_OP. 
postfix_expr
	::= postfix_expr DEC_OP.

%type argument_expr_list { std::list<Expr *> }

argument_expr_list(L)
	::= assign_expr(e). { L = std::list<Expr *>({e}); }
argument_expr_list(L)
	::= argument_expr_list(l) COMMA assign_expr(e). { (L=l).push_back (e); }

%type unary_expr { Expr * }
%type cast_expr { Expr * }
%type mul_expr { Expr * }
%type add_expr { Expr * }
%type shift_expr { Expr * }
%type rel_expr { Expr * }
%type eq_expr { Expr * }
%type excl_or_expr { Expr * }
%type incl_or_expr { Expr * }
%type log_and_expr { Expr * }
%type log_or_expr { Expr *}
%type cond_expr { Expr * }
%type assign_expr { Expr * }

unary_expr
	::= postfix_expr.
unary_expr
	::= unary_operator cast_expr. [UNA]
unary_expr
	::= SIZEOF unary_expr. [UN]
unary_expr
	::= SIZEOF LCARET type_name RCARET. [UN]

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
	::= LCARET type_name RCARET cast_expr. [UNA]

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

%type expr { Expr * }

expr
	::= assign_expr.
expr
	::= expr COMMA assign_expr.

%type primary_type_name { TypeRepr * }
%type type_name { TypeRepr * }

primary_type_name(T)
	::= INTEGER. { T = new BuiltinTypeRepr(pos(), BuiltinTypeRepr::evInteger); }
primary_type_name(T)
	::= IDENTIFIER(i). { T = new IdTypeRepr(pos(), i.stringValue); }
primary_type_name(T)
	::= LBRACKET type_name(t) RBRACKET. { T = t; }

generic_type_binding
	::= primary_type_name.
generic_type_binding
	::= primary_type_name LBRACKET type_name_list RBRACKET.

postfix_type_name
	::= generic_type_binding DOT generic_type_binding .
postfix_type_name
	::= generic_type_binding .

type_name_list
	::= type_name.
type_name_list
	::= type_name_list COMMA type_name.

type_name
	::= postfix_type_name.