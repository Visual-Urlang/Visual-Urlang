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

#include "Expr.h"
#include <string>

class IdentExpr : public Expr
{
    const std::string m_id;

  public:
    std::string id() const;

    explicit IdentExpr(Position _pos, std::string id) : Expr(_pos), m_id(id) {}
};

inline std::string IdentExpr::id() const { return m_id; }
