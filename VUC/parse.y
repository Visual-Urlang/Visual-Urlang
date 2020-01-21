%include{
#include <iostream>
#include <list>
#include <tuple>
#include <variant>

#include "VUComp.h"
#include "AST/Constant.h"
#include "AST/Expr.h"
#include "AST/Stmt.h"
#include "AST/TypeLoc.h"
#include "AST/Module.h"

#define LEMON_SUPER VU_Parser

typedef void * ClassDeclType;
typedef std::tuple<Token, TypeRepr *> TupTokTypeRepr;

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

// FIXME: need std::variant for this.
/*void addClsDecl(std::vector<Node *> rcvr, ClassDeclType decl)
{
	if (Node * nod = dynamic_cast<Node *>(decl))
		rcvr.push_back(nod);
	else
		for (auto d : dynamic_cast<std::vector<Node *>>(decl))
			rcvr.push_back(d);
}*/ 

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
%left EOL.

%right DOTACCESS.

%default_type { Node * }

file ::= module EOF.

module
	::= opt_eols block_stmt_list(l) opt_eols.
	{
		m_mod = new Unit("-a-unit-", l);
	}

opt_signature
	::= signature.
opt_signature
	::= .

%type opt_signature { std::vector<TypeParamDecl *> }
%type signature { std::vector<TypeParamDecl *> }
%type ofdecl_list { std::vector<TypeParamDecl *> }

signature(S)
	::= OF ofdecl_list(l). { S = l; }

ofdecl_list(L)
	::= IDENTIFIER(i). { L = std::vector<TypeParamDecl *>({new TypeParamDecl(pos(), i.stringValue)}); }
ofdecl_list(L)
	::= ofdecl_list(l) COMMA IDENTIFIER(i). { (L = l).push_back(new TypeParamDecl(pos(), i.stringValue)); }

opt_inherits_list
	::= inherits_list.
opt_inherits_list
	::= .

%type opt_inherits_list { std::vector<TypeLoc *> }
%type opt_implements_list { std::vector<TypeLoc *> }
%type inherits_list { std::vector<TypeLoc *> }
%type implements_list { std::vector<TypeLoc *> }
%type type_loc_list { std::vector<TypeLoc *> }

inherits_list(L)
	::= INHERITS type_loc_list(l) eols. { L = l; }

opt_implements_list
	::= implements_list.
opt_implements_list
	::= .

implements_list(L)
	::= IMPLEMENTS type_loc_list(l) eols. { L = l; }

type_loc_list(L)
	::= type_name_list(l).
	{
		std::transform(l.begin(), l.end(), std::back_inserter(L),
			[](TypeRepr * i) { return new TypeLoc(i); } );
	}

eol
	::= EOL.

opt_eols
	::= eols.
opt_eols
	::= .

eols
	::= eol.
eols
	::= eols eol.

cls_stmt(C)
	::= opt_visibility_spec CLASS IDENTIFIER(i) opt_signature(sig) eols 
		opt_inherits_list(inh)
		opt_implements_list(imp)
		opt_block_stmt_list(code)
		END CLASS.
	{
		C = new Class(pos(), i.stringValue, inh, imp, sig, code);
	}

func_stmt(F)
	::= opt_visibility_spec FUNCTION IDENTIFIER(n) 
		opt_param_list(p) opt_as_clause(t) EOL block_stmt_list(l) EOL END FUNCTION.
		{
			F = new FunDecl(pos(), n.stringValue, p, new TypeLoc(t), l);
		}

%type opt_block_stmt_list { CompoundStmt * }
%type block_stmt_list { CompoundStmt * }

opt_block_stmt_list(L)
	::= block_stmt_list(l) eols. { L = l; }
opt_block_stmt_list(L)
	::= . { L = new CompoundStmt(pos(), {}); }

block_stmt_list(L)
	::= block_stmt(s). { L = new CompoundStmt(pos(), {s}); }
block_stmt_list(L)
	::= block_stmt_list(l) eols block_stmt(s). { (L = l)->addCode(s); }

block_stmt ::= cls_stmt.
block_stmt ::= func_stmt.
block_stmt ::= variable_stmt.
block_stmt ::= bracketed_expr.
block_stmt(B) ::= dotaccess_expr(c) argument_expr_list(l).
	{
		B = new FunCallExpr(pos(), c, l);
	}
block_stmt(B)
	::= dotaccess_expr(c) LBRACKET argument_expr_list(l) RBRACKET.
	{
		B = new FunCallExpr(pos(), c, l);
	}

%type opt_param_list { std::vector<ParamDecl*> }
%type param_list { std::vector<ParamDecl *> }

opt_param_list
	::= LBRACKET param_list RBRACKET.
opt_param_list
	::= .

param_list(P)
	::= pass_style variable_decl_part(p). 
	{
		auto decl = new ParamDecl(pos(), std::get<0>(p).stringValue, TypeLoc(std::get<1>(p)));
		P = std::vector<ParamDecl *>({decl}); 
	}
param_list(P)
	::= param_list(l) pass_style variable_decl_part(p).
	{
		auto decl = new ParamDecl(pos(), std::get<0>(p).stringValue, TypeLoc(std::get<1>(p)));
		(P = l).push_back({decl}); 
	}

pass_style ::= BYVAL.
pass_style ::= BYREF.

opt_visibility_spec
	::= visibility_spec.

%type opt_as_clause { TypeRepr * }

opt_as_clause
	::= .
opt_as_clause(T)
	::= AS type_name(t). { T = t; }

visibility_spec
	::= PRIVATE.
visibility_spec
	::= PUBLIC.

dim_or_visibility_spec
	::= DIM.
dim_or_visibility_spec
	::= visibility_spec.

variable_stmt(S)
	::= dim_or_visibility_spec variable_stmt_els(s).
	{
		S = new DimDecl(pos(), std::get<0>(s).stringValue, TypeLoc(std::get<1>(s))); 
	}

%type variable_stmt_els { TupTokTypeRepr }

variable_stmt_els
	::= variable_decl_part.
variable_stmt_els
	::= variable_stmt_els COMMA variable_decl_part.

%type variable_decl_part { TupTokTypeRepr }

variable_decl_part(P)
	::= IDENTIFIER(s) opt_subscripts AS type_name(t) opt_initialiser.
	{
		P = TupTokTypeRepr(s, t);
	}

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
%type dotaccess_expr { Expr * }

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

dotaccess_expr(E)
	::= primary_expr(e). { E = e; }
dotaccess_expr(E)
	::= dotaccess_expr(e) DOT IDENTIFIER(i). [DOTACCESS]
	{ E = new DotExpr(pos(), i.stringValue, e); }

postfix_expr(E)
	::= dotaccess_expr(e). { E = e; }
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
%type and_expr { Expr * }
%type excl_or_expr { Expr * }
%type incl_or_expr { Expr * }
%type log_and_expr { Expr * }
%type log_or_expr { Expr *}
%type cond_expr { Expr * }
%type assign_expr { Expr * }

unary_expr(E)
	::= postfix_expr(e).  { E = e; }
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

cast_expr(E)
	::= unary_expr(e). { E = e; }
cast_expr
	::= LCARET type_name RCARET cast_expr. [UNA]

mul_expr(E)
	::= cast_expr(e). { E = e; }
mul_expr
	::= mul_expr STAR cast_expr.
mul_expr
	::= mul_expr FSLASH cast_expr.
mul_expr
	::= mul_expr PERCENT cast_expr.

add_expr(E)
	::= mul_expr(e). { E = e; }
add_expr
	::= add_expr PLUS mul_expr.
add_expr
	::= add_expr MINUS mul_expr.

shift_expr(E)
	::= add_expr(e). { E = e; }
shift_expr
	::= shift_expr LEFT_OP add_expr.
shift_expr
	::= shift_expr RIGHT_OP add_expr.

rel_expr(E)
	::= shift_expr(e). { E = e; }
rel_expr
	::= rel_expr LCARET shift_expr.
rel_expr
	::= rel_expr RCARET shift_expr.
rel_expr
	::= rel_expr LE_OP shift_expr.
rel_expr
	::= rel_expr GE_OP shift_expr.

eq_expr(E)
	::= rel_expr(e). { E = e; }
eq_expr
	::= eq_expr EQ_OP rel_expr.
eq_expr
	::= eq_expr NE_OP rel_expr.

and_expr(E)
	::= eq_expr(e). { E = e; }
and_expr
	::= and_expr AND eq_expr.

excl_or_expr(E)
	::= and_expr(e). { E = e; }
excl_or_expr
	::= excl_or_expr HAT and_expr.

incl_or_expr(E)
	::= excl_or_expr(e). { E = e; }
incl_or_expr
	::= incl_or_expr BAR excl_or_expr.

log_and_expr(E)
	::= incl_or_expr(e). { E = e; }
log_and_expr
	::= log_and_expr AND_OP incl_or_expr.

log_or_expr(E)
	::= log_and_expr(e). { E = e; }
log_or_expr
	::= log_or_expr OR_OP log_and_expr.

cond_expr(E)
	::= log_or_expr(e). { E = e; }
cond_expr
	::= log_or_expr QUESTION expr COLON cond_expr.

assign_expr(E)
	::= cond_expr(e). { E = e; }
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

expr(E)
	::= assign_expr(e). { E = e; }
expr(E)
	::= expr(e) SEMICOLON assign_expr. { E = e; printf("generated comma expr\n"); }

%type primary_type_name { TypeRepr * }
%type type_name { TypeRepr * }

primary_type_name(T)
	::= INTEGER. { T = new BuiltinTypeRepr(pos(), BuiltinTypeRepr::evInteger); }
primary_type_name(T)
	::= IDENTIFIER(i). { T = new IdTypeRepr(pos(), i.stringValue); }
primary_type_name(T)
	::= LBRACKET type_name(t) RBRACKET. { T = t; }
primary_type_name(T)
	::= primary_type_name(t) LBRACKET OF type_name_list(l) RBRACKET.
	{
		T = new GenericTypeInstRepr(pos(), t, l);
	}
primary_type_name(T)
	::= primary_type_name(t) DOT IDENTIFIER(i).
	{
		T = new DotTypeRepr(pos(), new IdTypeRepr(pos(), i.stringValue), t);
	}

%type type_name_list { std::vector<TypeRepr *> }

type_name_list(L)
	::= type_name(t). { L = std::vector<TypeRepr *>({t}); }
type_name_list(L)
	::= type_name_list(l) COMMA type_name(t). { (L = l).push_back(t); }

type_name(T)
	::= primary_type_name(t). { T = t; }