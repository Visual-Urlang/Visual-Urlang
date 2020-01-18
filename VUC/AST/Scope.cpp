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

#include <iostream>

#include "Decl.h"
#include "Scope.h"
#include "Scoped.h"

void Scoped::initScope(Scope *super)
{
    m_scope = new Scope(super);
    if (super)
        super->addSubScope(this->m_scope);
}

void Scoped::regClass(Class *decl) { std::cout << "unhandled regClass\n"; }

void Scoped::regDim(DimDecl *decl) { std::cout << "unhandled regDim\n"; }

void Scoped::regFun(FunDecl *fun)
{
    Sym *fSym = new Sym(fun->name(), fun, Sym::Kind::evFun);
    m_scope->reg(fSym);
}

void Scoped::regArg(ParamDecl *param)
{
    Sym *pSym = new Sym(param->name(), param, Sym::Kind::evArg);
    m_scope->reg(pSym);
}

void Scope::addSubScope(Scope *sub) { m_subScopes.push_back(sub); }

void Scope::reg(Sym *sym) { m_syms.push_back(sym); }

Sym *Scope::find(std::string name)
{
    for (auto sym : m_syms)
        if (sym->name() == name)
            return sym;
    return nullptr;
}
