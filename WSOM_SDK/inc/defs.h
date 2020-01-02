/*******************************************************************

        PROPRIETARY NOTICE

These coded instructions, statements, and computer programs contain
proprietary information of the Visual Urlang project, and are protected
under copyright law. They may not be distributed, copied, or used except
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

// The following ifdef block is the standard way of creating macros which make
// exporting
// from a DLL simpler. All files within this DLL are compiled with the
// WSOM_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any
// project
// that uses this DLL. This way any other project whose source files include
// this file see
// WSOM_API functions as being imported from a DLL, whereas this DLL sees
// symbols
// defined with this macro as being exported.
#ifdef WSOM_EXPORTS
#define WSOM_API __declspec(dllexport)
#else
#define WSOM_API __declspec(dllimport)
#endif

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
    WSLong iDate;
    WSLong iTime;
} WSDate;

typedef struct WSObject *WSObjectHdl;
typedef struct WSClass *WSClassHdl;

typedef const char *WSMethName;
typedef const char *WSTypeSig;

#ifdef __cplusplus
typedef void (*WSMethImpl)(...);
#else
typedef void (*WSMethImpl)();
#endif

/* Called obect, method name, and argument storage structure. */
typedef void (*WSCallForwarder)(WSObjectHdl, WSMethName, void *);

#endif