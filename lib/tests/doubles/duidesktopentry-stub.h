#ifndef DUIDESKTOPENTRY_STUB_H__
#define DUIDESKTOPENTRY_STUB_H__

#include <DuiDesktopEntry>

DuiDesktopEntry::DuiDesktopEntry(const QString &filename) : d_ptr(0)
{
    Q_UNUSED(filename);
}

DuiDesktopEntry::~DuiDesktopEntry()
{
}

QString  DuiDesktopEntry::fileName () const { return ""; }
bool  DuiDesktopEntry::isValid () const { return true; }
uint  DuiDesktopEntry::hash () const { return 0; }
QString  DuiDesktopEntry::type () const { return ""; }
QString  DuiDesktopEntry::version () const { return ""; }
QString  DuiDesktopEntry::name () const { return ""; }
QString  DuiDesktopEntry::nameUnlocalized () const { return ""; }
QString  DuiDesktopEntry::genericName () const { return ""; }
bool  DuiDesktopEntry::noDisplay () const { return false; }
QString  DuiDesktopEntry::comment () const { return ""; }
QString  DuiDesktopEntry::icon () const { return ""; }
bool  DuiDesktopEntry::hidden () const { return false; }
QStringList  DuiDesktopEntry::onlyShowIn () const { QStringList l; return l; }
QStringList  DuiDesktopEntry::notShowIn () const { QStringList l; return l; }
QString  DuiDesktopEntry::tryExec () const { return ""; }
QString  DuiDesktopEntry::exec () const { return ""; }
QString  DuiDesktopEntry::path () const { return ""; }
bool  DuiDesktopEntry::terminal () const { return false; }
QStringList  DuiDesktopEntry::mimeType () const { QStringList l; return l; }
QStringList  DuiDesktopEntry::categories () const { QStringList l; return l; }
bool  DuiDesktopEntry::startupNotify () const { return false; }
QString  DuiDesktopEntry::startupWMClass () const { return ""; }
QString  DuiDesktopEntry::url () const { return ""; }
QString  DuiDesktopEntry::xMaemoService () const { return ""; }
QString  DuiDesktopEntry::value (const QString&) const { return ""; }
QString  DuiDesktopEntry::value (const QString&, const QString&) const { return ""; }
bool  DuiDesktopEntry::contains (const QString&) const { return false; }
bool  DuiDesktopEntry::contains (const QString&, const QString&) const  { return false; }
#endif

