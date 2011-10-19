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

#ifndef MDESKTOPENTRY_STUB_H__
#define MDESKTOPENTRY_STUB_H__

#include <QStringList>
#include <MDesktopEntry>
#include "filedatas.h"
class MDesktopEntryPrivate
{
public:
    MDesktopEntryPrivate(const QString& fileName);
    QString fileName;
    bool isValid;
    StringMap values;

};

MDesktopEntryPrivate::MDesktopEntryPrivate(const QString& fileName):
    isValid(false)
{
    this->fileName = fileName;
    this->values= fileDatas[fileName];
}


MDesktopEntry::MDesktopEntry(const QString &filename) 
    : d_ptr(new MDesktopEntryPrivate(filename))
{
    d_ptr->fileName = filename;
}

MDesktopEntry::~MDesktopEntry()
{
}

QString  MDesktopEntry::fileName () const { return d_ptr->fileName; }
bool  MDesktopEntry::isValid () const 
{ 
    return fileDatas[d_ptr->fileName]["isValid"] == "y";
}
uint  MDesktopEntry::hash () const { return 0; }
QString  MDesktopEntry::type () const { return ""; }
QString  MDesktopEntry::version () const { return ""; }
QString  MDesktopEntry::name () const 
{
    return "NameLocalized";
}

QString  MDesktopEntry::nameUnlocalized () const {
    return d_ptr->values["Name"]; 
}
QString  MDesktopEntry::genericName () const { return ""; }
bool  MDesktopEntry::noDisplay () const { return false; }
QString  MDesktopEntry::comment () const { return ""; }
QString  MDesktopEntry::icon () const { return ""; }
bool  MDesktopEntry::hidden () const { return false; }
QStringList  MDesktopEntry::onlyShowIn () const
 { QStringList l; return l; }
QStringList  MDesktopEntry::notShowIn () const 
 { QStringList l; return l; }
QString  MDesktopEntry::tryExec () const { return ""; }
QString  MDesktopEntry::exec () const { return ""; }
QString  MDesktopEntry::path () const { return ""; }
bool  MDesktopEntry::terminal () const { return false; }
QStringList  MDesktopEntry::mimeType () const
 { QStringList l; return l; }
QStringList  MDesktopEntry::categories () const 
 { QStringList l; return l; }
bool  MDesktopEntry::startupNotify () const { return false; }
QString  MDesktopEntry::startupWMClass () const { return ""; }
QString  MDesktopEntry::url () const { return ""; }
QString  MDesktopEntry::xMaemoService () const { return ""; }

//#define OLD_LIBM
#ifdef OLD_LIBM
QString  MDesktopEntry::value (QString key) const 
{
    return d_ptr->values[key];
}

QString  MDesktopEntry::value (QString group, QString key) const 
{
    return d_ptr->values.value(group + "/" + key);
}

bool  MDesktopEntry::contains (QString key) const
{
    return d_ptr->values.contains(key); 
}

bool  MDesktopEntry::contains (QString group, QString key) const
{
    return d_ptr->values.contains(group + "/" + key);
}
#else
QString  MDesktopEntry::value (const QString& key) const
{
    return d_ptr->values[key];
}

QString  MDesktopEntry::value (const QString& group, const QString& key) const
{
    return d_ptr->values.value(group + "/" + key);
}

bool  MDesktopEntry::contains (const QString& key) const 
{
    return d_ptr->values.contains(key); 
}

bool  MDesktopEntry::contains (const QString& group, const QString& key) const 
{
    return d_ptr->values.contains(group + "/" + key);
}


#endif // OLD_LIBM
#endif // MDESKTOPENTRY_STUB_H__


