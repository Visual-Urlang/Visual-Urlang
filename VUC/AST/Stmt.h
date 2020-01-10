/*******************************************************************

        PROPRIETARY NOTICE

These coded instructions, statements, and computer programs contain
proprietary information of the Visual Urlang project, and are protected
under copyright law. They may not be distributed, copied, or used except
under the provisions of the terms of the End-User License Agreement, in
the file "EULA.md", which should have been included with this file.

        Copyright Notice

    (c) 2019-2020 The Visual Urlang Project.
              All rights reserved.
********************************************************************/

#pragma once

#include <vector>

#include "Decl.h"
#include "Expr.h"

class Stmt : public Node
{
  public:
    explicit Stmt(Position pos) : Node(pos) {}
};

class CompoundStmt : public Stmt
{
    std::vector<Node *> m_code;

  public:
    CompoundStmt(Position pos, std::vector<Node *> nodes)
        : Stmt(pos), m_code(nodes)
    {
    }

    void addCode(Node *c) { m_code.push_back(c); }

    std::vector<Node *> &getCode() { return m_code; }

    virtual void print(size_t indent);
};

class ExprStmt : public Stmt
{
    Expr *m_expr;

  public:
    ExprStmt(Position pos, Expr *expr) : Stmt(pos), m_expr(expr) {}
};