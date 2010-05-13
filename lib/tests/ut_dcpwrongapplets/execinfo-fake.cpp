/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#include <execinfo.h>
#include <stdlib.h>
#include <string.h>

static const char* fakeBacktraceSym[] = {
    "065 /manni/usr/lib/duicontrolpanel/applets/libss.so.4"
    "(_ZN12QApplication15x11ProcessEventEP7_XEvent+0x1311) [0xf69ec481]",
    "065 /usr/lib/libQtGui.so.4(_ZN12QApplication15x"
    "11ProcessEventEP7_XEvent+0x1311) [0xf69ec481]"
};


int backtrace(void **, int)
{
    return 2;
}

char **backtrace_symbols(void *const *, int)
{
    char** result = (char**)malloc(2*sizeof(char*));
    result[0] = strdup (fakeBacktraceSym[0]);
    result[1] = strdup (fakeBacktraceSym[1]);
    return result;
}

