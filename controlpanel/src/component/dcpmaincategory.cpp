#include "dcpmaincategory.h"

#include <DuiLayout>
#include <DuiGridLayoutPolicy>
#include <DuiLinearLayoutPolicy>
#include <DuiSceneManager>

#include <QtDebug>
#include <DuiSeparator>


static const QString SEPARATOR_OBJECTNAME = "DcpSmallSeparator";

DcpMainCategory::DcpMainCategory(const QString& title, QGraphicsWidget *parent,
                                 const QString& logicalId) :
    DcpCategory(title, parent, logicalId),
    m_ColCount(0),
	m_RowCount(0),
	m_ItemCount(0),
    m_CreateSeparators(false),
	m_HasLastSeparator(false)
{
    m_Layout = new DuiLayout(this);
//    m_Layout->setAnimator(0);

    m_LandscapeLayout = new DuiGridLayoutPolicy(m_Layout);

    m_Layout->setPolicy(m_LandscapeLayout);
    m_PortraitLayout = new DuiLinearLayoutPolicy(m_Layout, Qt::Vertical);

//    m_Layout->setContentsMargins(0,0,0,0);
    setLayout(m_Layout);

    // some defaults
  //  setHorizontalSpacing(12);
  //  setVerticalSpacing(12);
}

DcpMainCategory::~DcpMainCategory()
{}

void DcpMainCategory::deleteItems()
{
    if (!m_Layout) return;
    m_ItemCount = m_RowCount = m_ColCount = 0;

    // delete all items in all policies:
    foreach (DuiAbstractLayoutPolicy* policy, m_Layout->registeredPolicies()){
        for (int i=policy->count()-1; i >= 0; i--){
            QGraphicsWidget* widget = (QGraphicsWidget*)
                                      (policy->itemAt(i)->graphicsItem());
            Q_ASSERT(widget);
            m_Layout->removeItem(widget);
            widget->deleteLater();
        }
    }
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
    m_PortraitLayout->addItem(component);

    // add separators:
    if (m_CreateSeparators) {
        DuiSeparator* separator = new DuiSeparator(this);
        separator->setObjectName(SEPARATOR_OBJECTNAME);
        m_LandscapeLayout->addItemAtPosition(separator, m_RowCount+1, 0, 1,
                                             m_MaxColumns);
        m_PortraitLayout->addItem(separator);
        m_ItemCount++;
    }


    DcpCategory::add(component);
    m_RowCount++;
    m_ItemCount++;
}

// adds a normal item (not full line)
void DcpMainCategory::append(DcpComponent *component)
{
    if (m_ColCount >= m_MaxColumns) {
        m_ColCount = 0;
        m_RowCount++;
        if (m_CreateSeparators)
			m_RowCount++;
    }

    m_LandscapeLayout->addItemAtPosition(component,
                                         m_RowCount, m_ColCount);
    m_PortraitLayout->addItem(component);

    /*
    // force same size of columns:
    if (m_RowCount == 0) {
        m_LandscapeLayout->setColumnStretchFactor(m_ColCount, 1);
    }
    component->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    */

    // add separators:
    if (m_CreateSeparators) {
        DuiSeparator* separator = new DuiSeparator(this);
        separator->setObjectName(SEPARATOR_OBJECTNAME);
        m_LandscapeLayout->addItemAtPosition(separator, m_RowCount+1,
                                             m_ColCount);
        m_PortraitLayout->addItem(separator);
        m_ItemCount++;
    }

    DcpCategory::add(component);
    m_ColCount++;
    m_ItemCount++;
}

void DcpMainCategory::createContents()
{
}

void DcpMainCategory::onOrientationChange (const Dui::Orientation &orientation)
{
    if (orientation == Dui::Portrait) {
        m_Layout->setPolicy(m_PortraitLayout);
    } else {
        m_Layout->setPolicy(m_LandscapeLayout);
    }

    DcpCategory::onOrientationChange(orientation);
}

void DcpMainCategory::polishEvent()
{
    if (m_CreateSeparators && !m_HasLastSeparator) {
        fixSeparators();
    }
}

void DcpMainCategory::showEvent (QShowEvent*)
{
    if (sceneManager()) {
        onOrientationChange(sceneManager()->orientation());
    }
}

void DcpMainCategory::setCreateSeparators (bool create)
{
    m_CreateSeparators = create;
}

void DcpMainCategory::fixSeparators()
{
    // in landscape mode all items from the last line has to be removed
    int row = m_LandscapeLayout->rowCount()-1;
    for (int col=0; col<m_MaxColumns; col++) {
        QGraphicsLayoutItem* item = m_LandscapeLayout->itemAt(row, col);
        if (item) {
            m_LandscapeLayout->removeItem(item);
        }
    }
    // in portrait only the last one
    QGraphicsWidget* widget = (QGraphicsWidget*)(
                       m_PortraitLayout->itemAt(m_PortraitLayout->count()-1));
    if (widget){
        widget->deleteLater();
    }
}

void DcpMainCategory::setMaxColumns(int columns)
{
    m_MaxColumns = columns;
    for (int col=0; col<m_MaxColumns; col++) {
        m_LandscapeLayout->setColumnStretchFactor(col, 1);
    }
}

int DcpMainCategory::maxColumns(void)
{
    return m_MaxColumns;
}

void DcpMainCategory::setDoNotRemoveLastSeparator(bool remove)
{
    m_HasLastSeparator = remove;
}


