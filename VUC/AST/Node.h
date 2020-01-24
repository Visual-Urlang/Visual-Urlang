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

#include <iostream>

#include "AST.h"
#include "Position.h"
#include "Scoped.h"

class Scope;

class Node
{
  protected:
    Position m_pos;

  public:
    virtual ~Node() = default;
    explicit Node(Position pos) : m_pos(pos) {}

    Position pos() const;

    virtual void print(size_t indent);

    /* analysis */
    /* first step: generate symtabs */
    virtual void genSymTabs(Scoped *superNode, Scope *superScope) {}
    /* second step: resolve implements/inherits */
    virtual void resolveInheritance(Scoped *superNode)
    {
        std::cout << "unresolved resolveInheritance in " << typeid(*this).name()
                  << "\n";
    }
    virtual Node *typeCheck(Scoped *superNode)
    {
        std::cout << "unresolved typeCheck in " << typeid(*this).name() << "\n";
        return this;
    }
};

inline Position Node::pos() const { return m_pos; }