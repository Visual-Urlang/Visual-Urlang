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

#include "Module.h"
#include "Type.h"

Type *BuiltinType::copyWithSubs(std::vector<TypeParamBinding> subs)
{
    return this;
}

Type *UnboundTypeArg::copyWithSubs(std::vector<TypeParamBinding> subs)
{
    for (auto t : subs)
    {
        printf("[[%s]]\n", t.name.c_str());
        if (t.name == m_name)
        {
            Type *cand = t.type;
            if (m_isCls)
                cand->makeClassType();
            return cand;
        }
    }
    std::cout << "could not resolve myself " << m_name << "\n";
    return nullptr;
}

void UnboundTypeArg::print(size_t in)
{
    std::cout << blanks(in) << "(unbound-type-arg: " << m_name << ")";
}

ClassInstType *ClassInstType::copyWithSubs(std::vector<TypeParamBinding> subs)
{
    ClassInstType *newTy;
    std::vector<Type *> newInherits = m_inherits;
    std::vector<TypeParamBinding> changes = m_params;

    for (int i = 0; i < changes.size(); i++)
        changes[i].type = changes[i].type->copyWithSubs(subs);
    for (auto &i : newInherits)
        i = i->copyWithSubs(subs);

    newTy = new ClassInstType(m_class, changes);
    newTy->m_inherits = newInherits;
    return newTy;
}

ClassInstType *ClassInstType::copyAsClass()
{
    ClassInstType *newTy;
    auto newInherits = m_inherits;

    for (auto &i : newInherits)
        i = i->copyAsClass();

    newTy = new ClassInstType(m_class, m_params);
    newTy->m_inherits = newInherits;
    newTy->makeClassType();
    return newTy;
}

void ClassInstType::makeClassType()
{
    m_isCls = true;
    for (auto i : m_inherits)
        i->makeClassType();
}

ClassInstType *ClassInstType::invoke(std::vector<Type *> subs)
{
    ClassInstType *newTy;
    std::vector<Type *> newInherits = m_inherits;
    std::vector<TypeParamBinding> changes = m_params;

    for (int i = 0; i < changes.size(); i++)
        changes[i].type = subs[i];
    for (auto &i : newInherits)
        i = i->copyWithSubs(changes);

    newTy = new ClassInstType(m_class, changes);
    if (m_isCls)
        newTy->makeClassType();
    newTy->m_inherits = newInherits;
    return newTy;
}

void ClassInstType::print(size_t in)
{
    std::cout << blanks(in) << "(" << (m_isCls ? "+" : "-")
              << "class-inst: " << m_class->name() << "\n";

    if (!m_params.empty())
    {
        std::cout << blanks(in) << "bindings: \n";
        for (auto p : m_params)
        {
            std::cout << blanks(in) << "nam: " << p.name << ", type: \n";
            p.type->print(in + 2);
            std::cout << "\n";
        }
    }

    if (!m_inherits.empty())
    {
        std::cout << blanks(in) << "inherits: (";
        for (auto p : m_inherits)
        {
            p->print(in + 2);
            std::cout << "\n";
        }
        std::cout << blanks(in) << ")\n";
    }
    std::cout << blanks(in) << ")\n";
}
