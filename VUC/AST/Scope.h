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

#include <string>
#include <vector>

class Sym
{
  public:
    enum Kind
    {
        evCls,
        evIVar,
        evFun,
        evLocal,
        evArg,
    };

  protected:
    enum Kind m_kind;
    /* Decl * m_decl ? Are all of these decls? All decls have types? */
    std::string m_name;

  public:
    explicit Sym(std::string name, Sym::Kind symKind)
        : m_name(name), m_kind(symKind)
    {
    }

    std::string name() const { return m_name; }

    /* is a class */
    bool isCls() { return m_kind == evCls; }
    /* any class member */
    bool isClsMem() { return isIVar() | isFun(); }

    /* class instance variable */
    bool isIVar() { return m_kind == evIVar; }
    /* meth/fun */
    bool isFun() { return m_kind == evFun; }
    /* local variable of function/meth or lambda scope */
    bool isLocal() { return m_kind == evLocal; }
    /* function or method argument */
    bool isArg() { return m_kind == evArg; }
};

class Scope
{
  protected:
    Scope *m_super;
    std::vector<Scope *> m_subScopes;
    std::vector<Sym *> m_syms;

  public:
    Scope(Scope *super = nullptr) : m_super(super) {}

    void addSubScope(Scope *sub);
    void reg(Sym *sym);
    Sym *find(std::string name);
};
