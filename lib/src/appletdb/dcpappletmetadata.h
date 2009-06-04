#ifndef DCPAPPLETMETADATA_H
#define DCPAPPLETMETADATA_H

#include <QObject>
#include <QString>
class DuiDesktopEntry;
class DcpAppletIf;
class DcpBrief;

class DcpAppletMetadataPrivate;
class DcpAppletMetadata : public QObject
{
    Q_OBJECT
public:
    DcpAppletMetadata(const QString& filename);
    virtual ~DcpAppletMetadata();
    virtual bool isValid() const;
    virtual bool isModified() const;

    QString name() const;
    QString fileName() const;
    QString category() const;
//    QString icon() const;
    QString binary() const;
    QString fullBinary() const;

    QString widgetType() const;

    int widgetTypeID() const;

    Qt::Alignment align() const;
    bool toggle() const;

    QString text1() const;
    QString text2() const;

    QString image() const;

    int order() const;
    int usage() const;

    DcpAppletIf* applet() const;

signals:
    void briefChanged();

protected:
    DuiDesktopEntry* desktopEntry() const;
    QString desktopEntryStr(int id) const;
    DcpBrief* brief() const;

private:
    DcpAppletMetadataPrivate * const d;
    Q_DISABLE_COPY(DcpAppletMetadata);
};
#endif // DCPAPP LETMETADATA_H

