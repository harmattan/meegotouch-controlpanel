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

#ifndef FT_DCPCOMPONENT_H
#define FT_DCPCOMPONENT_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpComponent class declaration
#include <dcpcomponent.h>

Q_DECLARE_METATYPE(DcpComponent*);

class DcpSingleComponent : public DcpComponent
{
    Q_OBJECT
public:
    explicit DcpSingleComponent(DcpComponent *category,
                                  const QString& title="",
                                  QGraphicsWidget *parent=0,
                                  const QString& logicalId="");
    virtual void add(DcpComponent *component); 
    virtual void remove(DcpComponent *component); 
protected:
    virtual void createContents(); 
};

class Ft_DcpComponent : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testSubPage();
    void testTitle();
    void testCategory();
    void testLogicalId();    

private:
    DcpComponent* m_subject;
    DcpComponent* m_Category;
    QString m_Title;
    QGraphicsWidget *m_Parent;
    QString m_LogicalId;
    
};

#endif
