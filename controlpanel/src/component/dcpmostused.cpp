#include "dcpmostused.h"
#include "dcpcategories.h"
#include "category.h"

#include "dcpappletbuttons.h"

DcpMostUsed::DcpMostUsed (QGraphicsWidget* parent):
    MContainer (parent),
    m_ItemsAvailable (false)
{
    setStyleName ("CommonContainerInverted");
    Category* mostUsedCat = DcpCategories::instance()->categoryById (MostUsed);
    m_AppletButtons = new DcpAppletButtons (mostUsedCat);
    setCentralWidget (m_AppletButtons);
    checkItemsAvailable();
}

void DcpMostUsed::refresh()
{
    qDebug ("Refresh has happened in mostused, "
            "this should not happen at app start");
    m_AppletButtons->reload ();
    checkItemsAvailable();
}

void DcpMostUsed::checkItemsAvailable ()
{
    if (!m_ItemsAvailable && m_AppletButtons->metadataCount() > 0) {
        m_ItemsAvailable = true;
        retranslateUi ();
        emit itemsBecameAvailable();
    }
}

void DcpMostUsed::retranslateUi ()
{
    const Category* mostUsedCat = m_AppletButtons->categoryInfo();
    if (mostUsedCat) {
        setTitle (mostUsedCat->title());
    }
}

