#ifndef DCPAPPLETLAUNCHERIF_H
#define DCPAPPLETLAUNCHERIF_H

class DcpAppletLauncherIf
{
public:
    void appletPage( const QString &) {}
    void prestart () {}
    DcpAppletLauncherIf() {}
    bool isValid () const { return true; }

};

#endif

