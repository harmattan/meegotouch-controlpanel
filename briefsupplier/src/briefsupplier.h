#ifndef BRIEFSUPPLIER_H
#define BRIEFSUPPLIER_H

#include <QObject>

class DcpBrief;
class DcpAppletObject;
class QIODevice;

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
    void watch (const QString& appletName);
    void unwatch (const QString& appletName);
    void switchToggle (const QString& appletName);

    // output:
    void outputStart ();
    void outputEnd ();
    void output (const char* key, const QString& value);
    void output (const char* key, int value);
    void outputBrief (DcpAppletObject* applet, bool textOnly = false);

private:
    class Stream* m_Stream;
};


#endif // BRIEFSUPPLIER_H

