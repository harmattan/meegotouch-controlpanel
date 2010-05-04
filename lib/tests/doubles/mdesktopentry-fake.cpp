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

MDesktopEntryPrivate::MDesktopEntryPrivate(const QString& fileName)
{
    this->fileName = fileName;
    this->values= fileDatas[fileName];
}


MDesktopEntry::MDesktopEntry(const QString &filename) 
    : d_ptr(new MDesktopEntryPrivate(filename))
{
    d_ptr->fileName = filename;
    d_ptr->isValid = true;
}

MDesktopEntry::~MDesktopEntry()
{
}

QString  MDesktopEntry::fileName () const { return d_ptr->fileName; }
bool  MDesktopEntry::isValid () const { return d_ptr->isValid;; }
uint  MDesktopEntry::hash () const { return 0; }
QString  MDesktopEntry::type () const { return ""; }
QString  MDesktopEntry::version () const { return ""; }
QString  MDesktopEntry::name () const 
{
    return d_ptr->values["Desktop Entry/Name"]; 
}

QString  MDesktopEntry::nameUnlocalized () const { return ""; }
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


