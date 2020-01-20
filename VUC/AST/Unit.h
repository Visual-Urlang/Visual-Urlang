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

#include <string>

#include "Decl.h"
#include "Scoped.h"
#include "Stmt.h"

class CompoundStmt;

/* A unit is a collection of classes and other decls.
 * Essentially it is a whole program, plus other things.
 */
class Unit : public Decl, public Scoped
{
  protected:
    std::string m_name;
    CompoundStmt *m_body;

  public:
    Unit(std::string name, CompoundStmt *body)
        : Decl(Position(0, 0, 0, 0, 0, 0)), m_name(name), m_body(body)
    {
    }

    virtual void print(size_t indent);

    /* analysis */
    /* stage 1 */
    void genSymTabs();
    /* stage 2 */
    virtual void resolveInheritance(Scoped *superNode);

    void regClass(Class *decl) override;
};
