#include "dcpcategorypage.h"

#include <QtDebug>

#include <duilinearlayout.h>
#include <duilabel.h>
#include <duipannableviewport.h>

#include <QGraphicsSceneResizeEvent>

#include "dcpmaincategory.h"


DcpCategoryPage::DcpCategoryPage() :
	DcpPage()
{
}


void DcpCategoryPage::createContent()
{
    DcpPage::createContent();
    m_Category = new DcpMainCategory("");
    mainLayout()->addItem(m_Category);
}

