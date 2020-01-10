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

class Expr : public Node
{
  public:
    explicit Expr(Position pos) : Node(pos) {}
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