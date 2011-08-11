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

#ifndef CATEGORY_H
#define CATEGORY_H

#include <QStringList>

/*!
 * A class that describes an applet category that should appear inside the
 * control panel. It is read from an ini file.
 */
class Category
{
public:
    Category();
    virtual ~Category();

    QString parentId () const;

    QString titleId () const;
    QString subtitleId () const;
    QString name () const;
    QString title () const;
    QString subtitle () const;
    QStringList translationCategories () const;

    QString iconId () const;
    int order () const;

    QStringList referenceIds () const;

    bool idMatch (const QString& id) const;

    virtual bool isValid () const;
    void addChild (const Category* child);
    QList<const Category*> children () const;

    bool containsUncategorized () const;
    static bool orderLessThan (const Category* cat1, const Category* cat2);

    virtual bool hasMostUsed () const { return false; }

    enum SortType {
        SortByOrder,
        SortByTitle
    };
    SortType appletSort () const;

    enum ComponentOrderType {
        CategoriesFirst,
        AppletsFirst
    };
    ComponentOrderType componentOrder () const;

    bool appletAutoStart () const;

    QString helpId () const;

    QString titleStyle () const;

    bool hasSeparatorLine () const;

    QString subHeaderText () const;
    QString subHeaderTextLogicalId () const;

    QStringList mainApplets () const;

    bool hideIfEmpty () const;

protected:
    static const char* componentOrderToString (ComponentOrderType order);

    virtual QString value (int key) const = 0;
    QStringList valueList (int key) const;

    enum {
        ParentId,
        NameId,
        NameLogicalId,
        ValueId,
        ValueLogicalId,
        IconId,
        AliasesId,
        TranslationId,
        OrderId,
        ComponentOrderId,
        AppletSortId,
        AppletAutoStartId,
        HelpId,
        TitleStyleId,
        HasSeparatorLineId,
        SubHeaderTextId,
        SubHeaderTextLogicalId,
        MainAppletsId,
        HideIfEmptyId,
        KeyIdMax
    };

private:
    QList<const Category*> m_Children;
    bool m_IsChildComputed;
};

// a logical category:
#define MostUsed "Recently used"
#define MostUsedId "qtn_sett_main_most"

#endif // CATEGORY_H

