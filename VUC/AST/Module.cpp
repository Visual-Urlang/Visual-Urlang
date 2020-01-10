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

#include "AST/Module.h"
#include "AST/Stmt.h"

void Class::print(size_t indent)
{
    std::cout << blanks(indent) << "[class module: " << m_name
              << "\ncontents: \n";
    for (auto m : m_body->getCode())
    {
        m->print(indent + 2);
        std::cout << "\n";
    }

    std::cout << "]\n";
}