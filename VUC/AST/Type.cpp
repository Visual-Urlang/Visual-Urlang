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

void UnboundTypeArg::print()
{
    std::cout << "(unbound-type-arg: " << m_name << ")";
}

void ClassInstType::print()
{
    std::cout << "(class-inst: " << m_class->name();

    if (!m_params.empty())
    {
        std::cout << "\n\tbindings: \n";
        for (auto p : m_params)
        {
            std::cout << "\tnam: " << p.name << ", type: ";
            p.type->print();
            std::cout << "\n";
        }
    }

    if (!m_inherits.empty())
    {
        std::cout << "\n\tinherits: (";
        for (auto p : m_inherits)
        {
            p->print();
            std::cout << "\n";
        }
        std::cout << ")";
    }
    std::cout << ")\n";
}
