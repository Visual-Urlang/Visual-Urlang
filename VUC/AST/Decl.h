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

#include "Node.h"
#include "TypeLoc.h"

class CompoundStmt;

class Decl : public Node
{
  public:
    explicit Decl(Position pos) : Node(pos) {}

    virtual Type *type() { return nullptr; }

    /* 2nd step analysis */
    virtual void resolveDeclTypes()
    {
        std::cout << "Unimplemented resolveDeclTypes";
    }
};

/* any decl with a name */
class NamedDecl : public Decl
{
  protected:
    std::string m_name;

  public:
    NamedDecl(Position pos, std::string name) : Decl(pos), m_name(name) {}

    std::string name() const { return m_name; }
};

class TypeParamDecl : public NamedDecl
{
  public:
    Type *m_type = nullptr;

    TypeParamDecl(Position pos, std::string name) : NamedDecl(pos, name) {}

    virtual Type *type() { return m_type; }

    void synthType(Scoped *ctx);
};

/* a variable declaration */
class DimDecl : public NamedDecl
{
  protected:
    TypeLoc m_typeLoc;

  public:
    DimDecl(Position pos, std::string name, TypeLoc typeLoc)
        : NamedDecl(pos, name), m_typeLoc(typeLoc)
    {
    }

    virtual void genSymTabs(Scoped *superNode, Scope *superScope) override;
    virtual DimDecl *typeCheck(Scoped *superNode) override;

    virtual TypeRepr *typeRepr();
    virtual Type *type();

    virtual void print(size_t indent);
};

class ParamDecl : public DimDecl
{
  public:
    ParamDecl(Position pos, std::string name, TypeLoc typeLoc)
        : DimDecl(pos, name, typeLoc)
    {
    }

    void genSymTabs(Scoped *superNode, Scope *superScope) override;
};

class FunDecl : public NamedDecl, public Scoped
{
    std::vector<ParamDecl *> m_formals;
    TypeLoc *m_rType;
    CompoundStmt *m_code;

  public:
    FunDecl(Position pos, std::string name, std::vector<ParamDecl *> paramDecls,
            TypeLoc *type, CompoundStmt *code)
        : NamedDecl(pos, name), m_formals(paramDecls), m_rType(type),
          m_code(code)
    {
    }

    void genSymTabs(Scoped *superNode, Scope *superScope) override;
    virtual void regDim(DimDecl *decl) override;

    TypeRepr *rTypeRepr() { return m_rType->repr(); }
    std::vector<TypeRepr *> argTypeReprs()
    {
        std::vector<TypeRepr *> reprs;
        for (auto f : m_formals)
            reprs.push_back(f->typeRepr());
        return reprs;
    }

    virtual FunDecl *typeCheck(Scoped *superNode) override;

    virtual void print(size_t indent) override;
};