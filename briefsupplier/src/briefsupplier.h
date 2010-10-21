#ifndef BRIEFSUPPLIER_H
#define BRIEFSUPPLIER_H

#include <QObject>
#include <QStringList>
#include <QHash>

class DcpBrief;
class DcpAppletObject;
class QTextStream;

class BriefSupplier: public QObject
{
    Q_OBJECT

public:
    BriefSupplier();
    ~BriefSupplier();

    void setIODevice (QIODevice* device);

protected slots:
    void onCommandArrival (const QString& command);
    void onBriefChanged ();
    void onNewConnection ();
    void onLocaleChange ();

protected:
    // commands:
    void preload (const QString& appletName);
    void watch (const QString& appletName);
    void unwatch (const QString& appletName);
    void switchToggle (const QString& appletName);

    // output:
    void outputStart ();
    void outputEnd ();
    void output (const char* key, const QString& value);
    void output (const char* key, int value);
    void outputBrief (DcpAppletObject* applet, bool textOnly = false);

    // loading in the background:
    void startLoading ();
    void timerEvent ( QTimerEvent * event );

private:
    class Reader* m_Input;
    QTextStream* m_Output;

    QStringList m_PreloadApplets;
};


#endif // BRIEFSUPPLIER_H

