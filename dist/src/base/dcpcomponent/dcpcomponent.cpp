#include "dcpcomponent.h" 
#include <QtDebug>
DcpComponent::DcpComponent(DcpCategory *category,
                                  const QString& title, 
				  QGraphicsWidget *parent) : DuiWidget(parent),
                                m_Title(title),
				m_Category(category)
{
    /* Sadly this is not coming, so implemented in a manual way.
    connect (this, SIGNAL(orientationChanged (const Dui::Orientation &)),
             this, SLOT(onOrientationChange (const Dui::Orientation &)));
     */
}

DcpComponent*
DcpComponent::child(int i) const
{
    Q_UNUSED(i);
    qDebug() << "No child handling";
    return 0;
}

void
DcpComponent::switchToSubPage()
{
    emit openSubPage(subPage());
}

