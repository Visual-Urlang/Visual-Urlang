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

    virtual void associateArgs(std::vector<TypeRepr *> args)
    {
        std::cout << "unimplemented assocArgs in " << typeid(*this).name()
                  << "\n";
    }

    virtual Type *resolveInScope(Scope *aScope);

    virtual Type *realise(Scope *superNode)
    {
        std::cout << "\n\n\n\nunimplemented realise in " << typeid(*this).name()
                  << "\n\n\n\n";
        return nullptr;
    }
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

/*class IdTypeRepr : public TypeRepr
{
    std::string m_id;

  public:
    IdTypeRepr(Position pos, std::string id) : TypeRepr(pos), m_id(id) {}

    virtual Type *resolveInScope(Scope *aScope);

    virtual void print(size_t indent);
};*/

class DotTypeRepr : public TypeRepr
{
    TypeRepr *m_member;
    TypeRepr *m_base;

  public:
    DotTypeRepr(Position _pos, TypeRepr *member, TypeRepr *base)
        : TypeRepr(_pos), m_member(member), m_base(base)
    {
    }

    virtual void associateArgs(std::vector<TypeRepr *> args)
    {
        m_member->associateArgs(args);
    }

    virtual void print(size_t indent);
};

class GenericTypeInstRepr : public TypeRepr
{
    std::string m_base;
    std::vector<TypeRepr *> m_args;

  public:
    GenericTypeInstRepr(Position pos, std::string base,
                        std::vector<TypeRepr *> typeReprs)
        : TypeRepr(pos), m_base(base), m_args(typeReprs)
    {
    }

    virtual void associateArgs(std::vector<TypeRepr *> args) { m_args = args; }

    virtual Type *resolveInScope(Scope *aScope);

    virtual Type *realise(Scope *superNode);

    virtual void print(size_t indent);
};