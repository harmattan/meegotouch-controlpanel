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

#include "category.h"

#include <QSet>

Category::Category():
    m_IsChildComputed (false)
{
}

Category::~Category ()
{
}

QStringList Category::valueList (int key) const
{
    return value (key).split(QChar(','));
}

QString Category::parentId() const
{
    return value (ParentId);
}

QString Category::titleId() const
{
    return value (NameLogicalId);
}

QString Category::subtitleId() const
{
    return value (ValueLogicalId);
}

QString Category::name () const
{
    return value (NameId);
}

QStringList Category::translationCategories () const
{
    return valueList (TranslationId);
}

QString Category::title() const
{
    QString id = titleId();
    QString translated = qtTrId(qPrintable(id));

    if (translated == id)
        return "!! " + name ();
    else
        return translated;
}

QString Category::subtitle() const
{
    QString id = subtitleId();
    if (id.isEmpty()) return id;
    QString translated = qtTrId(qPrintable(id));

    if (translated == id) {
        return "!! " + value (ValueId);
    } else {
        return translated;
    }
}

QString Category::iconId() const
{
    return value (IconId);
}

QString Category::helpId () const
{
    return value (HelpId);
}

QString Category::titleStyle () const
{
    return value (TitleStyleId);
}

QStringList Category::referenceIds() const
{
    QStringList result = valueList (AliasesId);
    result.prepend (name());
    result.prepend (titleId());
    return result;
}

bool Category::idMatch(const QString& id) const
{
    foreach (QString refId, referenceIds()) {
        if (refId == id) return true;
    }
    return false;
}

bool Category::isValid() const
{
    return !name().isEmpty();
}


void Category::addChild(const Category* child)
{
    m_Children.append (child);
}

QList<const Category*> Category::children() const
{
    // this is the last step computing the children:
    if (!m_IsChildComputed) {
        Category* self = const_cast<Category*>(this);
        self->m_IsChildComputed = true;

        // make the list uniq:
        self->m_Children = m_Children.toSet().toList();

        // sort by order:
        qSort (self->m_Children.begin(), self->m_Children.end(), orderLessThan);
    }

    return m_Children;
}

/*! \brief Specifies in which order the applets in the category should be sorted.
 *
 * Default is SortByOrder, in which case the applets will be sorted by what
 * "Order" they specify in their .desktop files.
 * If SortByTitle, then applets should be sorted by their translated title.
 */
Category::SortType Category::appletSort () const
{
    QString sort = value (AppletSortId);
    return sort == "SortByTitle" ? SortByTitle : SortByOrder;
}

const char* Category::componentOrderToString (ComponentOrderType order)
{
    return order == AppletsFirst ? "AppletsFirst" : "CategoriesFirst";
}

/*! \brief Specifies the order of the categories and applets inside the category.
 *
 * \returns CategoriesFirst (default) if the categories should be above the
 * applets, or returns AppletsFirst if the applets should be above the categories.
 */
Category::ComponentOrderType Category::componentOrder () const
{
    QString compOrder = value (ComponentOrderId);
    if (compOrder == componentOrderToString (AppletsFirst)) {
        return AppletsFirst;
    }
    // default:
    return CategoriesFirst;
}

/*! \brief Specifies the order of the category in a list.
 *
 * The category with lower order has to be above a category with higher order
 * if they are put in a list.
 */
int Category::order () const
{
    bool ok;
    int result = value (OrderId).toInt(&ok);
    return ok ? result : 999999;
}

bool Category::containsUncategorized () const
{
    return idMatch ("Uncategorized");
}

bool Category::orderLessThan (const Category *c1, const Category *c2)
{
    return c1->order() < c2->order();
}

bool Category::appletAutoStart () const
{
    QString autoSt = value (AppletAutoStartId);
    return autoSt == "1";
}

