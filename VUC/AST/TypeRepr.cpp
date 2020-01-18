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

#include "TypeLoc.h"
#include "TypeRepr.h"

void TypeLoc::print(size_t indent)
{
    if (m_repr)
        m_repr->print(indent);
    else
        std::cout << "<empty-typeloc>";
}

void BuiltinTypeRepr::print(size_t indent)
{
    std::cout << "(Builtin-type: " << m_builtinKind << ")";
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
