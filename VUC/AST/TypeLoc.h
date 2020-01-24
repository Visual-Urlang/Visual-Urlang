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

#pragma once

#include "Type.h"
#include "TypeRepr.h"

/* Represents a location in the source where a type can be. */
class TypeLoc
{
    TypeRepr *m_repr = nullptr;
    Type *m_type = nullptr;

  public:
    explicit TypeLoc() {}
    explicit TypeLoc(TypeRepr *repr) : m_repr(repr) {}

    TypeRepr *repr() { return m_repr; }

    void resolveInScope(Scope *aScope);
    void typeCheck(Scope *aScope);

    void print(size_t indent);
};
