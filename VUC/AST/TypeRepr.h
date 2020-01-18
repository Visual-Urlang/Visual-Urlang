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

#include <vector>

#include "Expr.h"
#include "Node.h"

class TypeRepr : public Node
{
  public:
    explicit TypeRepr(Position pos) : Node(pos) {}
};

/* A builtin type. */
class BuiltinTypeRepr : public TypeRepr
{
  public:
    enum BuiltinKind
    {
        evByte,
        evBoolean,
        evInteger,
        evLong,
        evLongLong,
        evWord,
        evSingle,
        evDouble,
        evCharacter,
        evDate,
        evObject,
        evVariant,
    } m_builtinKind;

    BuiltinTypeRepr(Position pos, BuiltinKind builtinKind)
        : TypeRepr(pos), m_builtinKind(builtinKind)
    {
    }

    virtual void print(size_t indent);
};

class IdTypeRepr : public TypeRepr
{
    std::string m_id;

  public:
    IdTypeRepr(Position pos, std::string id) : TypeRepr(pos), m_id(id) {}

    virtual void print(size_t indent);
};

class DotTypeRepr : public TypeRepr
{
    IdTypeRepr *m_member;
    TypeRepr *m_base;

  public:
    DotTypeRepr(Position _pos, IdTypeRepr *member, TypeRepr *base)
        : TypeRepr(_pos), m_member(member), m_base(base)
    {
    }

    virtual void print(size_t indent);
};

class GenericTypeInstRepr : public TypeRepr
{
    TypeRepr *m_base;
    std::vector<TypeRepr *> m_args;

  public:
    GenericTypeInstRepr(Position pos, TypeRepr *base,
                        std::vector<TypeRepr *> typeReprs)
        : TypeRepr(pos), m_base(base), m_args(typeReprs)
    {
    }

    virtual void print(size_t indent);
};