/*******************************************************************

        PROPRIETARY NOTICE

These coded instructions, statements, and computer programs contain
proprietary information of the Visual Urlang project, and are protected
under copyright law. They may not be distributed, copied, or used except
under the provisions of the terms of the End-User License Agreement, in
the file "EULA.md", which should have been included with this file.

        Copyright Notice

    (c) 2020 The Visual Urlang Project.
              All rights reserved.
********************************************************************/

#include <iostream>

#include "AST/Decl.h"
#include "AST/Stmt.h"
#include "Scope.h"

void DimDecl::print(size_t indent)
{
    std::cout << blanks(indent) << "[DimDecl: " << m_name << " type: "
              << "blanktype"
              << "]";
}

void DimDecl::genSymTabs(Scoped *superNode, Scope *superScope)
{
    superNode->regDim(this);
}

void ParamDecl::genSymTabs(Scoped *superNode, Scope *superScope)
{
    superNode->regArg(this);
}

void FunDecl::regDim(DimDecl *decl)
{
    m_scope->reg(new Sym(decl->name(), decl, Sym::Kind::evLocal));
}

void FunDecl::genSymTabs(Scoped *superNode, Scope *superScope)
{
    initScope(superScope);
    superNode->regFun(this);
    for (auto p : m_formals)
        p->genSymTabs(this, m_scope);
    for (auto n : m_code->getCode())
        n->genSymTabs(this, m_scope);
}

void FunDecl::print(size_t indent)
{
    std::cout << blanks(indent) << "[FunDecl: " << m_name << " rtype: "
              << "blanktype\n";
    m_code->print(indent + 2);
    std::cout << "\n" << blanks(indent) << "]";
}
