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

#include "AST.h"

class Decl;
class TypeParamDecl;
class TypeParamBinding;
class Class;

class Type
{
  public:
    virtual void print(size_t in) { std::cout << blanks(in) << "unknown type"; }

    /* is this the right way? */
    virtual Type *copyWithSubs(std::vector<TypeParamBinding> subs)
    {
        std::cout << "unimplemented copyWithSubs() in " << typeid(*this).name()
                  << "\n";
        return nullptr;
    }
};

/* A basic type such as Integer, Short, etc.
 * Strings etc are actually resolved to the real type of e.g. String class. */
class BuiltinType : public Type
{
    virtual Type *copyWithSubs(std::vector<TypeParamBinding> subs);

    virtual void print(size_t in) { std::cout << "(builtin-type)"; }
};

/* To support HKTs, this should have an entry for its type parameters too.
 * Substitution then involves finding the Class defining the type name, and
 * then invoking it with any type args we have.
 */
class UnboundTypeArg : public Type
{
  public:
    std::string m_name;
    Decl *m_decl;

    explicit UnboundTypeArg(std::string name, Decl *decl)
        : m_name(name), m_decl(decl)
    {
    }

    virtual Type *copyWithSubs(std::vector<TypeParamBinding> subs);

    virtual void print(size_t in);
};

struct TypeParamBinding
{
    std::string name;
    Type *type;
    TypeParamDecl *m_decl;

    TypeParamBinding(std::string name, Type *type, TypeParamDecl *decl)
        : name(name), type(type), m_decl(decl)
    {
    }
};

/*struct FunType
{
    Type *rType;
    std::vector<Type *> argTypes;
};*/

/* Instantiated type*/
class ClassInstType : public Type
{
    std::vector<Type *> m_inherits;
    Class *m_class;
    /* Table of names to their concrete type replacements. Used to substitute
     * type parameter uses by Dims and methods of the class.*/
    std::vector<TypeParamBinding> m_params;

  public:
    ClassInstType(Class *class_, std::vector<TypeParamBinding> params)
        : m_class(class_), m_params(params)
    {
    }

    Class *cls() { return m_class; }

    void addArg(TypeParamBinding anArg) { m_params.push_back(anArg); }
    void addInherited(Type *inh) { m_inherits.push_back(inh); }

    /* Invoke this type with these arguments. */
    virtual Type *invoke(std::vector<Type *> subs);

    /* Copy type, substituting all instances of UnboundTypeArg that can be
     * subbed.*/
    virtual Type *copyWithSubs(std::vector<TypeParamBinding> subs) override;

    virtual void print(size_t in);
};