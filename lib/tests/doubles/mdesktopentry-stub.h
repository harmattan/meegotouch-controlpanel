#ifndef MDESKTOPENTRY_STUB_H__
#define MDESKTOPENTRY_STUB_H__

#include <MDesktopEntry>

MDesktopEntry::MDesktopEntry(const QString &filename) : d_ptr(0)
{
    Q_UNUSED(filename);
}

MDesktopEntry::~MDesktopEntry()
{
}

QString  MDesktopEntry::fileName () const { return ""; }
bool  MDesktopEntry::isValid () const { return true; }
uint  MDesktopEntry::hash () const { return 0; }
QString  MDesktopEntry::type () const { return ""; }
QString  MDesktopEntry::version () const { return ""; }
QString  MDesktopEntry::name () const { return ""; }
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
QString  MDesktopEntry::value (QString) const { return ""; }
QString  MDesktopEntry::value (QString, QString) const { return ""; }
bool  MDesktopEntry::contains (QString) const { return false; }
bool  MDesktopEntry::contains (QString, QString) const  { return false; }
#else
QString  MDesktopEntry::value (const QString&) const { return ""; }
QString  MDesktopEntry::value (const QString&, const QString&) const
 { return ""; }
bool  MDesktopEntry::contains (const QString&) const { return false; }
bool  MDesktopEntry::contains (const QString&, const QString&) const 
 { return false; }
#endif



#endif

