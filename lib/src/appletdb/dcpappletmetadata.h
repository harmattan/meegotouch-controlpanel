/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et sw=4 ts=4 sts=4: */

#ifndef DCPAPPLETMETADATA_H
#define DCPAPPLETMETADATA_H

#include <QObject>
#include <QString>
class DuiDesktopEntry;
class DcpAppletIf;
class DcpBrief;
class DcpWidget;

class DcpAppletMetadataPrivate;

/*!
 * \brief DcpAppletMetadata contains all the information on the applet variant
 * \details This class provides all the information about an applet variant in 
 *   practical format. Every applet can hold one or more .desktop file, for each
 *   there will be a #DcpAppletMetadata class object, and each will define a
 *   configuration for the applet binary. 
 * 
 *   If an applet have more than one desktop file we say the applet have more
 *   than one applet variant, that is from the user point of view the applet
 *   seems like it were more than one applet, but these variants might share 
 *   common elements (UI, code and data).
 */
class DcpAppletMetadata : public QObject
{
    Q_OBJECT
public:
    DcpAppletMetadata(const QString& filename);
    virtual ~DcpAppletMetadata();
    virtual bool isValid() const;
    virtual bool isUnique() const;
    virtual bool isModified() const;

    QString name() const;
    QString fileName() const;
    QString category() const;
    QString toggleIconId() const;
    
    QString binary() const;
    QString dslFilename () const;
    QString applicationCommand () const;
    bool    hasApplicationCommand () const;

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
    int getMainWidgetId () const;

    DcpAppletIf* applet() const;
    void setParent(DcpAppletMetadata *parent);
    DcpAppletMetadata* parent() const;
    QString parentName() const;
    void cleanup();
    static bool usageGreatherThan(DcpAppletMetadata *meta1,
                                  DcpAppletMetadata *meta2);

    static bool orderLessThan(DcpAppletMetadata *meta1,
                              DcpAppletMetadata *meta2);
signals:
    void briefChanged ();
    void activate ();
    void activateWithReferer (
            const QString  &refererName,
            int             refererWidgetId);

public slots:
	void slotClicked ();
    void setToggle (bool checked);
    bool activatePluginByName (const QString &name) const;

protected:
    DuiDesktopEntry* desktopEntry() const;
    QString desktopEntryStr(int id) const;
    DcpBrief* getBrief() const;

private:
    DcpAppletMetadataPrivate * const d;
    Q_DISABLE_COPY(DcpAppletMetadata);
};
#endif // DCPAPP LETMETADATA_H

