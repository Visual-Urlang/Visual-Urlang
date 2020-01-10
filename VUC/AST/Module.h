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

class CompoundStmt;

class Module : public Decl
{
  protected:
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
};

class Class : public Module
{
  public:
    Class(Position pos, std::string name, CompoundStmt *body)
        : Module(pos, evClass, name, body)
    {
    }

    virtual void print(size_t indent);
};
