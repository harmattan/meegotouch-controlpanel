/***************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <QtDebug>
#include <QDateTime>

#include "dcpperflogger.h"

#ifdef PERF_MEASUREMENT
static DcpPerfLogger g_dcpPerfLoggerInstance;

DcpPerfLogger::DcpPerfLogger() : m_logFd(-1)
{
}

DcpPerfLogger::~DcpPerfLogger()
{
    if (m_logFd >= 0) {
        qWarning() << "XXX close";
        int st = close(m_logFd);
        if (st < 0) {
            qCritical() << "close error in performance log" << errno;
        }
    }
}

DcpPerfLogger &DcpPerfLogger::instance()
{
    return g_dcpPerfLoggerInstance;
}

void DcpPerfLogger::startLogging(const QString &filename)
{
    m_logFd = open(filename.toAscii().data(), 
                   O_WRONLY | O_CREAT | O_APPEND, 
                   S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (m_logFd < 0) {
        qCritical() << "could not open" << filename << errno;
    }
}

void DcpPerfLogger::recordEvent(const QString &event)
{
    if (m_logFd < 0) {
        return;
    }

    static char buf[1024];
    qint64 msecs = QDateTime::currentDateTime().toMSecsSinceEpoch();
    int len = snprintf(buf, sizeof(buf), "%lld %s %d\n", 
                       msecs, event.toUtf8().data(), getpid()); 
    int writeSt = 0;
    if (len >= (int)sizeof(buf)) {
        qWarning() << "message truncated in performance log:" << msecs << event;
        buf[sizeof(buf)-2] = '\n'; // enforce a newline at the end
        writeSt = write(m_logFd, buf, sizeof(buf) - 1);
    } else {
        writeSt = write(m_logFd, buf, len);
    }
    if (writeSt < 0) {
        qCritical() << "write error in performance log:" << errno;
    }
}

#endif // PERF_MEASUREMENT
