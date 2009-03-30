#include "dcpcomponent.h" 
#include <QtDebug>
#include <QGraphicsLayout>

DcpComponent::DcpComponent(DcpCategory *category,
                                  const QString& title, 
                  QGraphicsWidget *parent) : DuiWidgetController(parent),
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

//    updateGeometry();
}


QSizeF DcpComponent::sizeHint(Qt::SizeHint which,
                              const QSizeF & constraint) const
{
    // see DcpComponent::boundingRect on why is this
    return DuiWidget::sizeHint(which, constraint);
}


QRectF DcpComponent::boundingRect() const
{
    /* this hack is for getting the correct boundingRect,
       if the view does not give it (eg. no view is set),
       based on the widgets sizes in the layout */
    QRectF size = DuiWidgetController::boundingRect();
    if (size.isEmpty()){
        return DuiWidget::boundingRect();
    } else {
        return size;
    }
}

