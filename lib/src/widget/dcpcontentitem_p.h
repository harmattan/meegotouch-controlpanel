#ifndef DCPCONTENTITEMPRIVATE_H
#define DCPCONTENTITEMPRIVATE_H

#include "dcpappletobject.h"
#include "dcpappletmetadata.h"
#include "dcpwidgettypes.h"

/******************************************************************************
 * Private data class for the DcpContentItem class.
 */
class DcpContentItemPrivate {
public:
    DcpContentItemPrivate ();

    DcpAppletObject *m_Applet;
    int m_WidgetTypeId;
    bool m_Hidden;

    QString m_MattiID;

    // for the image widget:
    QString m_ImageName; // either the image id or path
    const QPixmap* m_Pixmap;   // the pixmap requested from MTheme if any
};

#endif // DCPCONTENTITEMPRIVATE_H

