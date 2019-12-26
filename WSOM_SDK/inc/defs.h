/*******************************************************************

        LICENSE NOTICE

These coded instructions, statements, and computer programs contain
information of the Visual Urlang project, and are protected under
copyright law. They may not be distributed, copied, or used except
under the provisions of the terms of the Common Development and
Distribution License, in the file "COPYING.md", which should have
been included with this file.

        Copyright Notice

    (c) 2019 The Visual Urlang Project.
              All rights reserved.
********************************************************************/

#ifndef WSOM_DEFS_H
#define WSOM_DEFS_H

#include <stdint.h>

#define WSFALSE 0
#define WSTRUE 1

typedef short WSByte;
typedef char WSBoolean;
typedef short WSInteger;
typedef int32_t WSLong;
typedef int64_t WSLongLong;
typedef uintptr_t WSWord;
typedef float WSSingle;
typedef double WSDouble;
typedef WSLong WSCharacter;

typedef struct WSDate
{
    WSLong date;
    WSLong time;
} WSDate;

typedef struct WSObject *WSObjectHdl;
typedef struct WSClass *WSClassHdl;

typedef const char *WSTypeSig;

#endif