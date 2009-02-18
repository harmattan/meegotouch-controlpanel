#include "duisettingscomponent.h" 
#include <QtDebug>
DuiSettingsComponent::DuiSettingsComponent(DuiSettingsCategory *category,
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

DuiSettingsComponent*
DuiSettingsComponent::child(int i) const
{
    Q_UNUSED(i);
    qDebug() << "No child handling";
    return 0;
}

void
DuiSettingsComponent::switchToSubPage()
{
    emit openSubPage(subPageId());
}

