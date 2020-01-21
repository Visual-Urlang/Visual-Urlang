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

#include "AST/Module.h"
#include "AST/Stmt.h"
#include "AST/Unit.h"
#include "Scope.h"

void Unit::print(size_t indent)
{
    std::cout << blanks(indent) << "[unit: " << m_name << "\ncontents: \n";
    for (auto m : m_body->getCode())
    {
        m->print(indent + 2);
        std::cout << "\n";
    }

    std::cout << blanks(indent) << "]\n";
}

void Unit::genSymTabs()
{
    initScope();
    for (auto d : m_body->getCode())
        d->genSymTabs(this, m_scope);
}

void Unit::resolveInheritance(Scoped *superNode)
{
    for (auto d : m_body->getCode())
        d->resolveInheritance(this);
}

void Unit::regClass(Class *decl)
{
    Sym *sym = new Sym(decl->name(), decl, Sym::Kind::evCls);
    m_scope->reg(sym);
    printf("registed class %s\n", decl->name().c_str());
}

std::string Module::name() const { return m_name; }

void Class::print(size_t indent)
{
    std::cout << blanks(indent) << "[class module: " << m_name << "\n"
              << blanks(indent) << "contents: \n";
    for (auto m : m_body->getCode())
    {
        m->print(indent + 2);
        std::cout << "\n";
    }

    std::cout << blanks(indent) << "]\n";
}

void Class::genSymTabs(Scoped *parent, Scope *superScope)
{
    initScope(superScope);
    parent->regClass(this);
    for (auto d : m_body->getCode())
        d->genSymTabs(this, m_scope);
    std::cout << "generated class scope for " << m_name << "\n";
}

void Class::resolveInheritance(Scoped *superNode)
{
    for (auto d : m_inherits)
        d->resolveInScope(m_scope);
}