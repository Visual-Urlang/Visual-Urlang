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

#include <list>

#include "Node.h"

class Decl;
class Type;

class Expr : public Node
{
  public:
    explicit Expr(Position pos) : Node(pos) {}

    virtual Type *getType(Scoped *scope);
};

class FunCallExpr : public Expr
{
    Expr *m_func;
    std::list<Expr *> m_args;

  public:
    FunCallExpr(Position pos, Expr *func, std::list<Expr *> exprs)
        : Expr(pos), m_func(func), m_args(exprs)
    {
    }

    virtual void print(size_t indent);
};

class IdentExpr : public Expr
{
    const std::string m_id;
    /* the decl to which this ident refers */
    Decl *m_decl = nullptr;

  public:
    explicit IdentExpr(Position _pos, std::string id) : Expr(_pos), m_id(id) {}

    Type *getType(Scoped *scope) override;

    virtual void print(size_t indent);

    std::string id() const;
};

class DotExpr : public Expr
{
    const std::string m_id;
    Expr *m_base;

  public:
    explicit DotExpr(Position _pos, std::string id, Expr *base)
        : Expr(_pos), m_id(id), m_base(base)
    {
    }

    virtual void print(size_t indent);
};

inline std::string IdentExpr::id() const { return m_id; }
