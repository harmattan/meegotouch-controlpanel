#ifndef DCPAPPLETMETADATA_FAKE_H__
#define DCPAPPLETMETADATA_FAKE_H__

#include "dcpappletmetadata.h"

static QMap<const DcpAppletMetadata *, int> appletStat;

void DcpAppletMetadata::slotClicked()
{
    ++appletStat[this];
}

int DcpAppletMetadata::usage() const
{
    return appletStat.value(this);
}

#endif
