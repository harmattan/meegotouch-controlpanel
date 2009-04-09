#ifndef DCPAPPLETMETADATA_H
#define DCPAPPLETMETADATA_H
#include <duidesktopentry.h>
class DcpAppletMetadataPrivate;
class DcpAppletMetadata : public DuiDesktopEntry
{
public:
    DcpAppletMetadata(const QString& filename);
    virtual ~DcpAppletMetadata();
    virtual bool isValid();
    virtual bool isModified();
    QString category() const;
    QString icon() const;
    QString binary() const;
    QString fullBinary() const;

    QString widgetType();

    int widgetTypeID();

    Qt::Alignment align();
    bool toggle();
    bool smallToggle();

    QString text1();
    QString text2();

    QString image();

    QString buttonCSS();
    QString label1CSS();
    QString label2CSS();
    int order();
    int usage();
private:
    DcpAppletMetadataPrivate * const d;
//    Q_DISABLE_COPY(DcpAppletMetadata);
};
#endif // DCPAPP LETMETADATA_H
