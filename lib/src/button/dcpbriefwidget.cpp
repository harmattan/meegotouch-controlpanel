#include "dcpbriefwidget.h"
#include "dcpappletmetadata.h"
#include "dcpbutton2.h"
#include "dcpbutton2toggle.h"
#include "dcpbutton2image.h"
#include "dcpwidgettypes.h"

#include <duiscenemanager.h>

#include <QGraphicsLinearLayout>

DcpBriefWidget::DcpBriefWidget(DcpAppletMetadata* metadata, DuiWidget* parent)
    : DuiWidget(parent), m_RealWidget(0), m_Metadata(0)
{
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(this);
    layout->setContentsMargins(0,0,0,0);

    setMetadata(metadata);
}

DcpBriefWidget::~DcpBriefWidget()
{
}

void DcpBriefWidget::setMetadata(DcpAppletMetadata* metadata)
{
    // can be optimized if necessery (not recreating the widget, just updating its contents)
    if (m_RealWidget) m_RealWidget->deleteLater();

    if (m_Metadata) {
        disconnect (m_Metadata, SIGNAL(briefChanged()), this, SLOT(updateContents()));
    }
    Q_ASSERT(metadata);
    m_Metadata = metadata;

    switch(m_Metadata->widgetTypeID()) {
        case DCPLABELBUTTON:
        case DCPLABEL2BUTTON:
            m_RealWidget = constructToggle(metadata);
            break;
        case DCPLABEL2IMAGE :
            m_RealWidget = constructImage(metadata);
            break;
        default:
            m_RealWidget = new DcpButton2(this);
            break;
    }

    // this currently cannot change:
    m_RealWidget->setText1(m_Metadata->text1());

    ((QGraphicsLinearLayout*)(layout()))->addItem(m_RealWidget);
}

DcpButton2Image* DcpBriefWidget::constructImage(
        const DcpAppletMetadata* metadata)
{
    DcpButton2Image* image = new DcpButton2Image(this);
    image->setImageName(metadata->image());
    return image;
}

DcpButton2Toggle* DcpBriefWidget::constructToggle(
        const DcpAppletMetadata* metadata)
{
    DcpButton2Toggle* toggle = new DcpButton2Toggle(this);
    toggle->setSmallToggle(metadata->toggle());
/*  connect (m_RealWidget, SIGNAL(smallToggled(bool)),
             m_Metadata, SLOT(setToggle(bool))); TODO XXX */
    return toggle;
}

void DcpBriefWidget::updateContents()
{
    m_RealWidget->setText2(m_Metadata->text2());
}

void DcpBriefWidget::showEvent ( QShowEvent * event )
{
    Q_UNUSED (event);
    connect (m_RealWidget, SIGNAL(clicked()), this, SIGNAL(clicked()));
    connect (m_Metadata, SIGNAL(briefChanged()), this, SLOT(updateContents()));

    disconnect (this, SIGNAL(clicked()), m_Metadata, SLOT(slotClicked()));
    connect (this, SIGNAL(clicked()), m_Metadata, SLOT(slotClicked()));
    

//	disconnect (m_RealWidget, SIGNAL(clicked()), this, SLOT(slotClicked()));
 //   connect (m_RealWidget, SIGNAL(clicked()), this, SLOT(slotClicked()));


 /*   connect(DuiSceneManager::instance(),
            SIGNAL(orientationChanged (const Dui::Orientation &)),
            this, SLOT(onOrientationChange(const Dui::Orientation &)));
            */
    updateContents();
}

void DcpBriefWidget::hideEvent ( QHideEvent * event )
{
    Q_UNUSED (event);
    disconnect (m_RealWidget, SIGNAL(clicked()), this, SIGNAL(clicked()));
    disconnect (m_Metadata, SIGNAL(briefChanged()), this, SLOT(updateContents()));

//	disconnect (this, SIGNAL(clicked()), m_Metadata, SLOT(slotClicked()));	

//	disconnect (m_RealWidget, SIGNAL(clicked()), this, SLOT(slotClicked()));

 /*   disconnect(DuiSceneManager::instance(),
            SIGNAL(orientationChanged (const Dui::Orientation &)),
            this, SLOT(onOrientationChange(const Dui::Orientation &)));
            */
}
/*
void DcpBriefWidget::onOrientationChange (const Dui::Orientation &orientation)
{
    layout()->invalidate();
}
*/

void DcpBriefWidget::slotClicked()
{

	qDebug() << Q_FUNC_INFO;
}
