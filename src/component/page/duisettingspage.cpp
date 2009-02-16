#include "duisettingspage.h"

#include <QtDebug>

#include <duilinearlayout.h>
#include <duilabel.h>
#include <duipannableviewport.h>

#include <duibutton.h>

#include <QGridLayout>

#include "duisimplecategory.h"
#include "duimaincategory.h"

#include "button2.h"

DuiSettingsPage::DuiSettingsPage()
{
}


void DuiSettingsPage::createContent()
{
    DuiLinearLayout* mainLayout = new DuiLinearLayout(Qt::Vertical);

    DuiLabel* title = new DuiLabel("Title");
    title->setAlignment(Qt::AlignCenter);
    title->setMaximumHeight(130);

    title->setMinimumWidth(300);

    mainLayout->addItem(title);

    CButton2 *button = new CButton2("alpha", 200, 90, "beta", 110, 30, 30, 30);

    mainLayout->addItem(button->layout());

    m_DesktopViewport = new DuiPannableViewport(Qt::Vertical, this);
#if 0
    DuiSimpleCategory *category = new DuiSimpleCategory("Example");
    DuiSimpleCategory *subcategory = new DuiSimpleCategory("SubCategory");
    category->add(subcategory);
#endif

    m_Category = new DuiMainCategory(tr("Settings"));
    for (int i=0; i<10;i++){
        if (i%2){
            DuiSimpleCategory *c2 = new DuiSimpleCategory("Two in a row1");
            DuiSimpleCategory *c3 = new DuiSimpleCategory("Tow in a row2");
            m_Category->add(c2, c3);
        } else {
            DuiSimpleCategory *c1 = new DuiSimpleCategory("One in a row");
            m_Category->add(c1);
        }
    }

    connect (m_DesktopViewport,
             SIGNAL(sizeChanged(const QSizeF &, const QSizeF &)),
             this, SLOT(onSizeChanged(const QSizeF &, const QSizeF &)));
    m_DesktopViewport->setWidget(m_Category);

    
    mainLayout->addItem(m_DesktopViewport);

    setLayout(mainLayout);
}


/* This function is responsible for keeping the width of the panned widget
   and its viewport the same. */
void DuiSettingsPage::onSizeChanged(const QSizeF & pannedWidgetSize,
                                    const QSizeF & pannableViewportSize)
{
    int width = pannableViewportSize.width();
    if (pannedWidgetSize.width() != width){
        m_Category->setMinimumSize(width, -1);
        m_Category->setMaximumSize(width, -1);
    }
}


void DuiSettingsPage::organizeContent(Dui::Orientation ori)
{
    Q_UNUSED(ori);
    qDebug() << "WARNING: orientation change is not yet implemented";
}

