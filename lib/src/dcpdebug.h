/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

/******************************************************************************
 * The first part of the header can be loaded and loaded again, so we can turn
 * on and off the debug facility for each source file.
 */

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
		__func__, \
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
		__func__, \
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
		__func__, \
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
    void time(const QString& msg = "");
    void start(const QString& msg = "");
    void end(const QString& msg = "");
    void dcpMsg(QtMsgType type, const char *msg);

    void dcpPrintMsg (
		QtMsgType     type,
		const char   *function,
		const char   *formatstring,
		...);
};

#if 0
inline void DcpDebug::time(const QString& msg = "") {}
inline void DcpDebug::start(const QString& msg = "") {}
inline void DcpDebug::end(const QString& msg = "") {}

#else

#define DCP_FUNC_START DcpDebug::start(Q_FUNC_INFO);
#define DCP_FUNC_END DcpDebug::end(Q_FUNC_INFO);

#endif

#endif // DCPDEBUG_H
