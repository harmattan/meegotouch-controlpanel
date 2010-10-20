#ifndef DCPREMOTEBRIEF_P_H
#define DCPREMOTEBRIEF_P_H

#include <bsuppliercommands.h>
#include <QString>
#include <QHash>

#include "dcpremotebriefreceiver.h"

class DcpRemoteBriefPriv
{
public:
    DcpRemoteBriefPriv (const QString& name);

    QString appletName;
    QHash<const char*, QString> values;
};

#endif // DCPREMOTEBRIEF_P_H

