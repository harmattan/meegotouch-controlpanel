#include "dcpmaincategory.h"

#include <duilayout.h>
#include <duigridlayoutpolicy.h>
#include <duilinearlayoutpolicy.h>

#include <duiscenemanager.h>
#include <QtDebug>
#include <DuiSeparator>


static const QString SEPARATOR_OBJECTNAME = "DcpSmallSeparator";

DcpMainCategory::DcpMainCategory(
        const QString& title, QGraphicsWidget *parent
) : DcpCategory(title, parent), m_ColCount(0), m_RowCount(0), m_ItemCount(0),
    m_CreateSeparators(false), m_HasLastSeparator(false)
{
    m_Layout = new DuiLayout(this);
    m_Layout->setAnimator(0);

    m_LandscapeLayout = new DuiGridLayoutPolicy(m_Layout);

    m_Layout->setPolicy(m_LandscapeLayout);
    m_PortraitLayout = new DuiLinearLayoutPolicy(m_Layout, Qt::Vertical);

    m_Layout->setContentsMargins(0,0,0,0);
    setLayout(m_Layout);

    // some defaults
    setHorizontalSpacing(12);
    setVerticalSpacing(12);
}

void DcpMainCategory::setHorizontalSpacing(int space)
{
    m_LandscapeLayout->setHorizontalSpacing(space);
}

void DcpMainCategory::setVerticalSpacing(int space)
{
    m_LandscapeLayout->setVerticalSpacing(space);
    m_PortraitLayout->setSpacing(space);
}

// adds a full line item
void DcpMainCategory::add(DcpComponent *component)
{
    if (m_ColCount > 0) {
        m_ColCount = 0;
        m_RowCount++;
        if (m_CreateSeparators) m_RowCount++;
    }

    // add the component:
    m_LandscapeLayout->addItemAtPosition(component,
                                         m_RowCount, 0 /* column */,
              1 /* rowspan */, m_MaxColumns /* columnspan */);
    m_PortraitLayout->addItemAtPosition(component,
                                        m_ItemCount);

    // add separators:
    if (m_CreateSeparators) {
        DuiSeparator* separator = new DuiSeparator(this);
        separator->setObjectName(SEPARATOR_OBJECTNAME);
        m_LandscapeLayout->addItemAtPosition(separator, m_RowCount+1, 0, 1,
                                             m_MaxColumns);
        m_PortraitLayout->addItemAtPosition(separator, m_ItemCount+1);
        m_ItemCount++;
    }


    DcpCategory::add(component);
    m_RowCount++;
    m_ItemCount++;
}


// adds a normal item (not full line)
void DcpMainCategory::append(DcpComponent *component)
{
    if (m_ColCount >= m_MaxColumns)
    {
        m_ColCount = 0;
        m_RowCount++;
        if (m_CreateSeparators) m_RowCount++;
    }


    m_LandscapeLayout->addItemAtPosition(component,
                                         m_RowCount, m_ColCount);
    qDebug() << "XXX portraitlayout:" << m_ItemCount;
    m_PortraitLayout->addItemAtPosition(component,
                                        m_ItemCount);

    // add separators:
    if (m_CreateSeparators) {
        DuiSeparator* separator = new DuiSeparator(this);
        separator->setObjectName(SEPARATOR_OBJECTNAME);
        m_LandscapeLayout->addItemAtPosition(separator, m_RowCount+1,
                                             m_ColCount);
        m_PortraitLayout->addItemAtPosition(separator, m_ItemCount+1);
        m_ItemCount++;
    }

    DcpCategory::add(component);
    m_ColCount++;
    m_ItemCount++;
}


void DcpMainCategory::createContents()
{
}


void
DcpMainCategory::onOrientationChange (const Dui::Orientation &orientation)
{
    if (m_CreateSeparators) {
        fixSeparators(orientation);
    }

    if (orientation == Dui::Portrait) {
        m_Layout->setPolicy(m_PortraitLayout);
    } else {
        m_Layout->setPolicy(m_LandscapeLayout);
    }

    DcpCategory::onOrientationChange(orientation);
}


void DcpMainCategory::polishEvent ()
{
    if (DuiSceneManager::instance()){
        onOrientationChange(DuiSceneManager::instance()->orientation());
    }
}

void DcpMainCategory::setCreateSeparators (bool create)
{
    m_CreateSeparators = create;
}

void DcpMainCategory::fixSeparators(const Dui::Orientation &orientation)
{
    Q_ASSERT(m_CreateSeparators);

    // in landscape mode all items from the last line has to be hidden,
    // in portrait only the last one
    bool isLandscape = (orientation == Dui::Landscape);
    for (int col=0; col<m_MaxColumns-1; col++){
        QGraphicsLayoutItem* item = m_LandscapeLayout->itemAt(m_RowCount+1, col);
        if (item != 0) {
            item->graphicsItem()->setVisible(!isLandscape);
        }
    }
    QGraphicsLayoutItem* lastItem = m_LandscapeLayout->itemAt(m_RowCount+1, m_MaxColumns-1);
    if (!lastItem) {
        // last item is single
        lastItem = m_LandscapeLayout->itemAt(m_RowCount, 0);
    }
    if (lastItem) {
        lastItem->graphicsItem()->setVisible(m_HasLastSeparator);
    }
}

void DcpMainCategory::setMaxColumns(int columns){
    m_MaxColumns = columns;

    // force same size of columns:
    for (int i=0; i<columns; i++){
        m_LandscapeLayout->setColumnStretchFactor(i, 1);
    }
}

void DcpMainCategory::setDoNotRemoveLastSeparator(bool remove) {
    m_HasLastSeparator = remove;
}

