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

#include "Expr.h"
#include "Scope.h"
#include "Scoped.h"
#include "Type.h"

Type *Expr::getType(Scoped *aScoped)
{
    std::cout << "unimplemented getType in " << typeid(*this).name() << "\n";
    return nullptr;
}

Type *FunCallExpr::getType(Scoped *scope)
{
    FunType *funType = dynamic_cast<FunType *>(m_func->getType(scope));

    printf("Fun Type:\n");
    funType->print(12);

    for (auto m : m_args)
    {
        /* check if arg matches */
    }

    return funType->rType();
}

void FunCallExpr::print(size_t indent)
{
    std::cout << blanks(indent) << "[Funcall: recvr: \n";
    m_func->print(indent + 2);

    std::cout << "\n" << blanks(indent) << "args: \n";

    for (auto a : m_args)
    {
        std::cout << blanks(indent) << "arg: \n";
        a->print(indent + 2);
        std::cout << "\n";
    }

    std::cout << blanks(indent) << "]";
}

Type *IdentExpr::getType(Scoped *scope)
{
    if (Sym *cand = scope->scope()->find(m_id))
        return cand->type();
    else
    {
        std::cout << "Error: Undeclared identifier " << m_id << "\n";
        return nullptr;
    }
}

void IdentExpr::print(size_t indent)
{
    std::cout << blanks(indent) << "[IdentExpr: " << m_id << "]";
}

Type *DotExpr::getType(Scoped *scope)
{
    Type *baseType = m_base->getType(scope);
    Type *mem = baseType->getTypeOfMember(m_id);
    // baseType->print(12);
    return mem;
}

void DotExpr::print(size_t indent)
{
    std::cout << blanks(indent) << "[DotExpr: \n";
    m_base->print(indent + 2);
    std::cout << "." << m_id || "]";
}
