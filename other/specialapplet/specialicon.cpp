#include "specialicon.h"

#include "dcpskeleton.h"

#include <MButton>
#include <QGraphicsLinearLayout>

SpecialIcon::SpecialIcon()
{
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout (this);
    MButton* button1 = new MButton ("Open a page");
    MButton* button2 = new MButton ("Open Date & Time");
    layout->addItem (button1);
    layout->addItem (button2);
    connect (button1, SIGNAL (clicked()), this, SLOT(onClick1()));
    connect (button2, SIGNAL (clicked()), this, SLOT(onClick2()));
}

void SpecialIcon::onClick1()
{
    emit changeWidget (DcpSkeleton::Main);
}

void SpecialIcon::onClick2()
{
    emit activatePluginByName ("Date & Time");
}

