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

class CompoundStmt;

/* A unit is a collection of classes and other decls.
 * Essentially it is a whole program, plus other things.
 */
class Scope
{
  protected:
    Scope *m_super;
    std::vector<Scope *> m_subScopes;

  public:
    Scope(Scope *super = nullptr);
};
