#ifndef DCPREMOTEBRIEFRECEIVERPRIV_H
#define DCPREMOTEBRIEFRECEIVERPRIV_H

#include <QTextStream>
#include "dcpremotebrief.h"
#include <QHash>
#include <QLocalSocket>
#include <QStringList>

class DcpRemoteBriefReceiver;

class DcpRemoteBriefReceiverPriv
{
public:
    DcpRemoteBriefReceiverPriv ();

    QLocalSocket socket;
    QTextStream send;
    QTextStream receive;
    DcpRemoteBrief* currentBrief;
    QHash<QString, DcpRemoteBrief*> briefs;

    static DcpRemoteBriefReceiver* instance;
    static QStringList args;

    QStringList waitingCommands;
};


#endif // DCPREMOTEBRIEFRECEIVERPRIV_H
