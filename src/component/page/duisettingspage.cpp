#include "duisettingspage.h"

#include <QtDebug>

#include <duilinearlayout.h>
#include <duilabel.h>
#include <duiflowlayout.h>
#include <duipannableviewport.h>


DuiSettingsPage::DuiSettingsPage()
{
}


void DuiSettingsPage::createContent()
{
    DuiLinearLayout* mainLayout = new DuiLinearLayout(Qt::Vertical);

    DuiLabel* m_Label = new DuiLabel("Title");
    mainLayout->addItem(m_Label);

    DuiPannableViewport* desktopViewport = new DuiPannableViewport(Qt::Vertical, this);


    // --- TODO: Please replace me ---
    DuiWidget* textWidget = new DuiWidget();

    DuiFlowLayout* textLayout = new DuiFlowLayout();
    for (int i=0; i<360; i++){
        DuiLabel* label = new DuiLabel(QString("%1%1%1 ").arg(i));
        textLayout->addItem(label);
    }
    textWidget->setLayout(textLayout);

    textWidget->setMinimumSize(size().width()-30, 800);
    textWidget->setMaximumSize(size().width()-30, 800);

    // ---


    desktopViewport->setWidget(textWidget);
    mainLayout->addItem(desktopViewport);

    setLayout(mainLayout);
}


void DuiSettingsPage::organizeContent(Dui::Orientation ori)
{
    qDebug() << "WARNING: orientation change is not yet implemented";
}

