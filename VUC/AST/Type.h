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

class Type
{
};

/* A basic type such as Integer, Short, etc.
 * Strings etc are actually resolved to the real type of e.g. String class. */
class BuiltinType : public Type
{
};
