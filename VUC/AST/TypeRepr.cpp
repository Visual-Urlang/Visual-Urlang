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
#include "Scope.h"
#include "TypeLoc.h"
#include "TypeRepr.h"

void TypeLoc::resolveInScope(Scope *aScope)
{
    m_type = m_repr->resolveInScope(aScope);
}

void TypeLoc::print(size_t indent)
{
    if (m_repr)
        m_repr->print(indent);
    else
        std::cout << "<empty-typeloc>";
}

Type *TypeRepr::resolveInScope(Scope *aScope)
{
    std::cout << "Unimplemented TypeRepr::resolveInScope in class "
              << typeid(*this).name() << "\n";
    return nullptr;
}

void BuiltinTypeRepr::print(size_t indent)
{
    std::cout << "(Builtin-type: " << m_builtinKind << ")";
}

/*Type *IdTypeRepr::resolveInScope(Scope *aScope)
{

}

void IdTypeRepr::print(size_t indent)
{
    std::cout << "(id-type: " << m_id << ")";
}*/

void DotTypeRepr::print(size_t indent)
{
    std::cout << "(dot-type: (";
    m_base->print(indent);
    std::cout << ").";
    m_member->print(indent);
    std::cout << ")";
}

Type *GenericTypeInstRepr::resolveInScope(Scope *aScope)
{
    Type *base = nullptr;
    Sym *aSym = aScope->find(m_base);

    if (!aSym)
    {
        std::cout << "unresolved typerepr: " << m_base << "\n";
        return nullptr;
    }

    if (aSym->isCls())
        base = new ClassInstType(dynamic_cast<Class *>(aSym->decl()), {});
    if (aSym->isTypeParam())
        base = new UnboundTypeArg(m_base);
    else
    {
        std::cout << "unresolved idtype: " << aSym->name() << "\n";
        return nullptr;
    }

    if (ClassInstType *bCls = dynamic_cast<ClassInstType *>(base))
    {
        for (short i = 0; i < m_args.size(); i++)
        {
            auto p = m_args[i];
            auto arg = TypeParamBinding(bCls->cls()->paramAt(i)->name(),
                                        p->resolveInScope(aScope));
            bCls->addArg(arg);
        }

        /* Next step is to set up the supers. Of course we have to make sure
         * that we don't leave our own type params in scope; they have their
         * own. */

        /* My suggestion: We lookup the base name of each inherited one and call
         * on them Class to construct theirs, passing the TypeReprs of the
         * argument list.
         */

        return bCls;
    }
    else
    {
        std::cout << "error: Base is not a class.";
    }
    return nullptr;
}

void GenericTypeInstRepr::print(size_t indent)
{
    std::cout << "(gen-inst-type: " << m_base << " ";
    std::cout << "(";
    for (const auto &ty : m_args)
    {
        ty->print(indent);
        std::cout << ", ";
    }
    std::cout << ")";
}
