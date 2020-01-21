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
    virtual void print() { std::cout << "unknown type"; }
};

/* A basic type such as Integer, Short, etc.
 * Strings etc are actually resolved to the real type of e.g. String class. */
class BuiltinType : public Type
{
};

/* Instantiated type*/
class ClassInstType : public Type
{
    Class *m_class;
    std::vector<Type *> m_params;

  public:
    ClassInstType(Class *class_, std::vector<Type *> params)
        : m_class(class_), m_params(params)
    {
    }

    void addArg(Type *anArg) { m_params.push_back(anArg); }
};