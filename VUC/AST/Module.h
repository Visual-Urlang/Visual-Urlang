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

#include <memory>

#include "Decl.h"
#include "Scoped.h"

class CompoundStmt;

/* A Module is either a class or a collection of other things instead. */
class Module : public Decl, public Scoped
{
  protected:
    /* Is this module imported from elsewhere? If so we only care about it as
     * an interface. */
    bool m_isImported = false;
    std::string m_name;
    CompoundStmt *m_body;

  public:
    enum ModType
    {
        evMod,
        evClass,
    } m_modType;

    Module(Position pos, ModType modType, std::string name, CompoundStmt *body)
        : Decl(pos), m_modType(modType), m_name(name), m_body(body)
    {
    }

    std::string name() const;
};

class Class : public Module
{
    ClassInstType *m_prototype;
    /* Superclasses */
    std::vector<TypeLoc *> m_inherits;
    /* Interfaces implemented */
    std::vector<TypeLoc *> m_implements;
    /* Generic type parameters */
    std::vector<TypeParamDecl *> m_params;

  public:
    Class(Position pos, std::string name, std::vector<TypeLoc *> inherits,
          std::vector<TypeLoc *> implements,
          std::vector<TypeParamDecl *> params, CompoundStmt *body)
        : Module(pos, evClass, name, body), m_inherits(inherits),
          m_implements(implements), m_params(params)
    {
    }

    TypeParamDecl *paramAt(short i) { return m_params[i]; }
    std::vector<TypeLoc *> inherits() { return m_inherits; }
    std::vector<TypeLoc *> implements() const { return m_implements; }
    std::vector<TypeParamDecl *> params() const { return m_params; }

    virtual void print(size_t indent);
    virtual void genSymTabs(Scoped *superNode, Scope *superScope) override;
    virtual void resolveInheritance(Scoped *superNode);
    virtual Node *typeCheck(Scoped *superNode);
};
