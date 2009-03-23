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

    connect (this,
             SIGNAL(sizeChanged(const QSizeF &, const QSizeF &)),
             this, SLOT(onSizeChanged(const QSizeF &, const QSizeF &)));

}

#if 0
/* This function is responsible for keeping the width of the panned widget
   and its viewport the same. */
void DcpCategoryPage::resizeEvent ( QGraphicsSceneResizeEvent * event )
{
    QSizeF pannedWidgetSize = centralWidget()->size();
    QSizeF pannableViewportSize = this->size();

    qDebug() << "XXX sizechanged:" << pannedWidgetSize << "->" <<
             pannableViewportSize;
    int width = pannableViewportSize.width();
    if (pannedWidgetSize.width() != width){
        centralWidget()->setMinimumSize(width, -1);
        centralWidget()->setMaximumSize(width, -1);
        m_Category->setMinimumSize(width, -1);
        m_Category->setMaximumSize(width, -1);
    }

}
#endif


