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

#include "Module.h"
#include "Scope.h"
#include "TypeLoc.h"
#include "TypeRepr.h"

void TypeLoc::resolveInScope(Scope *aScope)
{
    m_type = m_repr->resolveInScope(aScope);
}

void TypeLoc::print(size_t indent)
{
    if (m_repr)
        m_repr->print(indent);
    else
        std::cout << "<empty-typeloc>";
}

Type *TypeRepr::resolveInScope(Scope *aScope)
{
    std::cout << "Unimplemented TypeRepr::resolveInScope in class "
              << typeid(*this).name() << "\n";
    return nullptr;
}

void BuiltinTypeRepr::print(size_t indent)
{
    std::cout << "(Builtin-type: " << m_builtinKind << ")";
}

Type *IdTypeRepr::resolveInScope(Scope *aScope)
{
    Sym *aSym = aScope->find(m_id);
    if (!aSym)
    {
        std::cout << "unresolved typerepr: " << m_id << "\n";
        return nullptr;
    }

    if (aSym->isCls())
    {
        return new ClassInstType(dynamic_cast<Class *>(aSym->decl()), {});
    }
    else
        std::cout << "sym: " << aSym->name() << "\n";
    return nullptr;
}

void IdTypeRepr::print(size_t indent)
{
    std::cout << "(id-type: " << m_id << ")";
}

void DotTypeRepr::print(size_t indent)
{
    std::cout << "(dot-type: (";
    m_base->print(indent);
    std::cout << ").";
    m_member->print(indent);
    std::cout << ")";
}

Type *GenericTypeInstRepr::resolveInScope(Scope *aScope)
{
    Type *base = m_base->resolveInScope(aScope);
    if (ClassInstType *bCls = dynamic_cast<ClassInstType *>(base))
    {
        for (auto p : m_args)
            bCls->addArg(p->resolveInScope(aScope));
        return bCls;
    }
    else
    {
        std::cout << "error: Base is not a class.";
    }
    return nullptr;
}

void GenericTypeInstRepr::print(size_t indent)
{
    std::cout << "(gen-inst-type:";
    m_base->print(indent);
    std::cout << "(";
    for (const auto &ty : m_args)
    {
        ty->print(indent);
        std::cout << ", ";
    }
    std::cout << ")";
}
