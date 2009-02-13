#include "duisettingscomponent.h" 
#include <QtDebug>
DuiSettingsComponent::DuiSettingsComponent(DuiSettingsCategory *category,
                                  const QString& title, 
				  QGraphicsWidget *parent) : DuiWidget(parent),
                                m_Title(title),
				m_Category(category)
{}	 

DuiSettingsComponent*
DuiSettingsComponent::child(int i) const
{
    Q_UNUSED(i);
    qDebug() << "No child handling";
    return 0;
}
