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

#ifndef WSOM_OBJ_H
#define WSOM_OBJ_H

#include "defs.h"

/* WSObject, WSClass, WSMethod, and WSProperty are all real WSOM objects. */

struct WSObject
{
    WSClassHdl cls;
};

struct WSClass
{
    /* pointer to class of class: ClassClass */
    WSClassHdl hdlCls;
    /* pointer to superClass */
    WSClassHdl hdlSuper;
    /* name of the class */
    const char *szNam;
    /* pointer to std::vector<WSMethod *> */
    void *pvecMethVec;
    void *pvecPropVec;
    /* size of an instance */
    WSInteger sSize;
};

struct WSMethod
{
    WSClassHdl hdlCls;
    WSTypeSig szType;
    const char *szName;
};

struct WSProperty
{
    WSClassHdl hdlCls;
    WSTypeSig szType;
    const char *szName;
};

/* A WSCallArgs instance */
struct WSCallArgs
{
    WSClassHdl hdlCls;
};

/* Returns the method implementation for some method. */
WSMethImpl wsGetMethod(WSObjectHdl hOn, WSMethName szMeth,
                       WSCallForwarder *fnForwarder);

#endif