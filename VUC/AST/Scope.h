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

class Decl;
class Class;
class Type;

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
        evTypeParam,
        evType,
    };

  protected:
    enum Kind m_kind;
    std::string m_name;
    Decl *m_decl; /*? Are all of these decls? All decls have types? */

  public:
    explicit Sym(std::string name, Decl *decl, Sym::Kind symKind)
        : m_name(name), m_kind(symKind), m_decl(decl)
    {
    }

    std::string name() const { return m_name; }
    Class *cls();
    Decl *decl() { return m_decl; }
    virtual Type *type();

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
    /* function/meth or lambda argument */
    bool isArg() { return m_kind == evArg; }
    /* type parameter to class */
    bool isTypeParam() { return m_kind == evTypeParam; }
    /* type entry */
    bool isType() { return m_kind == evType; }
};

class InternalTypeSym : public Sym
{
    Type *m_type;

  public:
    InternalTypeSym(std::string name, Decl *decl, Type *type)
        : Sym(name, decl, evType), m_type(type)
    {
    }

    Type *type() override { return m_type; }
};

class Scope
{
  protected:
    Scope *m_super;
    std::vector<Scope *> m_subScopes;
    std::vector<Sym *> m_syms;

  public:
    Scope(Scope *super = nullptr) : m_super(super) {}

    Scope *superScope() { return m_super; }

    void addSubScope(Scope *sub);
    void reg(Sym *sym);
    Sym *find(std::string name);
    Type *findType(std::string type);
};
