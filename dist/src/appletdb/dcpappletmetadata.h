#ifndef DCPAPPLETMETADATA_H
#define DCPAPPLETMETADATA_H
#include <duidesktopentry.h>

class DcpAppletMetadata : public DuiDesktopEntry
{
public:
    DcpAppletMetadata(const QString& filename);
    virtual ~DcpAppletMetadata();
    bool isValid();
    QString category() const;
    QString icon() const;
    QString appletBinary() const;

    QString widgetType();

    QString text1();
    QString text2();

    QString image();

    QString buttonCSS();
    QString label1CSS();
    QString label2CSS();
};
#endif // DCPAPPLETMETADATA_H
