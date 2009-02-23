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
    DuiLinearLayout* mainLayout = new DuiLinearLayout(Qt::Vertical);

    DuiLabel* title = new DuiLabel("Title");
    title->setAlignment(Qt::AlignCenter);
    title->setMaximumHeight(30);
    mainLayout->addItem(title);

    m_Category = new DcpMainCategory("");

    connect (m_DesktopViewport,
             SIGNAL(sizeChanged(const QSizeF &, const QSizeF &)),
             this, SLOT(onSizeChanged(const QSizeF &, const QSizeF &)));
    m_DesktopViewport->setWidget(m_Category);


    mainLayout->addItem(m_DesktopViewport);

    setLayout(mainLayout);
}


/* This function is responsible for keeping the width of the panned widget
   and its viewport the same. */
void DcpCategoryPage::onSizeChanged(const QSizeF & pannedWidgetSize,
                                    const QSizeF & pannableViewportSize)
{
    int width = pannableViewportSize.width();
    if (pannedWidgetSize.width() != width){
        m_Category->setMinimumSize(width, -1);
        m_Category->setMaximumSize(width, -1);
    }
}



