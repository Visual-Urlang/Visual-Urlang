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
};

class IdTypeRepr : public TypeRepr
{
    std::string m_id;

  public:
    IdTypeRepr(Position pos, std::string id) : TypeRepr(pos), m_id(id) {}
};