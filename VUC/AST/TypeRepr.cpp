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
    /* unused? */
    m_type = m_repr->resolveInScope(aScope);
}

void TypeLoc::typeCheck(Scope *aScope)
{
    m_type = m_repr ? m_repr->realise(aScope) : new BuiltinType();
}

void TypeLoc::print(size_t indent)
{
    std::cout << blanks(indent) << "(TypeLoc\n";
    if (m_repr)
    {
        std::cout << blanks(indent) << "(REPR: ";
        m_repr->print(indent + 2);
        std::cout << blanks(indent) << ")\n";
    }
    else
        std::cout << "<empty-typeloc>";
    if (m_type)
    {
        std::cout << blanks(indent);
        m_type->print(indent + 2);
        std::cout << "\n";
    }
    std::cout << blanks(indent) << ")";
}

Type *TypeRepr::resolveInScope(Scope *aScope)
{
    std::cout << "Unimplemented TypeRepr::resolveInScope in class "
              << typeid(*this).name() << "\n";
    return nullptr;
}

Type *BuiltinTypeRepr::realise(Scope *superNode) { return new BuiltinType; }
Type *BuiltinTypeRepr::resolveInScope(Scope *superNode)
{
    return realise(superNode);
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
    Scope *tempScope = new Scope(aScope);
    Type *base = nullptr;
    Sym *aSym = aScope->find(m_base);

    if (!aSym)
    {
        std::cout << "unresolved typerepr: " << m_base << "\n";
        return nullptr;
    }

    if (aSym->isCls())
    {
        base = new ClassInstType(dynamic_cast<Class *>(aSym->decl()), {});
    }
    else if (aSym->isTypeParam())
        base = new UnboundTypeArg(m_base, aSym->decl());
    else
    {
        std::cout << "unresolved id type: " << aSym->name() << "\n";
        return nullptr;
    }

    if (!m_args.empty())
    {
        if (auto *bCls = dynamic_cast<ClassInstType *>(base))
        {
            for (auto p : bCls->cls()->params())
                tempScope->reg(new Sym(p->name(), p, Sym::evTypeParam));

            for (size_t i = 0; i < m_args.size(); i++)
            {
                auto p = m_args[i];
                auto arg = TypeParamBinding(bCls->cls()->paramAt(i)->name(),
                                            p->resolveInScope(tempScope),
                                            bCls->cls()->paramAt(i));
                bCls->addArg(arg);
            }

            /* Next step is to set up the supers. Of course we have to make
             * sure that we don't leave our own type params in scope; they
             * have their own. */

            /* My suggestion: We lookup the base name of each inherited one
             * and call on them Class to construct theirs, passing the
             * TypeReprs of the argument list.
             */

            for (auto inh : bCls->cls()->inherits())
                bCls->addInherited(inh->repr()->resolveInScope(tempScope));

            return bCls;
        }
        else
        {
            /* NOTE! Have to allow for unbound type args to be specialised.
             */
            std::cout << "Base is not a class, cannot specialize.";
        }
    }
    return base;
}

Type *GenericTypeInstRepr::realise(Scope *aScope)
{
    Type *base = aScope->findType(m_base);
    std::vector<Type *> args;

    for (auto a : m_args)
        args.push_back(a->realise(aScope));

    if (auto ci = dynamic_cast<ClassInstType *>(base))
        return !ci->isInvoked() ? ci->invoke(args) : ci;
    else if (args.empty())
        return base; /* builtin case */

    std::cout << "failure in realisation of generic\n";
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
