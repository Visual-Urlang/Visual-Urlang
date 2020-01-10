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

#include <string>

#include "Node.h"

class Constant : public Node
{
  protected:
    enum ConstantType
    {
        evInt,
        evString,
    } m_constType;

    int m_intValue;
    std::string m_strValue;

  public:
    Constant(Position pos, int intValue)
        : Node(pos), m_intValue(intValue), m_constType(evInt)
    {
    }

    Constant(Position pos, std::string strValue)
        : Node(pos), m_strValue(strValue), m_constType(evInt)
    {
    }
};
