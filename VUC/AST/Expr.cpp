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

#include "AST/Expr.h"

void FunCallExpr::print(size_t indent)
{
    std::cout << blanks(indent) << "[Funcall: ";
    m_func->print(0);

    std::cout << " args: \n";

    for (auto a : m_args)
    {
        std::cout << blanks(indent) << "arg: \n";
        a->print(indent + 2);
        std::cout << "\n";
    }

    std::cout << "\n" << blanks(indent) << "]";
}