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

#include <vector>

class Class;

class Type
{
  public:
    virtual void print() { std::cout << "unknown type"; }
};

/* A basic type such as Integer, Short, etc.
 * Strings etc are actually resolved to the real type of e.g. String class. */
class BuiltinType : public Type
{
};

class UnboundTypeArg : public Type
{
  public:
    std::string m_name;

    explicit UnboundTypeArg(std::string name) : m_name(name) {}

    virtual void print();
};

struct TypeParamBinding
{
    std::string name;
    Type *type;

    TypeParamBinding(std::string name, Type *type) : name(name), type(type) {}
};

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

    virtual void print();
};