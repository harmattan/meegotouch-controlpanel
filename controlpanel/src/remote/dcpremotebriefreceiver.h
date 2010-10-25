#ifndef DCPREMOTEBRIEFRECEIVER_H
#define DCPREMOTEBRIEFRECEIVER_H

#include <QProcess>
class DcpRemoteBrief;

class DcpRemoteBriefReceiver: public QProcess
{
    Q_OBJECT

public:
    static void setArguments (int argc, char** argv);
    static DcpRemoteBriefReceiver* instance ();
    ~DcpRemoteBriefReceiver();

    void watch (DcpRemoteBrief* brief);
    int watchCount ();
    void unwatch (DcpRemoteBrief* brief);
    void switchToggle (const QString& appletName);
    void preload (const QString& appletName);

protected slots:
    void onReadyRead ();
    void onFinished ( int exitCode, QProcess::ExitStatus exitStatus );
    void suicide ();
    void onStarted ();
    void onConnectError ();

protected:
    void cmd (const QString& command, const QString& appletName);
    DcpRemoteBriefReceiver();

private:
    class DcpRemoteBriefReceiverPriv* priv;

};


#endif // DCPREMOTEBRIEFRECEIVER_H

