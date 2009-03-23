#include "dcpcategorypage.h"

#include <QtDebug>

#include <duilinearlayout.h>
#include <duilabel.h>
#include <duipannableviewport.h>
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
    /* XXX
    connect (m_DesktopViewport,
             SIGNAL(sizeChanged(const QSizeF &, const QSizeF &)),
             this, SLOT(onSizeChanged(const QSizeF &, const QSizeF &)));
    */
}


/* This function is responsible for keeping the width of the panned widget
   and its viewport the same. */
void DcpCategoryPage::onSizeChanged(const QSizeF & pannedWidgetSize,
                                    const QSizeF & pannableViewportSize)
{
/* XXX
   int width = pannableViewportSize.width();
    if (pannedWidgetSize.width() != width){
        panWidget()->setMinimumSize(width, -1);
        panWidget()->setMaximumSize(width, -1);
        m_Category->setMinimumSize(width, -1);
        m_Category->setMaximumSize(width, -1);
    }
    */
}



