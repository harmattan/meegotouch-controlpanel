#ifndef DCPAPPLETMETADATA_H
#define DCPAPPLETMETADATA_H

#include <QObject>
#include <QString>
class DuiDesktopEntry;
class DcpAppletIf;
class DcpBrief;

class DcpAppletMetadataPrivate;

/*!
    \brief DcpAppletMetadata contains all the information of the applet
    \details This class provides all the info
*/
//class DcpAppletMetadata;
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
    QString binaryDir() const;
    void setBinaryDir(const QString& dir);

    int widgetTypeID() const;

    Qt::Alignment align() const;
    bool toggle() const;

    QString text1() const;
    QString text2() const;

    QString image() const;

    int order() const;
    int usage() const;
    
    QString part() const;

    DcpAppletIf* applet() const;
    void setParent(DcpAppletMetadata *parent);
    DcpAppletMetadata* parent() const;
    QString parentName() const;
//	void save();
    void cleanup();
    static bool usageGreatherThan(DcpAppletMetadata *meta1,
                                  DcpAppletMetadata *meta2);

    static bool orderLessThan(DcpAppletMetadata *meta1,
                              DcpAppletMetadata *meta2);
signals:
    void briefChanged();

protected slots:
	void slotClicked();

protected:
    DuiDesktopEntry* desktopEntry() const;
    QString desktopEntryStr(int id) const;
    DcpBrief* brief() const;

private:
    DcpAppletMetadataPrivate * const d;
    Q_DISABLE_COPY(DcpAppletMetadata);
};
#endif // DCPAPP LETMETADATA_H

