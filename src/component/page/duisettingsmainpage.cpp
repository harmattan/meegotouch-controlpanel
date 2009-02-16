#include "duisettingsmainpage.h"

#include <QtDebug>

#include <duilinearlayout.h>
#include <duilabel.h>
#include <duipannableviewport.h>

#include "duisimplecategory.h"
#include "duimaincategory.h"
#include "duidescriptioncomponent.h"


DuiSettingsMainPage::DuiSettingsMainPage()
{
}


void DuiSettingsMainPage::createContent()
{
    DuiSettingsPage::createContent();
    DuiLinearLayout* mainLayout = new DuiLinearLayout(Qt::Vertical);

    DuiLabel* title = new DuiLabel("Title");
    title->setAlignment(Qt::AlignCenter);
    title->setMaximumHeight(30);
    mainLayout->addItem(title);

    m_Category = new DuiMainCategory(tr("Settings"));
    for (int i=0; i<10;i++){
        if (i%2){
            DuiDescriptionComponent *c2 = new DuiDescriptionComponent(
                    m_Category, "Example1");
            c2->setDescription("This is the first example configuration, "
                               "to test the look and feel... heyho. "
                               "i hope it is working, blabla bla...");
            DuiDescriptionComponent *c3 = new DuiDescriptionComponent(
                    m_Category, "Example2");
            c3->setDescription("This is the second example configuration, "
                               "to test the look and feel... heyho. "
                               "i hope it is working, blabla bla...");
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
void DuiSettingsMainPage::onSizeChanged(const QSizeF & pannedWidgetSize,
                                    const QSizeF & pannableViewportSize)
{
    int width = pannableViewportSize.width();
    if (pannedWidgetSize.width() != width){
        m_Category->setMinimumSize(width, -1);
        m_Category->setMaximumSize(width, -1);
    }
}


