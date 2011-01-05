/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef STREAM_H
#define STREAM_H

class QTextStream;
class QIODevice;
#include <QObject>

class Stream: public QObject
{
    Q_OBJECT

public:
    Stream (QObject* parent);
    ~Stream ();

    void setIODevice (QIODevice* device);
    void flush ();
    void writeLine (const QString& st);

signals:
    void newCommand (const QString& command);

protected slots:
    void onReadyRead ();

private:
    QTextStream* m_Text;
};


#endif // STREAM_H

