#include "dcpcomponent.h" 
#include <QtDebug>
#include <QGraphicsLayout>

DcpComponent::DcpComponent(DcpCategory *category, const QString& title, 
                           QGraphicsWidget *parent,
                           const QString& logicalId) : 
				DuiWidget(parent),
                m_Title(title),
                m_LogicalId(logicalId),
                m_Category(category)
{
}

DcpComponent* DcpComponent::child(int i) const
{
    Q_UNUSED(i);
    return 0;
}

void DcpComponent::switchToSubPage()
{
    emit openSubPage(subPage());
}

void DcpComponent::onOrientationChange(const Dui::Orientation& orientation)
{
    Q_UNUSED(orientation);
}
