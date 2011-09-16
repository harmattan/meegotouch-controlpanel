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

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#ifndef DCPAPPLETBUTTONS_H
#define DCPAPPLETBUTTONS_H

#include "dcpmaincategory.h"

class DcpAppletMetadata;
class QStandardItemModel;
class Category;
class DcpPage;
class DcpAppletObject;
class MLabel;

class DcpAppletButtons :
    public DcpMainCategory
{
    Q_OBJECT
    Q_PROPERTY (QString mattiID READ mattiID WRITE setMattiID)
    Q_PROPERTY (QString TDriverID READ TDriverID WRITE setTDriverID)

public:
    DcpAppletButtons (
            const Category  *categoryInfo,
            QGraphicsWidget *parent = 0,
            DcpPage* ownerPage = 0);
    ~DcpAppletButtons ();

    void setCategoryInfo (const Category *categoryInfo);
    const Category* categoryInfo () const { return m_CategoryInfo; }

    virtual bool reload();
    int metadataCount () const;
    DcpAppletMetadata* appletMetadata (int pos);

    QString mattiID() const;
    void setMattiID(const QString &mattiID);
    QString TDriverID() const;
    void setTDriverID(const QString &tdriverID);

signals:
    //! emitted after loading the applets has finished
    void loadingFinished();

protected:
    virtual void retranslateUi();
    virtual void createContents();
    void addComponent (DcpAppletMetadata *metadata, QStandardItemModel* model,
                       const QStringList& mainApplets = QStringList());

private:
    void markAllInactive();

    QGraphicsWidget* createSlider (DcpAppletObject* applet,
                                   DcpAppletMetadata* metadata);
    QGraphicsWidget* createSpecial (DcpAppletObject* applet);
    QGraphicsWidget* createButton (DcpAppletObject* applet,
                                   DcpAppletMetadata* metadata);
    QGraphicsWidget* createDefault (DcpAppletObject* applet,
                                    DcpAppletMetadata* metadata);
    inline QString genTDriverID (const char* prefix,
                                 DcpAppletMetadata* metadata);

    const Category *m_CategoryInfo;
    friend class Ut_DcpAppletButtons;

    class MList* m_List;
    QString m_TDriverID;
    DcpPage* m_Page; // the page the widget is on, or 0 if unknown
    MLabel* m_SubHeader;
    bool m_HasButton;
};

#endif

