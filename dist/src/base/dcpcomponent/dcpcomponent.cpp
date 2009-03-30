#include "dcpcomponent.h" 
#include <QtDebug>
#include <QGraphicsLayout>

DcpComponent::DcpComponent(DcpCategory *category,
                                  const QString& title, 
                  QGraphicsWidget *parent) : DuiWidget(parent),
                                m_Title(title),
				m_Category(category)
{
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

void
DcpComponent::onOrientationChange(const Dui::Orientation& orientation)
{
    Q_UNUSED(orientation);

    if (layout()) {
        layout()->invalidate();
        layout()->activate();
    }
}


QSizeF DcpComponent::sizeHint(Qt::SizeHint which,
                              const QSizeF & constraint) const
{
    return DuiWidget::sizeHint(which, constraint);
}

