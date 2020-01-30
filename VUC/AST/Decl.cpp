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

void TypeParamDecl::synthType(Scoped *ctx) {}

void DimDecl::print(size_t indent)
{
    std::cout << blanks(indent) << "[DimDecl: " << m_name << " type:\n";
    m_typeLoc.print(indent);
    std::cout << "]";
}

void DimDecl::genSymTabs(Scoped *superNode, Scope *superScope)
{
    superNode->regDim(this);
}

DimDecl *DimDecl::typeCheck(Scoped *superNode)
{
    m_typeLoc.typeCheck(superNode->scope());
    return this;
}

Type *DimDecl::type() { return m_typeLoc.type(); }

void ParamDecl::genSymTabs(Scoped *superNode, Scope *superScope)
{
    superNode->regArg(this);
}

void FunDecl::regDim(DimDecl *decl)
{
    m_scope->reg(new Sym(decl->name(), decl, Sym::Kind::evLocal));
}

FunDecl *FunDecl::typeCheck(Scoped *superNode)
{
    m_rType->typeCheck(m_scope);

    m_scope->reg(new InternalTypeSym("$ReturnType", this, m_rType->type()));

    for (auto p : m_formals)
    {
        /* NO! We get their type by asking the decl.
         * m_scope->reg(new Sym(p->name(), p, Sym::evType)); */
        p->typeCheck(this); /* consider initialisers*/
    }

    for (auto &n : m_code->getCode())
        n = n->typeCheck(this);
    return this;
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
    std::cout << blanks(indent) << "[FunDecl: " << m_name << " rtype: ";
    m_rType->print(indent);
    std::cout << "\n" << blanks(indent) << "args:\n";
    for (const auto f : m_formals)
    {
        f->print(indent);
        std::cout << "\n";
    }
    m_code->print(indent + 2);
    std::cout << "\n" << blanks(indent) << "]";
}
