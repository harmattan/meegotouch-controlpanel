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

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include <syslog.h>

/******************************************************************************
 * The first part of the header can be loaded and loaded again, so we can turn
 * on and off the debug facility for each source file.
 */

/*
 * Use these lines to disable the debug (or warning) messages in the entire 
 * source tree.
 */
//#undef DEBUG
//#undef WARNING

/*
 * Or use these lines to turn on all the debug (or warning) messages.
 */
//#define DEBUG
#define WARNING

/*
 * If the debug facility is enabled we also enable all the warning messages.
 */
#if defined(DEBUG) && !defined(WARNING)
#  define WARNING
#endif

#if defined(WARNING) && !defined(CRITICAL)
#  define CRITICAL
#endif

/*
 * The DCP_DEBUG macro is used to print normal debug messages.
 */
#undef DCP_DEBUG
#ifdef DEBUG
#  define DCP_DEBUG(...) DcpDebug::dcpPrintMsg (\
        QtDebugMsg, \
        __PRETTY_FUNCTION__, \
        __VA_ARGS__)
#else
#  define DCP_DEBUG(...) { /* Nothing... */ }
#endif

/*
 * The DCP_WARNING is used to print warning messages.
 */
#undef DCP_WARNING
#ifdef WARNING
#  define DCP_WARNING(...) DcpDebug::dcpPrintMsg (\
        QtWarningMsg, \
        __PRETTY_FUNCTION__, \
        __VA_ARGS__)
#else
#  define DCP_WARNING(...) { /* Nothing... */ }
#endif

/*
 * The DCP_CRITICAL is used to print warning messages.
 */
#undef DCP_CRITICAL
#ifdef CRITICAL
#  define DCP_CRITICAL(...) DcpDebug::dcpPrintMsg (\
        QtCriticalMsg, \
        __PRETTY_FUNCTION__, \
        __VA_ARGS__)
#else
#  define DCP_CRITICAL(...) { /* Nothing... */ }
#endif

/******************************************************************************
 * Here we have those parts that can be loaded only once, so we protect them
 * with DCPDEBUG_H. 
 */
#ifndef DCPDEBUG_H
#define DCPDEBUG_H

#include <QtDebug>

#define DCP_STR(qstring) qstring.toLatin1().constData()

namespace DcpDebug
{
    /*! \brief Prints out a message with the current time. */
    void time(const QString& msg = "");

    /*! \brief Marks the start of msg.
     * Can be used with DcpDebug::end to easily debug how long time
     * it took between start and end. */
    void start(const QString& msg = "");

    /*! \brief Marks the end of msg.
     * \details DcpDebug::start marks the start, it can be used
     * to easily debug how long time it took between start and end. */
    void end(const QString& msg = "");

    /*! \brief message handler for qDebug
     * \details this function can be installed as a message handler for
     * for debugging with Qt way, using qDebug() */
    void dcpMsg(QtMsgType type, const char *msg);

    void dcpPrintMsg (
        QtMsgType     type,
        const char   *function,
        const char   *formatstring,
        ...);
};

/*! \brief convenience macros for debugging how long time a function takes.
 * \details The start and the end of the function should be marked with it. */
#define DCP_FUNC_START DcpDebug::start(Q_FUNC_INFO);
#define DCP_FUNC_END DcpDebug::end(Q_FUNC_INFO);

/* In debug mode this macro is a synonym for assert,
 * otherwise just outputs a waring message (as we are expected not to assert
 * in a release build */
#ifdef DEBUG

#define dcp_failfunc_unless(x, return_value...) \
    Q_ASSERT (x)

#else // DEBUG

#define dcp_failfunc_unless(x, return_value...) \
    if (!(x)) { \
        syslog (LOG_WARNING, #x " is false at %s", Q_FUNC_INFO); \
        return return_value; \
    }

#endif // DEBUG

#endif // DCPDEBUG_H

