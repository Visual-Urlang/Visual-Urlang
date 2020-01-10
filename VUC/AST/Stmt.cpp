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

#include "AST/Stmt.h"

void CompoundStmt::print(size_t indent)
{
    std::cout << blanks(indent) << "[CompoundStmt: \n";
    for (auto c : m_code)
    {
        c->print(indent + 2);
        std::cout << "\n";
    }
    std::cout << blanks(indent) << "]";
}
