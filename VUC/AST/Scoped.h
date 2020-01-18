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

class Scope;
class DimDecl;
class FunDecl;
class ParamDecl;
class Class;

/* All nodes in which a new scope is introduced inherit from this class. */
class Scoped
{
  protected:
    Scope *m_scope;

  public:
    Scoped() : m_scope(nullptr) {}

    void initScope(Scope *parent = nullptr);

    /* register a funarg */
    virtual void regArg(ParamDecl *param);
    virtual void regClass(Class *decl);
    virtual void regDim(DimDecl *decl);
    virtual void regFun(FunDecl *fun);
};
